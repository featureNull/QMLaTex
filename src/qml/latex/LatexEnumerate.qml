import QtQuick 2.3
import qmlatex.reports 1.0

LatexCodeBlock {
	code: {
		return "\\begin{enumerate}"
			+ childCode 
			+ "\\end{enumerate}";
	}
}
