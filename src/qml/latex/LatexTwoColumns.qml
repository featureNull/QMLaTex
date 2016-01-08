import QtQuick 2.3
import qmlatex.reports 1.0

LatexCodeBlock {
	packages: "{multicol}"
	code: "\\begin{multicols}{2}\n"
		+ childCode
		+"\\end{multicols}\n"
}
