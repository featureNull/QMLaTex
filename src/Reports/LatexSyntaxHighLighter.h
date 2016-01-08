#pragma once

#include <QVector>
#include <QString>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>


// class forward decl
class QQuickTextDocument;

namespace Reports {

/**
 * @brief sehr sher simpler syntax highlighter fuer latex
 */
class LatexSyntaxHighLighter : public QSyntaxHighlighter
{
    Q_OBJECT

	/** text dokument, must be type of 	QQuickTextDocument
	  * @note getter und setter clashen mit basisklasse 
	  */
	Q_PROPERTY(QObject* quickTextDocument READ quickTextDocument
			   WRITE setQuickTextDocument NOTIFY quickTextDocumentChanged)

	/** syntax highlighting for latex or porno */
	Q_PROPERTY(SyntaxMode syntaxMode READ syntaxMode WRITE setSyntaxMode NOTIFY syntaxModeChanged)

public:
	/**
	 * @brief highligting mode 
	 */
	enum SyntaxMode {
		LatexSyntax,		///< latex code
		BadWordsSyntax		///< zur belustigung von sarah schimpfwoeter
	};
	Q_ENUMS(SyntaxMode);

public:

    // mysterioeses verhalten in qml (bug in QSyntaxHighlighter constructore parent darf nicht null sein)
	LatexSyntaxHighLighter();
	
	void setQuickTextDocument(QObject*);
	QObject* quickTextDocument() const;

	void setSyntaxMode(SyntaxMode m);
	SyntaxMode syntaxMode() const;
	
signals:
	void quickTextDocumentChanged();
	void syntaxModeChanged();
	
protected:
    void highlightBlock(const QString &text) override;

	/** liest aus einer datei line by line woerter */
	static QStringList readKeyWordsFromTextFile(const QString& fname);

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
	
    QVector<HighlightingRule> _latexRules;
	QVector<HighlightingRule> _badWordRules;

	QQuickTextDocument* _quickdoc;
	SyntaxMode _syntaxMode;
};

}