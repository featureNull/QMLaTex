#include "LatexCompilerWorker.h"

#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include <QPixmap>

#define TEX_FILENAME		"report.tex"
#define PDF_FILENAME		"report.pdf"
#define PDFINFO_FILENAME	"report.pdfinfo"

#define PDFLATEX_TIMEOUT	10000

namespace Reports {

LatexCompilerWorker::LatexCompilerWorker(QObject* parent) 
	: QThread(parent), logger("Latex.LatexCompilerWorker")
{
	_terminate = false;
	start();
}

LatexCompilerWorker::~LatexCompilerWorker()
{
	_terminate = true;
	_waitCond.wakeAll();

	// wait until thread is down
	if (!wait(3000)) {
		// get rough
		terminate();
	}
}

void LatexCompilerWorker::startBuild(const QString& outPath, const QString& code)
{
	_mutex.lock();
	_currentCode = code;
	_currentOutPath = outPath;
	_mutex.unlock();

	_waitCond.wakeAll();
}

void LatexCompilerWorker::run()
{
	forever {
		QString code;
		QString outPath;
		bool terminate;

		pollNext(&outPath, &code, &terminate);

		if (terminate)
			break;

		// note das ist nicht der main thread
		emit buildStarted();
		build(outPath, code);
		emit buildTerminated();

		if (errorPresent()) {
			// beginn von neuem wenn fahler da sind
			continue;
		}

		// previews erstellen (sehr teuer)
		emit startCreatingPreviews();

		// previw jpegs bauen
		const int numOfPages = _pdfInfo["Pages"].toInt();
		for (int ii = 1; ii <=  numOfPages; ii++) {
			QPixmap pix = createPreviewPage(outPath, PDF_FILENAME, ii);
			emit previewPageGenerated(ii, pix);

			if (commandPending())
				break;
		}
	} // forever
}

void LatexCompilerWorker::pollNext(QString* outPath, QString* code, bool* terminate)
{
	Q_ASSERT(outPath != nullptr);
	Q_ASSERT(code != nullptr);
	Q_ASSERT(terminate != nullptr);

	_mutex.lock();

	while ((_currentCode.length() == 0) && !_terminate) {
		_waitCond.wait(&_mutex);
	}

	(*outPath) = _currentOutPath;
	(*code) = _currentCode;
	(*terminate) = _terminate;

	_lastErrorText.clear();
	_currentCode.clear();
	_currentOutPath.clear();

	_mutex.unlock();
}


void LatexCompilerWorker::build(const QString& outPath, const QString& code)
{
	QElapsedTimer dbgTimer;
	dbgTimer.start();

	qCDebug(logger) << "build" << code;

	QFile file(outPath + "/" + TEX_FILENAME);
	file.open(QIODevice::WriteOnly);
	QTextStream out(&file);   // we will serialize the data into the file
	out << code;
	file.close();

	// tex kompilieren
	if (compileFile(outPath, TEX_FILENAME) != SuperXiVollGeil) {
		emitError(tr("cannot compile tex file"), _pdfLatexErrorText);
		return;
	}

	// dem pdf info entlocken (hauptsaechlich seitenanzahl)
	if (queryPdfInfo(outPath, PDF_FILENAME) != SuperXiVollGeil) {
		emitError(tr("cannot read pdf info"));
		return;
	}
	else {
		emit pdfInfoReaded(_pdfInfo);
	}

	emit buildSuccess();
}

LatexCompilerWorker::Result 
	LatexCompilerWorker::compileFile(const QString& outPath, const QString& file)
{
	QElapsedTimer dbgTimer;
	dbgTimer.start();

	qCInfo(logger) << "compile file:" << file;
	const char* exefile = "pdflatex.exe";

	QStringList args;
	args << "-halt-on-error" << file;

	QProcess process;
	process.setWorkingDirectory(outPath);
	process.setArguments(args);
	process.setProgram(exefile);

	Result res = exec_process(&process, PDFLATEX_TIMEOUT);

	if (res != SuperXiVollGeil) {
		// note that error is stdout
		QString txt = QString::fromLatin1(process.readAllStandardOutput());

		// letzten zeilen selecten
		int index = txt.length();
		int l = txt.length();

		for (int ii = 0; ii < 15; ii++) {
			int curinx = txt.lastIndexOf('\n', index - txt.length() - 1);

			if (curinx == -1)
				break;	// nicht so wahrscheinlich
			
			index = curinx;
		}

		_pdfLatexErrorText = txt.right(txt.length() - index);
	}
	else {
		_pdfLatexErrorText.clear();
	}

	qCDebug(logger) << "compile file done in [msec]:" << dbgTimer.elapsed();

	return res;
}

LatexCompilerWorker::Result 
	LatexCompilerWorker::queryPdfInfo(const QString& outPath, const QString& file)
{
	QElapsedTimer dbgTimer;
	dbgTimer.start();

	qCInfo(logger) << "request pdf info:" << file;

	const char* exefile = "pdfinfo.exe";

	QStringList args;
	args << file;

	QProcess process;
	process.setWorkingDirectory(outPath);
	process.setArguments(args);
	process.setProgram(exefile);


	Result res = exec_process(&process);

	if (res == SuperXiVollGeil) {
		// spllit output by linefeeds
		QString processresults = process.readAllStandardOutput();
		QStringList listofInfo = processresults.split("\r\n");

		_pdfInfo.clear();

		foreach(QString line, listofInfo) {
			int trenner = line.indexOf(":");
			if (trenner <= 0)
				break;
			QString keyString = line.left(trenner);
			QString value = line.right(trenner).simplified();
			_pdfInfo.insert(keyString, value);
		}
	}

	qCDebug(logger) << "request pdfinfo done in [msecs]:" << dbgTimer.elapsed();

	return res;
}

QPixmap LatexCompilerWorker::createPreviewPage(const QString& outPath, const QString& pdfFile, int pageNum)
{
	QElapsedTimer dbgTimer;
	dbgTimer.start();
	QPixmap ret;

	qCInfo(logger) << "create preview image:" << pdfFile << ", pageNum=" << pageNum;

	const char* exefile = "pdftoppm.exe";

	QString args;
	args = QString("-f %1 -singlefile %2 ") .arg(pageNum) .arg(pdfFile);

	QProcess process;
	process.setWorkingDirectory(outPath);
	process.setNativeArguments(args);
	process.setProgram(exefile);

	Result res = exec_process(&process);
		
	qCDebug(logger) << "create preview image: process" << exefile 
		<< " done in [msecs]:" << dbgTimer.elapsed();
	
	if (res== SuperXiVollGeil) {
		bool ok = ret.loadFromData(process.readAllStandardOutput());
	}

	qCDebug(logger) << "create preview image in [msecs]:" << dbgTimer.elapsed();

	return ret;
}

LatexCompilerWorker::Result LatexCompilerWorker::exec_process(QProcess* process, int msectimout)
{
	process->start();

	if (process->error() == QProcess::FailedToStart) {
		qCCritical(logger) << "could noot start " << process->program()
			<< ", maybe missing Mitex installation or Path variable";
		return DasGibtEsNicht;
	}

	if (!process->waitForFinished(msectimout)) {
		qCCritical(logger) << "timeout for waiting " << process->program() << " done";
		return ZeitUeberschreitung;
	}

	int ret = process->exitCode();

	if (ret != 0) {
		qCCritical(logger) << "pdf preview generator did exit with an error: exit Code=" << ret;
		return DasIstScheisse;
	}

	return SuperXiVollGeil;
}

void LatexCompilerWorker::emitError(QString& text, const QString& details /*= QString()*/)
{
	_lastErrorText = text;
	qCDebug(logger) << "emitError: text=" << text << ", details=" << details;
	emit buildError(text, details);
}

bool LatexCompilerWorker::errorPresent() const
{
	return (_lastErrorText.length() > 0);
}

bool LatexCompilerWorker::commandPending()
{
	QMutexLocker l(&_mutex);
	return (_currentCode.length() > 0);
}

} // namespace