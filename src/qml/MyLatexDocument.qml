import QtQuick 2.3

import qmlatex.reports 1.0

import "latex"

LatexDocument {
	LatexSection {
		title: "QMLaTex Document Example"
	}

	LatexCodeBlock {
		code: 'This example demonstrates QMLaTex features. Simple code blocks are shown. ' +
			  'Further more complex data is shown in a table and a charts to demonstrate the ' +
			  ' interaction between Qt\'s C++ data model and QML.'
	}

	
	LatexSubSection {
		title: "The LatexTable Item"
	}
	
	LatexTable {
		model: dataTable
	}

	LatexSubSection {
		title: "The LatexChart Item"
	}

	LatexChart {
		model: dataTable
		xRole: dataTable.roleNum("Measure")

		LatexChartSeries {
			model: dataTable
			xRole: parent.xRole
			yRole: dataTable.roleNum("Samples1")
		}

		LatexChartSeries {
			model: dataTable
			xRole: parent.xRole
			yRole: dataTable.roleNum("Samples2")
		}
	}
	LatexCodeBlock {
		code: "\\newpage"
	}

	LatexSubSection {
		title: "The new page"
	}

}
