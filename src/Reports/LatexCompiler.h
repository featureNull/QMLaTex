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
 * @brief Starts the latex Compiler
 * @details Motivation is to generate from dynamic data a .tex file
	and generate a pdf document. 
 *
 * The software is tested under windows with MikTex distribution.
 * <h3>Concept</h3>
 * with \code pdflatex.exe \endcode a pdf document is generated from source code \n
 * with \code pdfinfo.exe \endcode pdf information is retrieved \n
 * with \code pdftoppm.exe \endcode to generate a jpg image from pdf \n
 * The preview for QML is provided as jpg image 
 * @note LatexBackend because of temporary files not multithread save. It is 
 * also not save if LatexBackend is instanciated more than once
 * @note the actuall work is done by LatexCompilerWorker
 *
 * @attention it is not tested under linux and may fail to run
 * @sa http://miktex.org/download
 */
class LatexCompiler : public QObject
{
	Q_OBJECT

	/* the document to compile */
	Q_PROPERTY(Reports::LatexDocument* document READ document WRITE setDocument NOTIFY documentChanged)

	/** should the compiler run automatically if the document is chaned or manually */
	Q_PROPERTY(CompileMode compileMode READ compileMode WRITE setCompileMode NOTIFY compileModeChanged)

	
	/** time to start compiler, after document change [msecs]
	  * @note only for autocompile mode
	  */
	Q_PROPERTY(int compileLatency READ compileLatency WRITE setCompileLatency NOTIFY compileLatencyChanged)

	/** number of pages after compilation */
	Q_PROPERTY(int numOfPages READ numOfPages NOTIFY buildTerminated)

	/** file size in bytes */
	Q_PROPERTY(int fileSize READ fileSize NOTIFY buildTerminated)

	/** the pdf version */
	Q_PROPERTY(QString pdfVersion READ pdfVersion NOTIFY buildTerminated)

	Q_PROPERTY(bool busy READ isBusy NOTIFY busyChanged)

	/** @brief set the output path for the document 
	  * @ details the string can be url encoded or the
	  *	filename with slashes /(backslash need to be escaped \\)
	  **/
	Q_PROPERTY(QString outPath READ outPath WRITE setOutPath NOTIFY outPathChanged)

public:
	/** 
	 * build automatic new when something changed 
	 */
	enum CompileMode {
		ManualCompile,	///< compile with manual trigger \code compile \endcode
		AutoCompile		///< compile if doc is chaned
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
	
	void setOutPath (QString outPath);
	QString outPath() const;


public slots:
	void startCompile();

signals:
	/** build is runnning **/
	void buildStarted();		

	/** build without errors **/
	void buildSuccess();

	/** build with some errors */
	void buildError(const QString& errorText, const QString& detailedText);

	/** build finished without errors */
	void buildTerminated();

	/** is emmited if the preview is generated*/
	void startCreatingPreviews();

	/** emits the preview image, [pagenumber], Pixmap */
	void previewPageGenerated(int page);

	/** emits when the path is changed **/
	void outPathChanged();

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
