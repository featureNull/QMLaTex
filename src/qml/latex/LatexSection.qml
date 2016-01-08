import QtQuick 2.3
import lisa.reports 1.0

LatexCodeBlock {
	property string title
	code: "\\section{" + title + "}";
}
