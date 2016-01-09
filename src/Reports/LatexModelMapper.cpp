#include "LatexModelMapper.h"
#include "IQmlModelSchemaPresenter.h"

#include <QObject>
#include <QString>
#include <QElapsedTimer>

namespace Reports {

LatexModelMapper::LatexModelMapper(QObject* parent /*= NULL*/) 
	: LatexCodeBlock(parent), logger("Latex.LatexModelMapper")
{
	_model = nullptr;

	_seperator = " & ";
	_rowStartMark = "";
	_rowEndMark = "\\\\\r\n";
}

LatexModelMapper::~LatexModelMapper()
{
}
void LatexModelMapper::setModel(QAbstractItemModel* model)
{
	if (_model != nullptr) {
		// disconnect old model
		_model->disconnect(this);
	}
	
	if (model != nullptr) {
		// connect new model
		connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex &, const QVector<int>&)),	
				this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&)));
	}
	_model = model;
	tryBuild();

	emit modelChanged();
}

QAbstractItemModel* LatexModelMapper::model() const
{
	return _model;
}

void LatexModelMapper::setEnabledRoles(const QList<int>& roles)
{
	_enabledRoles = roles;
	tryBuild();
	emit enabledRolesChanged();
}

QList<int> LatexModelMapper::enabledRoles() const
{
	return _enabledRoles;
}

void LatexModelMapper::setSeperator(const QString& value)
{
	_seperator = value;
	emit seperatorChanged();
}

QString LatexModelMapper::seperator() const
{
	return _seperator;
}

void LatexModelMapper::setRowStartMark(const QString& value)
{
	_rowStartMark = value;
	tryBuild();
	emit rowStartMarkChanged();
}

QString LatexModelMapper::rowStartMark() const
{
	return _rowStartMark;
}

void LatexModelMapper::setRowEndMark(const QString& value)
{
	_rowEndMark = value;
	tryBuild();
	emit rowEndMarkChanged();
}

QString LatexModelMapper::rowEndMark() const
{
	return _rowEndMark;
}

void LatexModelMapper::tryBuild() 
{
	QElapsedTimer dbgtmr;
	dbgtmr.start();
	qCInfo(logger) << "try build modelmapper set";
	

	if (_model == nullptr) {
		qCDebug(logger) << "try build model not set";
		return;
	}

	QString result;
	QTextStream stream(&result);
	QList<int> roles = determineRoles();

	// rows spaxen
	for (int ii = 0; ii < _model->rowCount(); ii++) {
		stream << _rowStartMark;
		stream << createSingleRow(roles, ii);
		stream << _rowEndMark;
	}

	setCode(result);
	qCDebug(logger) << "tryBuild success done in [ms]:" << dbgtmr.elapsed();
}

QString LatexModelMapper::createSingleRow(const QList<int>& roles, int row) const
{
	QStringList list;
	QModelIndex modelinx = _model->index(row, 0);

	IQmlModelSchemaPresenter* presi;
	presi = dynamic_cast<IQmlModelSchemaPresenter*>(_model);

	foreach (int role, roles) {
		if (presi == nullptr) {
			// schema presenter nicht implementiert
			QString curstr = _model->data(modelinx, role).toString();
			list << escape(curstr);
		}
		else {
			// standard schema presenter implementiert. Dann kann man auch 
			// das kunststueck mit den kommastallen machen
			QString curstr = presi->formatedData(modelinx, role);
			list << escape(curstr);
		}
	}

	return list.join(_seperator);
}

void LatexModelMapper::onDataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>& roles)
{
	foreach (int role, determineRoles()) {
		if (roles.contains(role)) {
			tryBuild();
			return;
		}
	}
}

QList<int> LatexModelMapper::determineRoles() const
{
	QList<int> roles;

	IQmlModelSchemaPresenter* presi;
	presi = dynamic_cast<IQmlModelSchemaPresenter*>(_model);

	if (!_enabledRoles.isEmpty()) {
		// roles gesetzt vom qml
		roles = _enabledRoles;
	}
	else if (presi != nullptr) {
		// alle rollen von schemapresenter
		roles = presi->roleNums();
	}
	else {
		// letzte chance, nur vom modell. 
		// das wird bei komplexen dynamischen modellen nicht gehen
		roles = _model->roleNames().keys();
		qSort(roles.begin(), roles.end());
	}

	return roles;
}


} // namespace

