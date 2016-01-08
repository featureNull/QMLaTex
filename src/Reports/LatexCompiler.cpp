#include "LatexCompiler.h"
#include "LatexCompilerWorker.h"
//#include "Application.h"
#include "ImageProvider.h"

#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QElapsedTimer>
#include <QPixmap>


#define TEX_FILENAME		"report.tex"
#define PDF_FILENAME		"report.pdf"
#define PDFINFO_FILENAME	"report.pdfinfo"

namespace Reports {

LatexCompiler::LatexCompiler(QObject* parent)
	: QObject(parent), logger("Latex.Compiler")
{
	_outPath = "C:/temp"; //TODO QDir::tempPath();
	_worker = new LatexCompilerWorker();
	_compileMode = ManualCompile;
	_doc = nullptr;
	_isBusy = false;

	// signals von dem worker wieterleiten, note dass hier ein thrad wechsel stattfindet und
	// die sw nicht mehr durch mutex geschuetzt werden muss
	// Qt::BlockingQueuedConnection ist  notwendig, dass die slots nie verwuerfelt komen
	connect(_worker, SIGNAL(buildStarted()), this,  SLOT(onBuildStarted()),
			Qt::BlockingQueuedConnection);

	connect(_worker, SIGNAL(buildSuccess()), this, SIGNAL(buildSuccess()),
			Qt::BlockingQueuedConnection);

	connect(_worker, SIGNAL(buildTerminated()), this, SLOT(onBuildTerminated()),
			Qt::BlockingQueuedConnection);

	connect(_worker, SIGNAL(buildError(const QString&, const QString&)),
			this, SIGNAL(buildError(const QString&, const QString&)),
			Qt::BlockingQueuedConnection);

	connect(_worker, SIGNAL(pdfInfoReaded(const QMap<QString, QString>&)),
			this, SLOT(onPdfInfoReaded(const QMap<QString, QString>&)),
			Qt::BlockingQueuedConnection);

	/*connect(_worker, SIGNAL(startCreatingPreviews()), 
			this,  SLOT(onStartCreatingPreviews()),
			Qt::BlockingQueuedConnection);*/

	/*connect(_worker, SIGNAL(previewPageGenerated(int, const QPixmap&)), 
			this,  SLOT(onPreviewPageGenerated(int, const QPixmap&)),
			Qt::BlockingQueuedConnection);*/

	_timer = new QTimer(this);
	_timer->setInterval(500);
	_timer->setSingleShot(true);
	connect(_timer, SIGNAL(timeout()), this, SLOT(startCompile()));
}

LatexCompiler::~LatexCompiler()
{
	delete _worker;
	// massives pdf image wieder loeschen
	//ImageProvider::instance()->clearPdfPreview();
}

void LatexCompiler::setDocument(LatexDocument* doc)
{
	if (_doc != nullptr) {
		// disconnect odl doc
		_doc->disconnect(this);
	}

	_doc = doc;
	if (_doc != nullptr) {
		connect(_doc, SIGNAL(codeChanged()), this, SLOT(onDocCodeChanged()));
	}

	// kompilieren trigern
	if (_compileMode == AutoCompile) {
		_timer->start();
	}

	emit documentChanged();
}

LatexDocument* LatexCompiler::document() const
{
	return _doc;
}

void LatexCompiler::onDocCodeChanged()
{
	if (_compileMode == AutoCompile && _doc != nullptr) {
		qCDebug(logger) << "onDocCodeChanged trigger timer";
		_timer->start();
	}
}


void LatexCompiler::setCompileMode(CompileMode value)
{
	_compileMode = value;
	emit compileModeChanged();
}

LatexCompiler::CompileMode LatexCompiler::compileMode() const
{
	return _compileMode;
}

void LatexCompiler::setCompileLatency(int msecs)
{
	_timer->setInterval(msecs);
	emit compileLatencyChanged();
}

int LatexCompiler::compileLatency() const
{
	return _timer->interval();
}

int LatexCompiler::numOfPages() const
{
	return _pdfInfoMap.value("Pages", 0).toInt();
}

int LatexCompiler::fileSize()  const
{
	return 0;
}

QString LatexCompiler::pdfVersion() const
{
	return "not implememnted";
}

bool LatexCompiler::isBusy() const
{
	return _isBusy;
}

QString LatexCompiler::outPath() const
{
	return _outPath;
}

void LatexCompiler::onBuildStarted()
{
	_isBusy = true;
	_pdfInfoMap.clear();

	emit busyChanged();
	emit buildStarted();
}

void LatexCompiler::onBuildTerminated()
{
	_isBusy = false;

	emit busyChanged();
	emit buildTerminated();
}

void LatexCompiler::onStartCreatingPreviews()
{
	ImageProvider::instance()->clearPdfPreview();
	emit startCreatingPreviews();
}

void LatexCompiler::onPreviewPageGenerated(int page, const QPixmap& pixi)
{
	ImageProvider::instance()->setPdfPreview(page, pixi);
	emit previewPageGenerated(page);
}

void LatexCompiler::startCompile()
{
	_worker->startBuild(_outPath, _doc->code());
}

void LatexCompiler::onPdfInfoReaded(const QMap<QString, QString>& textmap)
{
	_pdfInfoMap = textmap;
}

} // namespace