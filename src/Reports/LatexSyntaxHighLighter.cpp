#include <QTextStream>
#include <QQuickTextDocument>

#include "LatexSyntaxHighLighter.h"

namespace Reports {

LatexSyntaxHighLighter::LatexSyntaxHighLighter()
    : QSyntaxHighlighter((QTextDocument*)nullptr)
{
	HighlightingRule rule;
	QTextCharFormat keywordFormat;
	QTextCharFormat commentFormat;
	QTextCharFormat badWordsFormat;

	_quickdoc = nullptr;
	_syntaxMode = LatexSyntax;

	keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

	//
	// long latex commands
	//
	QStringList keywords = readKeyWordsFromTextFile(":/res/latex_commands.txt");
    foreach (const QString& kw, keywords) {
		QString pattern = 
			QStringLiteral("\\\\") 
			+ QStringLiteral("\\b") 
			+ QRegularExpression::escape(kw)
			+ QStringLiteral("\\b");

        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        _latexRules.append(rule);
    }

	//
	// short latex stuff
	//
	QStringList shortcmds;
	shortcmds << "\\;" << "\\:" << "\\!" << "\\-" << "\\=" << "\\>" << "\\<" << "\\+" << "\\'"
		<< "\\`" << "\\|" << "\\(" << "\\)" << "\\[" << "\\]";

	foreach (const QString& kw, shortcmds) {
		QString pattern = QRegularExpression::escape(kw);
		rule.pattern = QRegularExpression(pattern);
		rule.format = keywordFormat;
		_latexRules.append(rule);
	}

	//
	// comment line
	//
	commentFormat.setForeground(Qt::darkGray);
    rule.pattern = QRegularExpression("%[^\n]*");
    rule.format = commentFormat;
    _latexRules.append(rule);

	//
	// zur bespassung von Sarah bad words
	//
	badWordsFormat.setForeground(Qt::red);
	badWordsFormat.setFontStrikeOut(true);

	keywords = readKeyWordsFromTextFile(":/res/bad_words.txt");
	foreach (const QString& kw, keywords) {
		QString pattern = QRegularExpression::escape(kw);

		rule.pattern = QRegularExpression(pattern);
		rule.format = badWordsFormat;
		_badWordRules.append(rule);
	}
}

void LatexSyntaxHighLighter::setQuickTextDocument(QObject* doc)
{
	if (doc) {
		_quickdoc =  qobject_cast<QQuickTextDocument*>(doc);
		Q_ASSERT_X(_quickdoc != nullptr, Q_FUNC_INFO, 
			"document must be type of QQuickTextDocument");
		setDocument(_quickdoc->textDocument());
	}
	else {
		_quickdoc = nullptr;
		setDocument(nullptr);
	}

	emit quickTextDocumentChanged();
}

QObject* LatexSyntaxHighLighter::quickTextDocument() const
{
	return _quickdoc;
}

void LatexSyntaxHighLighter::setSyntaxMode(SyntaxMode m)
{
	_syntaxMode = m;
	rehighlight();
	emit syntaxModeChanged();
}

LatexSyntaxHighLighter::SyntaxMode LatexSyntaxHighLighter::syntaxMode() const
{
	return _syntaxMode;
}

void LatexSyntaxHighLighter::highlightBlock(const QString &text)
{
	const QVector<HighlightingRule>& rules =
		(_syntaxMode == LatexSyntax) ? _latexRules : _badWordRules;

	foreach (const HighlightingRule &rule, rules) {
		QRegularExpression expression(rule.pattern);
		QRegularExpressionMatchIterator i = expression.globalMatch(text);

		while (i.hasNext()) {
			QRegularExpressionMatch match = i.next();
			// use match
			int index = match.capturedStart();
			int length = match.capturedLength();
			setFormat(index, length, rule.format);
		}
	}
}

QStringList LatexSyntaxHighLighter::readKeyWordsFromTextFile(const QString& fname)
{
	QStringList ret;

	QFile file(fname);

	if (file.open(QIODevice::ReadOnly)) {
		QTextStream in(&file);

		while (!in.atEnd())	{
			QString line = in.readLine();
			ret << line.simplified();
		}
	}

	return ret;
}

}