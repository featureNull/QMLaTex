#pragma once

#include <QObject>
#include <QQmlListProperty>


namespace Reports {

// class forward decls
class Document;

/**
 * @brief Basis klasse fuer latex code
 * @details reprsaentiert einen code snipsel in latex. Zu verwnden mit 
 */
class LatexCodeBlock : public QObject
{
	Q_OBJECT

	/** einzelne code bloecke (default property) */
	Q_PROPERTY(QQmlListProperty<Reports::LatexCodeBlock> childs READ childs)
	Q_CLASSINFO("DefaultProperty", "childs")

	/** soll der code tatsaechlich eine ausgabe produzieren */
	Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)

	/** was wird dazu gebraucht in der form \code [option]{package} \endcode */
	Q_PROPERTY(QStringList packages READ packages WRITE setPackages NOTIFY packagesChanged)

	/** latex quellcode von diesem LatexCodeBlock
	  * @sa childCode
	  */
	Q_PROPERTY(QString code READ code WRITE setCode NOTIFY codeChanged)

	/** code der kinder der user muss sich selbst drum kuemmern. childCode ist nicht in code
	  * eingewebt
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

	/** @brief latex quellcode  */
	void setCode(const QString &code);
	QString code() const;

	QString childCode() const;

	/** */
	QQmlListProperty<LatexCodeBlock> childs();

	/** internal use packeges von dieem und von den kindern */
	QStringList packegesWithChilds() const;

signals:
	void enabledChanged();
	void codeChanged();
	void packagesChanged();

	// wird immer emitiert, wenn irgendwas im code sich aendert
	void changed();

	// wird emittiert, wenn sich ein kind aendert
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
