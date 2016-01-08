#include <QGuiApplication>

#include <QtQuick/QQuickView>

#include "Reports/LatexDocument.h"
#include "Reports/LatexCodeBlock.h"
#include "Reports/LatexSyntaxHighLighter.h"
#include "Reports/LatexCompiler.h"
//#include "Reports/LatexModelMapper.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
	
	qmlRegisterType<Reports::LatexDocument>("qmlatex.reports", 1, 0, "LatexDocument");
	qmlRegisterType<Reports::LatexCodeBlock>("qmlatex.reports", 1, 0, "LatexCodeBlock");
	qmlRegisterType<Reports::LatexSyntaxHighLighter>("qmlatex.reports", 1, 0, "LatexSyntaxHighLighter");
	qmlRegisterType<Reports::LatexCompiler>("qmlatex.reports", 1, 0, "LatexCompiler");
	//qmlRegisterType<Reports::LatexModelMapper>("lisa.reports", 1, 0, "LatexModelMapper");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("../../QMLatex/src/qml/main.qml"));
    view.show();


    return app.exec();
}