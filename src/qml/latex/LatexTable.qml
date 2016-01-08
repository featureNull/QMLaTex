import QtQuick 2.3
import qmlatex.reports 1.0

LatexCodeBlock {
	property string tableparms
	code: "\\begin{supertabular}"+tableparms+"\n"
		+ childCode
		+ "\\end{supertabular}\n"
}
