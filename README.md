# QMLaTex
QML Wrapper for creating Latex Documents

QMLaTex provides an interface for writing structured documents in QML which is compiled to LaTex code for generating PDF documents. QML Items are provided via C++ interface and are exposed to the QML context. See the Example below of how to define the document in QML. A more advanced example can be found in `src/qml/MyLatexDocument.qml`. The provided `LatexCompiler` Item takes a QML document as input and generates the PDF file. Note you need to have installed a LaTex distribution (including needed packages). The compiler `pdflatex` is called by the QML `LatexCompiler` in the background LaTex to generate the document. The software was tested under Windows with the MikTex environment.

#### Example Sketch in QML
```qml
Item {
	
	property var compiler: LatexCompiler {
		document: doc
	}
	
	Button {
		text: "generate"
		onClicked: {
			compiler.startCompile();
		}
	}

    LatexDocument {
		id: doc
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
			code: "Here comes the text for the first section"
		}
	}
}
```
#### QML Items Provided by the C++ Interface:
  
  - `LatexDocument` - The top level item for each document
  - `LatexCodeBlock` - The document is build up by a set of (nested) LaTex code blocks
  - `LatexModelMapper` - An Item for generating data out of Qt models
  - `LatexCompiler` - A utility item for generating LaTex Documents 
  - `LatexSyntaxHighlighter` - A utility item for LaTex synthax highlighting

#### QML Convenience Items
The folder [src/qml/latex] [PlDb] contains defined convenience items for reuse. 

  - `LatexSection` - Defines a section
  - `LatexSubSection` - Defines a subsection
  - `LatexTable` - Defines a table with an Qt model as input
  - ...