#pragma once

#include "LatexDocument.h"

#include <QString>
#include <QUrl>
#include <QList>
#include <QLoggingCategory>

namespace Reports {

// class forward decls 
class LatexCompilerWorker;

/**
 * @brief bedient den latex Compiler
 * @details Motivation ist es, aus dynamischen Datenseatzen ein .tex file zu generieren
 * und auf diesem Weg zu einem Druckbaren dokument zu kommen. 
 *
 * Als distribution wurde unter Windows die Miktex Distribution verwendet.
 * <h3>Konzept</h3>
 * mittels \code pdflatex.exe \endcode wird aus quellcode ein Pdf erstellt \n
 * mit \code pdfinfo.exe \endcode wird dem pdf anschliesend information entlockt \n
 * mit \code pdftoppm.exe \endcode wird dem pdf anschliesend information entlockt \n
 * das Preview fuer Qml wird mit jpg images bereitgestellt 
 * @note LatexBackend aufgrund von temporaeren Dateien nicht multithread save, sowie 
 * auch nicht save wenn LatexBackend oefter als einaml instanziert wird 
 * @note die eigentliche arbeit macht asynchron LatexCompilerWorker
 *
 * @attention unter linux wird das wahrscheinlich nicht funtionieren
 * @sa http://miktex.org/download
 */
class LatexCompiler : public QObject
{
	Q_OBJECT

	Q_PROPERTY(Reports::LatexDocument* document READ document WRITE setDocument NOTIFY documentChanged)

	/** soll der compiler von sich aus neu bauen, wenn sich das dokument aendert,  oder manuell */
	Q_PROPERTY(CompileMode compileMode READ compileMode WRITE setCompileMode NOTIFY compileModeChanged)

	/** wartezeit bis compiler gestartet wird, nachdem sich das dokument geaendert hat [msecs]
	  * @note nur relevant bei compileMode AutoCompile 
	  */
	Q_PROPERTY(int compileLatency READ compileLatency WRITE setCompileLatency NOTIFY compileLatencyChanged)

	/** anzahl der seiten nach compiilieren */
	Q_PROPERTY(int numOfPages READ numOfPages NOTIFY buildTerminated)

	/** datei groesse in bytes */
	Q_PROPERTY(int fileSize READ fileSize NOTIFY buildTerminated)

	/** vollsteandigkeit halber die pdf version */
	Q_PROPERTY(QString pdfVersion READ pdfVersion NOTIFY buildTerminated)

	Q_PROPERTY(bool busy READ isBusy NOTIFY busyChanged)

	Q_PROPERTY(QString outPath READ outPath CONSTANT)

public:
	/** 
	 * build automatic new when something changed 
	 */
	enum CompileMode {
		ManualCompile,	///< compilieren mit manuellen trigger \code compile \endcode
		AutoCompile		///< compilieren immer wenn sich das doc aendert 
	};
	Q_ENUM(CompileMode);

public:
	explicit LatexCompiler(QObject *parent = nullptr);
	~LatexCompiler();

	void setDocument(LatexDocument* doc);
	LatexDocument* document() const;

	void setCompileMode(CompileMode value);
	CompileMode compileMode() const;

	void setCompileLatency(int msecs);
	int compileLatency() const;

	int numOfPages() const;
	int fileSize()  const;
	QString pdfVersion() const;
	bool isBusy() const;
	QString outPath() const;

public slots:
	void startCompile();

signals:
	/** build lauft */
	void buildStarted();

	/** build wurde ohne fehler durchgefuehrt 
	  * @param preview sind die vorschau images (der namespace ist notwendig ueber threads)
	  */
	void buildSuccess();

	/** build hat einen errror getan */
	void buildError(const QString& errorText, const QString& detailedText);

	/** build wurde mit oder ohne fehler fertig */
	void buildTerminated();

	/** wird emmitiert, wenn die previews neu erstellt werden */
	void startCreatingPreviews();

	/** emittiert eine liste von vorschau images, [seitennnummer], Pixmap */
	void previewPageGenerated(int page);

	// property notifiers 
	void documentChanged();
	void compileModeChanged();
	void compileLatencyChanged();
	void busyChanged();

private slots:
	void onDocCodeChanged();

	void onBuildStarted();
	void onPdfInfoReaded(const QMap<QString, QString>& textmap);
	void onBuildTerminated();

	void onStartCreatingPreviews();
	void onPreviewPageGenerated(int page, const QPixmap& pixmap);

private:
	QLoggingCategory logger;
	
	CompileMode _compileMode;
	QMap<QString, QString> _pdfInfoMap;

	LatexDocument*_doc;
	bool _isBusy;
	QString _outPath;

	QTimer* _timer;
	LatexCompilerWorker* _worker;
};

} // namespace
