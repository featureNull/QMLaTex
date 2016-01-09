#include "SqlQueryModel.h"
#include <QSqlRecord>
#include <QSqlField>

SqlQueryModel::SqlQueryModel(QObject *parent) :
	QSqlQueryModel(parent)
{
}

QList<int> SqlQueryModel::roleNums()
{
	return roleNames().keys();
}

QString SqlQueryModel::roleTitleName(int key)
{
	return roleNames().value(key);
}

void SqlQueryModel::setQuery(const QString &query, const QSqlDatabase &db)
{
	QSqlQueryModel::setQuery(query, db);
	generateRoleNames();
}

void SqlQueryModel::setQuery(const QSqlQuery & query)
{
	QSqlQueryModel::setQuery(query);
	generateRoleNames();
}

void SqlQueryModel::generateRoleNames()
{
	m_roleNames.clear();
	for( int i = 0; i < record().count(); i ++) {
		m_roleNames.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
	}
}

QVariant SqlQueryModel::data(const QModelIndex &index, int role) const
{
	QVariant value;

	if(role < Qt::UserRole) {
		value = QSqlQueryModel::data(index, role);
	}
	else {
		int columnIdx = role - Qt::UserRole - 1;
		QModelIndex modelIndex = this->index(index.row(), columnIdx);
		value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
	}
	return value;
}
