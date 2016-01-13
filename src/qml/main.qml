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

	SimpleDoucument {
		id: simpleDoc
	}

	DataDocument {
		id: dataDoc
		orientation: self.orientation
    }

    property var compiler: LatexCompiler {
		document: simpleDoc //latte

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

		Column {
			spacing: 10
			anchors.top : parent.top
			width: 200
			Row {
				spacing: 10
				Text {
					anchors.verticalCenter: parent.verticalCenter
					text: "Select"
				}

				ComboBox {
					implicitWidth: 120
					id: cbDocument
					model: ["SimpleDocument", "DataDocument"]
					onCurrentIndexChanged: {
						if (currentIndex == 0) {
							compiler.document = simpleDoc;
							txtHelp.text = txtHelp.help[0];
						} else {
							compiler.document = dataDoc;
							txtHelp.text = txtHelp.help[1];
						}
					}
				}
			}

			Button {
				text:"Compile Document"
				onClicked: {
					compiler.startCompile();
				}
			}

			Text {
				width: parent.width
				text: compiler.outPath + "/" + compiler.document.docName + ".tex"
				wrapMode: Text.WrapAnywhere
			}

			Button {
				text: "Change Output Path"
				onClicked: {
					dlgOutPath.open();
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
				visible: cbDocument.currentIndex == 1;
				text: "Coffee Stain"
				onCheckedChanged: {
					//add package to list
					if (dataDoc.packages.indexOf("{coffee4}") < 0 && checked)
						dataDoc.packages.push("{coffee4}");
					dataDoc.coffeeEnabled = checked;
				}
			}

			Text {
				id:txtHelp
				width: parent.width
				wrapMode: Text.WordWrap
				property var help: [
					"This is a simple Latex document.",

					"In this document data is retrievied from C++ models."+
					"Your Latex installation need to have installed the 'pgfplots' " +
					"package for printing the charts. If you have installed also the coffee4 " +
					"package you can produce a nice coffee stain (enable the check and " +
					"compile twice too see the stain)"
				]
			}
		} // columnlayout

		PdfPreview {
			id: preview
			Layout.fillWidth: true
			Layout.fillHeight: true
			compiler: self.compiler
		}
    } // RowLayout

	FileDialog {
		id: dlgOutPath
		selectFolder: true
		onAccepted: {
			compiler.outPath = folder;
		}
	}
}
