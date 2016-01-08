/**
 * @brief Csv Export Dialog
 */
import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2
import qmlatex.reports 1.0

Dialog {
	/// @brief ist \c true, wenn es latex syntax sein soll, 
	/// bei plaintext false
	property bool plainText: {
		return __syntaxMode != LatexSyntaxHighLighter.LatexSyntax
	}
	
	onPlainTextChanged: {
		console.log("syntaxMode = ", __syntaxMode, "plainText=", plainText);
	}
	
	/// @brief latex code, bzw plain text
	property alias code: textEdit.text
	
	//
	// internals
	//
	id: self
	height: 600
	width: 600 * 1.41
	visible: false
	property alias __syntaxMode: cbxMode.syntaxMode
	

	contentItem: Rectangle {
		// rechteck hintergrund (ist irgendwie scheisse)
		color: "#ededed"
		
		ColumnLayout {
			anchors.fill: parent
			anchors.margins: 10
			spacing: 10
			
			Row {
				Label {
					text: "String quote"
				}
				ComboBox {
					id: cbxMode
				
					property var syntaxMode: {
						var value = modeModel.get(currentIndex).value
						return value;
					}

					model: ListModel {
						id: modeModel
						ListElement { 
							text: "Plain Text"; 
							value: LatexSyntaxHighLighter.BadWordsSyntax 
						}
						
						ListElement { 
							text: "Latex snipped"; 
							value: LatexSyntaxHighLighter.LatexSyntax
						}
					}
				}
			}
			
			TextArea {
				id: textEdit
				Layout.fillWidth: true
				Layout.fillHeight: true
			}

			//
			// buttons ok und cancel
			//
			RowLayout {
				Layout.fillWidth: true
				
				Item { 
					Layout.fillWidth: true
				}
				Button {
					text: "Ok"
					width: 200

					onClicked: {
						accepted();
						close();
					}
				}
				Button {
					text: "Cancel"
					width: 200
					onClicked: {
						close();
					}
				}
			} // rowlayout
		}
	}
	
	LatexSyntaxHighLighter {
		quickTextDocument: textEdit.textDocument
		syntaxMode: __syntaxMode
	}
}
