import QtQuick 2.3

import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2

import qmlatex.reports 1.0

import "latex"


Item {
	id: self
    width: 1100
    height: 950

	property alias orientation: cbOrientation.currentValue
/*
	LatexDocument {
		id: doc;

		LatexSection{
			title: "test"
		}
	}*/

    MyLatexDocument {
		id: doc
		orientation: self.orientation
		coffee: cbCoffee.checked
		chart: cbChart.checked

    }

    property var compiler: LatexCompiler {
        document: doc //latte
		
		onBuildError: {
			messageDialog.text = errorText;
			messageDialog.detailedText = detailedText;
			messageDialog.open();
		}
	} // compiler
	
	MessageDialog {
		id: messageDialog
		icon: StandardIcon.Critical
		title: "Report Error"
		width: 400
	}		
	
	RowLayout {
		anchors.fill: parent
		anchors.margins: 10
		spacing: 10

		ColumnLayout {
			Button {
				text:"Compile MyLatexDocument"
				onClicked: {
					compiler.startCompile();
				}
			}

			Row {
				spacing: 10
				Text {
					anchors.verticalCenter: parent.verticalCenter
					text: "Orientation"
				}

				ComboBox {
					implicitWidth: 80
					id: cbOrientation
					property var currentValue: {
						return orientationModel.get(currentIndex).value;
					}

					model: ListModel {
						id: orientationModel
						ListElement { text: "Portrait"; value: LatexDocument.Portrait }
						ListElement { text: "Landscape"; value: LatexDocument.Landscape }
					}
				}
			}

			CheckBox {
				id: cbCoffee
				text: "Coffee (need coffee4 package installed,\n" +
					  " compile twice to see changes)"
				onCheckedChanged: {
					if (doc.packages.indexOf("{coffee4}") < 0)
						if (checked)
							doc.packages.push("{coffee4}");
				}
			}

			CheckBox {
				id: cbChart
				text: "Charts (need pgfplots package installed)"
				onCheckedChanged: {
					if (doc.packages.indexOf("{pgfplots}") < 0)
						if (checked)
							doc.packages.push("{pgfplots}");
				}
			}

			Item {
				Layout.fillHeight: true
			}
		} // columnlayout

		PdfPreview {
			id: preview
			Layout.fillWidth: true
			Layout.fillHeight: true
			compiler: self.compiler
		}
    } // RowLayout
}
