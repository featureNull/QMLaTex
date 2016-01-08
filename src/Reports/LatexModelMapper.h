#pragma once

#include "LatexCodeBlock.h"

#include <QObject>
#include <QMap>
#include <QPair>
#include <QAbstractItemModel>
#include <QLoggingCategory>


namespace Reports {

/**
 * @brief Mapped ein Qt TableModel auf latex code zu ueberfuehren
 */
class LatexModelMapper : public LatexCodeBlock
{
	Q_OBJECT
	
	/** daten model, aus denen die werte gelesen werden
	  * @note idealerweise sollte dieses Modell auch IQmlSchemaPresenter implementieren 
	  */
	Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)

	/** rollen die man sehen will, bei einer leeren liste werden alle roles angezeigt */
	Q_PROPERTY(QList<int> enabledRoles READ enabledRoles WRITE setEnabledRoles NOTIFY enabledRolesChanged)

	/** trenner zwischen columns default \c &. */
	Q_PROPERTY(QString seperator READ seperator WRITE setSeperator NOTIFY seperatorChanged)

	/** string vor einem Datensatz, default: nix */
	Q_PROPERTY(QString rowStartMark READ rowStartMark WRITE setRowStartMark NOTIFY rowStartMarkChanged)
	
	/** string am ende eines Datensatzes, deafult: "\\\\\r\n" */
	Q_PROPERTY(QString rowEndMark READ rowEndMark WRITE setRowEndMark NOTIFY rowEndMarkChanged)

public:
	explicit LatexModelMapper(QObject* parent = NULL);
	~LatexModelMapper();
		
	/** daten model, aus denen die werte gelesen werden, muss vom type QAbstractTableModel sein */
	void setModel(QAbstractItemModel* model);
	QAbstractItemModel* model() const;

	void setEnabledRoles(const QList<int>& list);
	QList<int> enabledRoles() const;
	
	/** trenner zwischen columns default \c &. */
	void setSeperator(const QString& value);
	QString seperator() const;

	void setRowStartMark(const QString& value);
	QString rowStartMark() const;
	
	void setRowEndMark(const QString& value);
	QString rowEndMark() const;
	
signals:
	void modelChanged();
	void enabledRolesChanged();
	void seperatorChanged();
	void rowStartMarkChanged();
	void rowEndMarkChanged();

private slots:
	void tryBuild();
	void onDataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>& roles);

private:
	QString createSingleRow(const QList<int>& roles, int row) const;
	QList<int> determineRoles() const;

private:
	QLoggingCategory logger;

	QList<int> _enabledRoles;
	QAbstractItemModel* _model;

	QString _seperator;
	QString _rowStartMark;
	QString _rowEndMark;
};

} // namespace
