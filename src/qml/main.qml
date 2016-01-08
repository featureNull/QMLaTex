import QtQuick 2.3

import qmlatex.reports 1.0

Item {
    width: 320
    height: 320

	property var compiler: LatexCompiler {
		document: doc
	}
	
	MouseArea {
		anchors.fill: parent
		Text {
			anchors.centerIn: parent
			text: "click to compile latex file";
		}
				
		onClicked: {
			compiler.startCompile();
		}
	}	

	MyLatexDocument {
		id: doc
	}
}