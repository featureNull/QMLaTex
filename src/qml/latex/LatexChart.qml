import QtQuick 2.3

import qmlatex.reports 1.0

/**
* @brief prints a chart from model
* @details role numbers are defined in table starting at 257 for first row
**/
LatexCodeBlock {
	id: self
	property var model
	property int xRole

	packages: [	"{pgfplots}" ]

	code: '\\begin{tikzpicture}' + '\r\n' +
		  '	\\begin{axis}[' + '\r\n' +
		  '		grid=major,' + '\r\n' +
		  '		xlabel = ' + self.model.roleTitleName(xRole) +
		  '		]' + '\n' +
		  childCode +
		  '\\end{axis}' + '\r\n' +
		  '	\\end{tikzpicture}'

}
