#pragma once

#include "LatexCodeBlock.h"

#include <QThread>
#include <QString>
#include <QMutex>
#include <QWaitCondition>
#include <QProcess>
#include <QPixmap>

#include <QLoggingCategory>

namespace Reports {

/**
 * @brief workerthread which is used by the compiler
 * @sa Reports::LatexCompiler
 */
class LatexCompilerWorker : public QThread
{
	Q_OBJECT

public:
	explicit LatexCompilerWorker(QObject *parent = nullptr);
	~LatexCompilerWorker();

	/** run a build */
	void startBuild(const QString& outPath, const QString& code, const QString& docName);
	
signals:
	/** build is runnning */
	void buildStarted();

	/** build without errors 
	  */
	void buildSuccess();

	/** build with some errors */
	void buildError(const QString& title, const QString& details);

	/** build finished without errors */
	void buildTerminated();

	/** emit information about the document */
	void pdfInfoReaded(const QMap<QString, QString>& textmap);

	/** is emmited if the preview is generated*/
	void startCreatingPreviews();

	/** emits the preview image, [pagenumber], Pixmap */
	void previewPageGenerated(int page, const QPixmap& pixmap);
	
private:
	/** 
	  * @TODO make the error codes englih
	  */
	enum Result {
		SuperXiVollGeil,	///< everything well
		DasIstScheisse,		///< not so well
		DasGibtEsNicht,
		ZeitUeberschreitung,
		DasDuerftIhrNichtAendern
	};

protected:
	virtual void run() override;
	void pollNext(QString* outPath, QString* code, QString* DocName, bool* terminate);

	void build(const QString& outPath, const QString& code, const QString& docName);
	Result compileFile(const QString& outPath, const QString& file);
	Result queryPdfInfo(const QString& outPath, const QString& file);
	
//	void createPreviews(const QString& outPath);
	QPixmap createPreviewPage(const QString& outPath, const QString& pdfFile, int pageNum);

private:
	void emitError(QString& errorText, const QString& details = QString());
	bool errorPresent() const;
	bool commandPending();

	Result exec_process(QProcess* process, int msectimout = 10000);

	QLoggingCategory logger;

	QMutex _mutex;
	QWaitCondition _waitCond;
	// data which is mutex protected
	QString _currentCode;
	QString _currentOutPath;
	QString  _docName;
	bool _terminate;

	// worker status members
	QString _lastErrorText;
	QString _pdfLatexErrorText;
	QMap<QString, QString> _pdfInfo;
};

} // namespace
