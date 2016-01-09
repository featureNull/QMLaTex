import QtQuick 2.3

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
        title: "Employee Table"
	}

    LatexTable {
        model: employeeTable
	}

    LatexSubSection {
        title: "Company Table"
    }

    LatexTable {
        model: companyTable
    }

    LatexSection {
        title: "Sample Chart"
    }

    LatexSampleChart {

    }
}
