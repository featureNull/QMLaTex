#pragma once

#include <QString>
#include <QModelIndex>


/**
 * @brief Interface for dynamic role access in data models
 * @note currently not used
 */
class IQmlModelSchemaPresenter
{
public:

	IQmlModelSchemaPresenter() {}
	virtual ~IQmlModelSchemaPresenter() {}

	/** @brief RoleNumber sorted ascending */
	virtual QList<int> roleNums() const = 0;

	/** @brief sw internal name of a role */
	virtual QString roleName(int role) const = 0;

	/** @brief human readable text for the header */
	virtual QString roleTitleName(int role) const = 0;

	/** @brief formated text with e.g. postion after decimal point etc.. */
	virtual QString formatedData(const QModelIndex& index, int role) const  = 0;
};
