#include "LatexCodeBlock.h"
#include <QTextStream>

namespace Reports {

LatexCodeBlock::LatexCodeBlock(QObject* parent) 
	: QObject(parent)
{
	_isEnabled = true;
}

void LatexCodeBlock::setEnabled(bool value)
{
	_isEnabled = value;
	emit changed();
	emit enabledChanged();
}

bool LatexCodeBlock::isEnabled() const
{
	return _isEnabled;
}

void LatexCodeBlock::setPackages(const QStringList& list)
{
	_packages = list;
	emit changed();
	emit packagesChanged();
}

QStringList LatexCodeBlock::packages() const
{
	return _packages;
}

/** @brief latex source code  */
void LatexCodeBlock::setCode(const QString &code)
{
	_code = code;
	emit changed();
	emit codeChanged();
}

QString LatexCodeBlock::code() const
{
	return _code;
}

QString LatexCodeBlock::escape(const QString& code) const
{
	QString ret = code;
	ret.replace(QStringLiteral("\\"), QStringLiteral("\\textbackslash"));
	ret.replace(QStringLiteral("^"), QStringLiteral("\\textasciicircum"));
	ret.replace(QStringLiteral("~"), QStringLiteral("\\textasciitilde"));

	ret.replace(QStringLiteral("&"), QStringLiteral("\\&"));
	ret.replace(QStringLiteral("%"), QStringLiteral("\\%"));
	ret.replace(QStringLiteral("$"), QStringLiteral("\\$"));
	ret.replace(QStringLiteral("#"), QStringLiteral("\\#"));
	ret.replace(QStringLiteral("_"), QStringLiteral("\\_"));
	
	return ret;
}

QString LatexCodeBlock::childCode() const
{
	QString ret;
	QTextStream ts(&ret);

	foreach (LatexCodeBlock* cur, _childs) {
		if (!cur->isEnabled())
			continue;

		ts << "\r\n";
		ts << cur->code();
	}

	return ret;
}

QStringList LatexCodeBlock::packegesWithChilds() const
{
	QStringList ret;

	ret << _packages;

	foreach(LatexCodeBlock* c, _childs) {
		ret << c->packegesWithChilds();
	}

	return ret;
}

QQmlListProperty<Reports::LatexCodeBlock> LatexCodeBlock::childs()
{
	return QQmlListProperty<LatexCodeBlock>(this, 0,  
		&appendChild, &childCount,&childAt, &childsClear);
}

void LatexCodeBlock::appendChild(QQmlListProperty<LatexCodeBlock> *list, LatexCodeBlock *child)
{
	LatexCodeBlock *doc = qobject_cast<LatexCodeBlock*>(list->object);
	if(doc && child) {
		connect(child,  SIGNAL(changed()), doc, SIGNAL(childChanged()));
		doc->_childs.append(child);
	}
}

int LatexCodeBlock::childCount(QQmlListProperty<LatexCodeBlock>*list)
{
	LatexCodeBlock *doc = qobject_cast<LatexCodeBlock*>(list->object);
	if(doc) {
		return doc->_childs.count();
	}
	return 0;
}

LatexCodeBlock* LatexCodeBlock::childAt(QQmlListProperty<LatexCodeBlock> *list, int i)
{
	LatexCodeBlock *doc = qobject_cast<LatexCodeBlock*>(list->object);
	if(doc) {
		return doc->_childs.at(i);
	}
	return nullptr;
}

void LatexCodeBlock::childsClear(QQmlListProperty<LatexCodeBlock> *list)
{
	LatexCodeBlock *doc = qobject_cast<LatexCodeBlock*>(list->object);
	if(doc) {
		while(doc->_childs.count() > 0) {
			QObject* obj = doc->_childs.takeLast();
			obj->disconnect(doc);
		}
	}
}



} // namespace