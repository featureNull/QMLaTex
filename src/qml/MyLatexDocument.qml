import qmlatex.reports 1.0

import "latex"

LatexDocument {

	LatexSection {
		title: "Section"
	}

	LatexCodeBlock {
		code: "some text for the first section"
	}

	LatexSubSection {
		title: "subsection"
	}

	LatexCodeBlock {
		code: "some text for the first subsection"
	}
}