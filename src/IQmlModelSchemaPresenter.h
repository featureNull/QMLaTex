#pragma once

#include <QString>
#include <QModelIndex>


/**
 * @brief Interface fuer das man vom ui dynamisch das modell mit den rollen
 * abfragen kann
 * @note brauchen tuts das zB fuer den csv export
 */
class IQmlModelSchemaPresenter
{
public:

	IQmlModelSchemaPresenter() {}
	virtual ~IQmlModelSchemaPresenter() {}

	/** @brief RoleNummern ausfsteigend sortiert */
	virtual QList<int> roleNums() const = 0;

	/** @brief sw interner name einer rolle */
	virtual QString roleName(int role) const = 0;

	/** @brief human readable text fuer den header */
	virtual QString roleTitleName(int role) const = 0;

	/** @brief formatierter text mit nachkommastellen etc.. */
	virtual QString formatedData(const QModelIndex& index, int role) const  = 0;
};
