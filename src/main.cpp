
#include <QGuiApplication>

#include <QtQuick/QQuickView>
#include <QQmlContext>

#include <QSqlDatabase>

#include "ImageProvider.h"
#include "SqlQueryModel.h"

#include "Reports/LatexDocument.h"
#include "Reports/LatexCodeBlock.h"
#include "Reports/LatexSyntaxHighLighter.h"
#include "Reports/LatexCompiler.h"
#include "Reports/LatexModelMapper.h"


/** 
 * registriert alle Klassen, die wo man in Qml instanzieren will
 */
static void registerQmlTypes() {
	qmlRegisterType<Reports::LatexDocument>("qmlatex.reports", 1, 0, "LatexDocument");
	qmlRegisterType<Reports::LatexCodeBlock>("qmlatex.reports", 1, 0, "LatexCodeBlock");
	qmlRegisterType<Reports::LatexSyntaxHighLighter>("qmlatex.reports", 1, 0, "LatexSyntaxHighLighter");
	qmlRegisterType<Reports::LatexCompiler>("qmlatex.reports", 1, 0, "LatexCompiler");
	qmlRegisterType<Reports::LatexModelMapper>("qmlatex.reports", 1, 0, "LatexModelMapper");

}

int main(int argc, char **argv)
{
	QGuiApplication app(argc, argv);
	
	registerQmlTypes();
	
    QQuickView view;

	view.engine()->addImageProvider(QLatin1String("previews"), new ImageProvider);

	//provide model from database
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("../../QMLaTex/test.db");
	SqlQueryModel emp;
	SqlQueryModel comp;
	SqlQueryModel dataTable;
	if (db.open()) {
		emp.setQuery("SELECT * FROM Employee");
		view.rootContext()->setContextProperty("employeeTable", &emp);

		comp.setQuery("SELECT * FROM Company");
		view.rootContext()->setContextProperty("companyTable", &comp);

		dataTable.setQuery("SELECT * FROM DataTable");
		view.rootContext()->setContextProperty("dataTable", &dataTable);

	} else {
		qDebug() << "cannot open database " << db.databaseName();
	}

    view.setSource(QUrl("../../QMLatex/src/qml/main.qml"));

    view.show();

    return app.exec();
}
