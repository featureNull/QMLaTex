#pragma once
#include <QSqlQueryModel>

class SqlQueryModel : public QSqlQueryModel
{
	Q_OBJECT

public:
	explicit SqlQueryModel(QObject *parent = 0);

	Q_INVOKABLE QList<int> roleNums();
	Q_INVOKABLE QString roleTitleName(int key);

	void setQuery(const QString &query, const QSqlDatabase &db = QSqlDatabase());
	void setQuery(const QSqlQuery &query);
	QVariant data(const QModelIndex &index, int role) const;

	QHash<int, QByteArray> roleNames() const {	return m_roleNames;	}

private:
	void generateRoleNames();
	QHash<int, QByteArray> m_roleNames;
};
