import QtQuick 2.3

import qmlatex.reports 1.0

/**
 * @brief print a chart from model
 * @details first column in model is the x axis others are printed as y axis
**/
LatexCodeBlock {
    id: self
    property var model

	packages: [	"{pgfplots}" ]
	
    code: '	\\begin{tikzpicture}' + '\r\n' +
          generatePlotCode() +
          '	\\end{tikzpicture}'

    LatexModelMapper {
        id: mapper
        model: self.model
        seperator: ","
        rowStartMark: "("
        rowEndMark: ")\n"
    }

    function generatePlotCode() {
        var roleNums = self.model.roleNums();

        // first role is the xRole
        var xRole = roleNums.shift();
        var xName = self.model.roleTitleName(xRole);

        var tmpCode =
        '		\\begin{axis}[' + '\r\n' +
        '			grid=major,' + '\r\n' +
        '         xlabel = ' + xName +
        '		]' + '\r\n' +
        '\r\n';
        for (var i in roleNums) {
            tmpCode += generateSinglePlotCode(xRole, roleNums[i]);
        }
        tmpCode += '\\end{axis}' + '\r\n';
        return tmpCode;
    }

    function generateSinglePlotCode(xRole, yRole){
        var enabled = [xRole, yRole];
        //@TODO this creates loop error solve it!!
        mapper.enabledRoles = enabled;
        var tmpCode =
        '		\\addplot coordinates {' + '\r\n' +
        mapper.code +
        '		};' + '\r\n' +
        '		\\addlegendentry{' + self.model.roleTitleName(yRole) + '}' + '\r\n';
        return tmpCode;
    }
}
