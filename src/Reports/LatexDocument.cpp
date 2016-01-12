#include "LatexDocument.h"

#include <QDebug>
#include <QDir>
#include <QTextStream>

namespace Reports {

LatexDocument::LatexDocument(QObject* parent) 
	: QObject(parent), logger("Latex.Document")
{
	_fontSize = 12;
	_orientation = Portrait;
	_paperSize = A4;
	_docName = "report";
}

LatexDocument::~LatexDocument()
{
}

void LatexDocument::append(LatexCodeBlock* block)
{

}

void LatexDocument::clear()
{
}

QString LatexDocument::code() const
{
	QString code;
	QTextStream lcs(&code);
	QString lf = "\r\n";

	lcs << lf << documentclassCode();

	foreach (QString cur, usedPackages()) {
		lcs << lf << "\\usepackage" << cur;
	}

	foreach(LatexCodeBlock* cur, _preamble) {
		if (cur->isEnabled()) {
			lcs << lf << cur->code() << lf;
		}
	}

	lcs << lf << "\\begin{document}";

	foreach(LatexCodeBlock* cur, _blocks) {
		if (cur->isEnabled()) {
			lcs << lf << cur->code() << lf;
		}
	}

	lcs << lf << "\\end{document}";

	return code;
}

QQmlListProperty<LatexCodeBlock> LatexDocument::blocks()
{
	return QQmlListProperty<LatexCodeBlock>(this, 0,  
		&appendBlock, &blockCount,&blockAt, &blocksClear);
}

QQmlListProperty<LatexCodeBlock> LatexDocument::preamble()
{
	return QQmlListProperty<LatexCodeBlock>(this, 0,  
		&appendPreamble, &preambleCount,&preambleAt, &preambleClear);
}

void LatexDocument::setFontSize(int value)
{
	_fontSize = value;
	emit codeChanged();
	emit fontSizeChanged();
}

int LatexDocument::fontSize() const
{
	return _fontSize;
}

void LatexDocument::setOrientation(Orientation o)
{
	_orientation = o;
	/// @todo wording
	emit codeChanged();
	emit orientationChanged();
}

LatexDocument::Orientation LatexDocument::orientation() const
{
	return _orientation;
}

void LatexDocument::setPaperSize(PaperSize ps)
{
	_paperSize = ps;
	emit codeChanged();
	emit paperSizeChanged();
}

LatexDocument::PaperSize LatexDocument::paperSize() const
{
	return _paperSize;
}


void LatexDocument::setDocName(QString docName)
{
	if (docName == "") {
		return;
	}
	_docName = docName;
	emit docNameChanged();
}

QString LatexDocument::docName() const
{
	return _docName;
}

QString LatexDocument::documentclassCode() const
{
	const char* ps = (_paperSize == A3) ? "a3paper" : "a4paper";
	const char* o = (_orientation == Landscape) ? "landscape" : "portrait";
	QString ret;

	ret = QString("\\documentclass[%1,%2pt,%3]{article}") .arg(ps) .arg(_fontSize) .arg(o);
	return ret;
}

QStringList LatexDocument::usedPackages() const
{
	QStringList ret;

	foreach(LatexCodeBlock* cur, _preamble) {
		QStringList packages = cur->packegesWithChilds();

		foreach (QString cur,  packages) {
			QString trimmed = cur.simplified();

			if (!ret.contains(trimmed)) {
				ret << trimmed;
			}
		} // foreach package
	}// foreach LatexCodeBlock

	foreach(LatexCodeBlock* cur, _blocks) {
		QStringList packages = cur->packegesWithChilds();

		foreach (QString cur,  packages) {
			QString trimmed = cur.simplified();

			if (!ret.contains(trimmed)) {
				ret << trimmed;
			}
		} // foreach package
	}// foreach LatexCodeBlock

	return ret;
}

void LatexDocument::appendBlock(QQmlListProperty<LatexCodeBlock> *list, LatexCodeBlock *block)
{
	LatexDocument *doc = qobject_cast<LatexDocument*>(list->object);
	if(doc && block) {
		connect(block,  SIGNAL(changed()), doc, SIGNAL(codeChanged()));
		doc->_blocks.append(block);
	}
}

int LatexDocument::blockCount(QQmlListProperty<LatexCodeBlock>*list)
{
	LatexDocument *doc = qobject_cast<LatexDocument*>(list->object);
	if(doc) {
		return doc->_blocks.count();
	}
	return 0;
}

LatexCodeBlock* LatexDocument::blockAt(QQmlListProperty<LatexCodeBlock> *list, int i)
{
	LatexDocument *doc = qobject_cast<LatexDocument*>(list->object);
	if(doc) {
		return doc->_blocks.at(i);
	}
	return nullptr;
}

void LatexDocument::blocksClear(QQmlListProperty<LatexCodeBlock> *list)
{
	LatexDocument *doc = qobject_cast<LatexDocument*>(list->object);
	if(doc) {
		while(doc->_blocks.count() > 0) {
			QObject* obj = doc->_blocks.takeLast();
			obj->disconnect(doc);
		}
	}
}

void LatexDocument::appendPreamble(QQmlListProperty<LatexCodeBlock> *list, LatexCodeBlock*block)
{
	LatexDocument *doc = qobject_cast<LatexDocument*>(list->object);
	if(doc && block) {
		connect(block,  SIGNAL(changed()), doc, SIGNAL(codeChanged()));
		doc->_preamble.append(block);
	}
}

int LatexDocument::preambleCount(QQmlListProperty<LatexCodeBlock>*list)
{
	LatexDocument *doc = qobject_cast<LatexDocument*>(list->object);
	if(doc) {
		return doc->_preamble.count();
	}
	return 0;
}

LatexCodeBlock* LatexDocument::preambleAt(QQmlListProperty<LatexCodeBlock> *list, int i)
{
	LatexDocument *doc = qobject_cast<LatexDocument*>(list->object);
	if(doc) {
		return doc->_preamble.at(i);
	}
	return nullptr;
}

void LatexDocument::preambleClear(QQmlListProperty<LatexCodeBlock> *list)
{
	LatexDocument *doc = qobject_cast<LatexDocument*>(list->object);
	if(doc) {
		while(doc->_blocks.count() > 0) {
			QObject* obj = doc->_preamble.takeLast();
			obj->disconnect(doc);
		}
	}
}

} // namespace