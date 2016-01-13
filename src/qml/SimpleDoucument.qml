import qmlatex.reports 1.0

import "latex"

LatexDocument {
	docName: "SimpleDocument"

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
