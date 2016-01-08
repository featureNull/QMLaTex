import QtQuick 2.3
import QtQuick.Controls 1.2

import qmlatex.reports 1.0

Item {
    width: 320
    height: 480
	
	Button {
		id: btn
		text: "compile";
				
		onClicked: {
			compiler.startCompile();
		}
	}

	LatexDocument {
		id: doc

		LatexCodeBlock {
			packages: [	"[table,xcdraw]{xcolor}" ]
			code: "hallo ich bins"
		}
	}

	property var compiler: LatexCompiler {
		document: doc
	}
}