import QtQuick 2.3

import qmlatex.reports 1.0

import "latex"

LatexDocument {
	docName: "MyLatexDocument"
	property alias coffee: coffee.enabled
	property alias chart: chart.enabled

	packages: [
	]	// empty package list per default add at runtime

	LatexSection {
		title: "QMLaTex Document Example"
	}

	LatexCodeBlock {
		code: 'This example demonstrates QMLaTex features. Simple code blocks are shown. ' +
			  'Further more complex data is shown in a table and a charts to demonstrate the ' +
			  ' interaction between Qt\'s C++ data model and QML.'
	}

	LatexParagraph {
		title: "A new Paragraph"
	}

	LatexCodeBlock {
		code: 'is beginning here'
	}

	CoffeeStains {
		id: coffee
		enabled:false
	}

	LatexSection {
		title: "Work with Qt's DataModel"
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
		id: chart
		enabled: false;
		model: dataTable
		xRole: dataTable.roleNum("Measure")

		LatexChartSeries {
			model: dataTable
			xRole: dataTable.roleNum("Measure")
			yRole: dataTable.roleNum("Samples1")
		}

		LatexChartSeries {
			model: dataTable
			xRole: dataTable.roleNum("Measure")
			yRole: dataTable.roleNum("Samples2")
		}
	}

	LatexSection {
		title: "Enumerations"
	}

	LatexEnumerate {
		LatexItem {
			LatexCodeBlock { code: 'The first line.' }
		}
		LatexItem {
			LatexCodeBlock { code: 'The second line.' }
			LatexEnumerate {
				LatexItem {
					LatexCodeBlock {code: "Subitem 1"}
				}
				LatexItem {
					LatexCodeBlock {code: "Subitem 2" }
				}
			}
		}
		LatexItem {
			LatexCodeBlock { code: 'The last item.' }
		}
	}

	LatexCodeBlock {
		code: "\\newpage"
	}

	LatexSubSection {
		title: "The new page"
	}

}
