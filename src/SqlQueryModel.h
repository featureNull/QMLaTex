#pragma once
#include <QSqlQueryModel>

/**
 * @brief A simple model to access database tables
**/
class SqlQueryModel : public QSqlQueryModel
{
	Q_OBJECT

public:
	explicit SqlQueryModel(QObject *parent = 0);

	/** @brief Get a List of user role numbers **/
	Q_INVOKABLE int roleNum(QString colName);
	/** @brief Get a List of user role numbers **/
	Q_INVOKABLE QList<int> roleNums();
	/** @brief Get the name for a speciefied role number **/
	Q_INVOKABLE QString roleTitleName(int key);

	/** @ brief This method set a query to select data and generates
	  * new role name according to the database columns.
	  **/
	void setQuery(const QString &query, const QSqlDatabase &db = QSqlDatabase());
	void setQuery(const QSqlQuery &query);
	QVariant data(const QModelIndex &index, int role) const;

	QHash<int, QByteArray> roleNames() const {	return m_roleNames;	}

private:
	void generateRoleNames();
	QHash<int, QByteArray> m_roleNames;
	QHash<QString, int> m_nameRoles;
};
