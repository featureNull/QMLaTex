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
 * @brief workerthread der den compiler bedient
 * @sa Reports::LatexCompiler
 */
class LatexCompilerWorker : public QThread
{
	Q_OBJECT

public:
	explicit LatexCompilerWorker(QObject *parent = nullptr);
	~LatexCompilerWorker();

	/** einen build anstassen */
	void startBuild(const QString& outPath, const QString& code);
	
signals:
	/** build lauft */
	void buildStarted();

	/** build wurde ohne fehler durchgefuehrt 
	  * @param preview sind die vorschau images (der namespace ist notwendig ueber threads)
	  */
	void buildSuccess();

	/** build hat einen errror getan */
	void buildError(const QString& title, const QString& details);

	/** build wurde mit oder ohne fehler fertig */
	void buildTerminated();

	/** emittiert info ueber das dok */
	void pdfInfoReaded(const QMap<QString, QString>& textmap);

	/** wird emmitiert, wenn die previews neu erstellt werden */
	void startCreatingPreviews();

	/** emittiert eine liste von vorschau images, [seitennnummer], Pixmap */
	void previewPageGenerated(int page, const QPixmap& pixmap);

private:
	/** 
	  * schwyzerischer error. In respect to Mr Hirzel sind fehler hier positiv, 
	  * obwohl ein fehler wirklich etwas negatives ist
	  */
	enum Result {
		SuperXiVollGeil,	///< mit freude verkuenden, eine Srechpause zwische SuperXi und VollGeil
		DasIstScheisse,		///< mit gesenktem Kopf zusammendhaengend auszusprechen
		DasGibtEsNicht,
		ZeitUeberschreitung,
		DasDuerftIhrNichtAendern
	};

protected:
	virtual void run() override;
	void pollNext(QString* outPath, QString* code, bool* terminate);

	void build(const QString& outPath, const QString& code);
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
	// daten die wo ueber mutex geschuetzt werden sollten
	QString _currentCode;
	QString _currentOutPath;
	bool _terminate;

	// worker status mebers
	QString _lastErrorText;
	QString _pdfLatexErrorText;
	QMap<QString, QString> _pdfInfo;
};

} // namespace
