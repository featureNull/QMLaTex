#pragma once

#include <QObject>
#include <QQmlListProperty>


namespace Reports {

// class forward decls
class Document;

/**
 * @brief Baseclass for latex code
 * @details represents a code snipped in latex
 */
class LatexCodeBlock : public QObject
{
	Q_OBJECT

	/** single code blocks (default property) */
	Q_PROPERTY(QQmlListProperty<Reports::LatexCodeBlock> childs READ childs)
	Q_CLASSINFO("DefaultProperty", "childs")

	/** should the code actually produce an output */
	Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)

	/** what packages are needed? Has the form \code [option]{package} \endcode */
	Q_PROPERTY(QStringList packages READ packages WRITE setPackages NOTIFY packagesChanged)

	/** latex source code of this LatexCodeBlock
	  * @sa childCode
	  */
	Q_PROPERTY(QString code READ code WRITE setCode NOTIFY codeChanged)

	/** Code of children. The Use have to insert the childCode own its own to the parent code
	  */
	Q_PROPERTY(QString childCode READ childCode NOTIFY childChanged)

public:
	explicit LatexCodeBlock(QObject* parent = NULL);
	
	/** Escapes all characters of str so that they no longer have any special meaning when 
	  * used with latex, and returns the escaped string
	  * @sa http://tex.stackexchange.com/questions/34580/escape-character-in-latex
	  */
	Q_INVOKABLE QString escape(const QString& code) const;

	void setEnabled(bool);
	bool isEnabled() const;

	void setPackages(const QStringList& list);
	QStringList packages() const;

	/** @brief latex source code  */
	void setCode(const QString &code);
	QString code() const;

	QString childCode() const;

	/** */
	QQmlListProperty<LatexCodeBlock> childs();

	/** internal use packages from this object and from childs*/
	QStringList packegesWithChilds() const;

signals:
	void enabledChanged();
	void codeChanged();
	void packagesChanged();

	// is always emitted if anything is changed
	void changed();

	// is emmited if a child is changed
	void childChanged();

private:
	// stuff around qmllistproperty
	static void appendChild(QQmlListProperty<LatexCodeBlock> *list, LatexCodeBlock*block);
	static int childCount(QQmlListProperty<LatexCodeBlock>*list);
	static LatexCodeBlock* childAt(QQmlListProperty<LatexCodeBlock> *list, int i);
	static void childsClear(QQmlListProperty<LatexCodeBlock> *list);

	QString _code;
	bool _isEnabled;
	QStringList _packages;
	QList<LatexCodeBlock*> _childs;
};

} // namespace
