import QtQuick 2.3
import QtQuick.Controls 1.2

//plugin need to be provided by C++ application see main.cpp how to publish
import qmlatex.reports 1.0

import "latex"	//convenience QML Latex Files

Item {
	width: 100
	height: 100

	Button {
		text: "generate"
		onClicked: {
			compiler.startCompile();
		}
	}

	//The Compiler
	property var compiler: LatexCompiler {
		document: doc
		// specify outPath (default temp dir is used)
		outPath: "C:/myPath"
	}

	//The Document
	LatexDocument {
		id: doc
		name: "SimpleDocument"
		LatexSection {
			title: "{The First Section}"
		}
		LatexCodeBlock {
			code: "Here comes the text for the first section"
		}
		LatexSubSection {
			title: "{The Sub Section}"
		}
		LatexCodeBlock {
			code: "Here comes the text for the second section"
		}
	}
}