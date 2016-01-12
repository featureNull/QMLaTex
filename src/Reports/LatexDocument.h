#pragma once

#include "LatexCodeBlock.h"

#include <QObject>
#include <QString>
#include <QUrl>
#include <QList>
#include <QQmlListProperty>
#include <QTimer>
#include <QLoggingCategory>

namespace Reports {


/**
 * @brief reprensents a  latex tex file
 */
class LatexDocument : public QObject
{
	Q_OBJECT

	/** single code blocks (default property) */
	Q_PROPERTY(QQmlListProperty<Reports::LatexCodeBlock> blocks READ blocks)
	Q_CLASSINFO("DefaultProperty", "blocks")

	Q_PROPERTY(QQmlListProperty<Reports::LatexCodeBlock> preamble READ preamble)

	/** font size in pts */
	Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)

	/** prtrait or ladnscape */
	Q_PROPERTY(Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)

	/** page size */
	Q_PROPERTY(PaperSize paperSize READ paperSize WRITE setPaperSize NOTIFY paperSizeChanged)

	/** name of the document */
	Q_PROPERTY(QString docName READ docName WRITE setDocName NOTIFY docNameChanged)

public:
	enum Orientation {
		Portrait = 	0,	///< the page's height is greater than its width.
		Landscape =	1	///< the page's width is greater than its heigh
	};
	Q_ENUMS(Orientation);

	enum PaperSize {
		A3 = 0,			///< 297 x 420 mm
		A4 = 1			///< 210 x 297 mm, 8.26 x 11.69 inches
	};
	Q_ENUMS(PaperSize);

public:
	explicit LatexDocument(QObject* parent = NULL);
	~LatexDocument();

	/** append code */
	Q_INVOKABLE void append(Reports::LatexCodeBlock* block);
	Q_INVOKABLE void clear();

	/** code blocks between \\begin{document} and \\end{document} */
	QQmlListProperty<LatexCodeBlock> blocks();

	/** code blocks between \\d\\begin{document} and \\end{document} */
	QQmlListProperty<LatexCodeBlock> preamble();

	void setFontSize(int value);
	int fontSize() const;

	void setOrientation(Orientation);
	Orientation orientation() const;

	void setPaperSize(PaperSize ps);
	PaperSize paperSize() const;
	
	void setDocName(QString docName);
	QString docName() const;

	/** brief latex quellcode for the whole document */
	QString code() const;

signals:
	void titleChanged();
	void fontSizeChanged();
	void orientationChanged();
	void paperSizeChanged();
	void docNameChanged();

	/** the document has changed in some form */
	void codeChanged();
private:
	QString documentclassCode() const;
	QStringList usedPackages() const;

	// stuff around qmllistproperty
	static void appendBlock(QQmlListProperty<LatexCodeBlock> *list, LatexCodeBlock*block);
	static int blockCount(QQmlListProperty<LatexCodeBlock>*list);
	static LatexCodeBlock* blockAt(QQmlListProperty<LatexCodeBlock> *list, int i);
	static void blocksClear(QQmlListProperty<LatexCodeBlock> *list);

	static void appendPreamble(QQmlListProperty<LatexCodeBlock> *list, LatexCodeBlock*block);
	static int preambleCount(QQmlListProperty<LatexCodeBlock>*list);
	static LatexCodeBlock* preambleAt(QQmlListProperty<LatexCodeBlock> *list, int i);
	static void preambleClear(QQmlListProperty<LatexCodeBlock> *list);

	QLoggingCategory logger;
	int _fontSize;
	Orientation _orientation;
	PaperSize _paperSize;
	QString _docName;
	QList<LatexCodeBlock*> _blocks;
	QList<LatexCodeBlock*> _preamble;
};

} // namespace
