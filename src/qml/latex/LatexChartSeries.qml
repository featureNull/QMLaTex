import QtQuick 2.3

import qmlatex.reports 1.0

/**
* @brief prints a single series from model
* @details define the roles you want to print in this plot
**/
LatexCodeBlock {
	id: self
	property var model
	property var xRole
	property var yRole

	code: '\\addplot coordinates {\n' +
			childCode +
			'};' + '\r\n' +
			'\\addlegendentry{' + self.model.roleTitleName(yRole) + '}\n';

	LatexModelMapper {
		id: mapper
		model: self.model
		seperator: ","
		rowStartMark: "("
		rowEndMark: ")\n"
		enabledRoles: [xRole,yRole]
	}
}
