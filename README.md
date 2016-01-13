# QMLaTex
QML Wrapper for creating Latex Documents 

QMLaTex provides an interface for writing structured documents in QML which is compiled to LaTex code for generating PDF documents. The following Example generates a LaTex(Pdf) files which can be found in `doc/SimpleDocument.tex(pdf)`.

```qml
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
```
### Details
QML Items are provided via C++ interface and are exposed to the QML context. See the Example below of how to define the document in QML. A more advanced example can be found in `src/qml/DataDocument.qml`. The provided `LatexCompiler` Item takes a QML `LatexDocument` as input and generates the PDF file. Note you need to have installed a LaTex distribution (including needed packages). The QML item `LatexCompiler` generates `.tex` code from the `LatexDocument` and call the latex compiler `pdflatex` in the background LaTex to generate the pdf document(the tools `pdfinfo` and `pdftoppm` to generate previews in the QML appplication). The software was tested under Windows with the MikTex environment. But should also run on Linux System. 


#### Prerequisites
  - Qt 5.5 
  - LaTex compiler and tools (`pdflatex`  `pdfinfo` and `pdftoppm`). All included in the MikTex distribution.
  - To generate the example document under `src/qml/DataDocument` you need the latex package `pgfplots` to print the charts. (optionally to see a coffee stain the package `coffee4` should be installed)
  
#### QML Items Provided by the C++ Interface:
  
  - `LatexDocument` - The top level item for each document
  - `LatexCodeBlock` - The document is build up by a set of (nested) LaTex code blocks
  - `LatexModelMapper` - An Item for generating data out of Qt models
  - `LatexCompiler` - A utility item for generating LaTex Documents 
  - `LatexSyntaxHighlighter` - A utility item for LaTex syntax highlighting (currently not used in the examples)

#### QML Convenience Items
The folder `src/qml/latex` contains defined convenience items for reuse. 

  - `LatexSection` - Defines a section
  - `LatexSubSection` - Defines a subsection
  - `LatexTable` - Defines a table with an Qt data model for input data
  - ...