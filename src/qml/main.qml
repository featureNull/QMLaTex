import QtQuick 2.3

import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2

import qmlatex.reports 1.0

import "latex"
import "styles"


Item {
	id: self
    width: 1000
    height: 700

	property alias orientation: paperFormat.currentValue
	property alias paperSize: cbxPaperSize.currentValue
	property var model: null
	
	LatexDocument {
		id: latte
		orientation: self.orientation
		paperSize: self.paperSize
		fontSize: 24
		
		LatexCodeBlock {
			packages: [	"[table,xcdraw]{xcolor}" ]
			code: "iojhoijoij"
		}
				
		LatexSampleChart {
			enabled: checkdemoChart.checked
		}
		
		LatexLongTable {
			enabled: checkTable.checked
			model: self.model
		}

		/*
		das bricht leider :(
		CoffeeStains {
			enabled: checkCoffe.checked
		}
		*/
		
		LatexCodeBlock {
			id: kjhkjh
			enabled: true

			code: 'A rather long string of English text, an error message ' +
				  'actually that just keeps going and going -- an error ' +
				  'message to make the Energizer bunny blush (right through ' +
				  'those Schwarzenegger shades)! Where was I? Oh yes, ' +
				  'you\'ve got an error and all the extraneous whitespace is ' +
				  'just gravy.  Have a nice day.'
		}
		
		LatexSection {
			title: "test section"
		}

		LatexCodeBlock {
			code: 'ein supertolles taxi rast durch muenchen'
		}

		LatexCodeBlock {
			code: 'ein supertolles taxi rast durch muenchen'
		}
	}

	property var compiler: LatexCompiler {
		document: latte
		
		compileMode: {
			if (btnManualCompile.checked)
				return LatexCompiler.ManualCompile;
			else 
				return LatexCompiler.AutoCompile;
		}
		
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
			
			ExclusiveGroup { id: compilegroup }
			RadioButton {
				id: btnManualCompile
				text: "Manuelles compilierenen"
				checked: true
				exclusiveGroup: compilegroup
				style: MyRadioButtonStyle {}
			}
			RadioButton {
				text: "Automatisches compilierenen"
				exclusiveGroup: compilegroup
				style: MyRadioButtonStyle {}
			}
		
			Button {
				text: "doIt";
				id: btn
				enabled: btnManualCompile.checked
				
				onClicked: {
					compiler.startCompile();
				}
				style: MyButtonStyle {}
			}

			CheckBox {
				id: checkCoffe
				text: "Kafffe flecken"
				style: MyCheckBoxStyle {}
			}
			
			CheckBox {
				id: checkdemoChart
				text: "Deno chart"
				style: MyCheckBoxStyle {}
			}
			
			CheckBox {
				id: checkTable
				text: "Table"
				style: MyCheckBoxStyle {}
			}

			CheckBox {
				id: checksnet
				text: "enable comment"
				style: MyCheckBoxStyle {}
			}

			Row {
				Label { text: "format" }

				ComboBox {
					id: paperFormat
					property var currentValue: {
						return stringQuoteModel.get(currentIndex).value;
					}

					model: ListModel {
						id: stringQuoteModel
						ListElement { text: "HochFormat"; value: LatexDocument.Portrait }
						ListElement { text: "QuerFormat"; value: LatexDocument.Landscape }
					}
					style: MyComboBoxStyle {}
				}
			}

				
			Row {
				Label { text: "Papiergroesse" }

				ComboBox {
					id: cbxPaperSize
					property var currentValue: {
						return jaweissnichtModel.get(currentIndex).value;
					}

					model: ListModel {
						id: jaweissnichtModel
						ListElement { text: "A4"; value: LatexDocument.A4 }
						ListElement { text: "A3"; value: LatexDocument.A3 }
					}
					style: MyComboBoxStyle {}
				}
			}
			
			Button {
				text: "comment"
				onClicked: {
					commentDialog.open();
				}
			}

			TextArea {
				id: textEdit
				enabled: checksnet.checked
				text: ""
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
	
	LatexCodeDialog {
		id: commentDialog
	}
	
}