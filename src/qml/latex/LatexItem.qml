import QtQuick 2.3
import qmlatex.reports 1.0

LatexCodeBlock {
	property string text

	code: {	return "\\item " + text; }
}
