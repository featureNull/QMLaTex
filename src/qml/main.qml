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

    MyLatexDocument {
        id: doc
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
