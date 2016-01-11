#pragma once

#include "LatexCodeBlock.h"

#include <QObject>
#include <QMap>
#include <QPair>
#include <QAbstractItemModel>
#include <QLoggingCategory>


namespace Reports {

/**
 * @brief Mapped a Qt TableModel to latex code
 */
class LatexModelMapper : public LatexCodeBlock
{
	Q_OBJECT
	
	/** data model where data is read
	  * @note this model can implement IQmlModelSchemaPresenter
	  */
	Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)

	/** roles which should be shown, if listed is empty all roles are shown */
	Q_PROPERTY(QList<int> enabledRoles READ enabledRoles WRITE setEnabledRoles NOTIFY enabledRolesChanged)

	/** seperator between columns \c &. */
	Q_PROPERTY(QString seperator READ seperator WRITE setSeperator NOTIFY seperatorChanged)

	/** string before data line, default: nothing */
	Q_PROPERTY(QString rowStartMark READ rowStartMark WRITE setRowStartMark NOTIFY rowStartMarkChanged)
	
	/** string at end of data line, default: "\\\\\r\n" */
	Q_PROPERTY(QString rowEndMark READ rowEndMark WRITE setRowEndMark NOTIFY rowEndMarkChanged)

public:
	explicit LatexModelMapper(QObject* parent = NULL);
	~LatexModelMapper();
		
	/** data model from which data is read, have to be of type QAbstractTableModel */
	void setModel(QAbstractItemModel* model);
	QAbstractItemModel* model() const;

	void setEnabledRoles(const QList<int>& list);
	QList<int> enabledRoles() const;
	
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
