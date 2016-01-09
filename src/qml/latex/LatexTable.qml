import QtQuick 2.3
import qmlatex.reports 1.0

LatexCodeBlock {
    id: self
    property var model

    code: "\\begin{tabular}"+getTableSchema()
        + "\n\\hline\n"
        + getHeaderRow() + "\\\\"
        + "\r\n\\hline"
        + childCode
        + "\\hline\n"
        + "\\end{tabular}\n"


    LatexModelMapper {
        id: mapstmi
        model: self.model
    }

    function getHeaderRow() {
        if (self.model === null)
            return;

        var colums = [];
        var roles = self.model.roleNums();
        for (var ii in roles) {
            var c = "\\textbf{"
                    + model.roleTitleName(roles[ii])
                    + "}";

            colums.push(c);
        }
        return colums.join(" & ");
    }

    function getTableSchema() {
        if (self.model === null)
            return;

        var text = "|";
        var roles = self.model.roleNums();
        for (var ii in roles) {
            text += " l |";
        }
        return "{" + text + "}";
    }
}
