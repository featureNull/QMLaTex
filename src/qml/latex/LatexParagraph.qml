import QtQuick 2.3
import lisa.reports 1.0

LatexCodeBlock {
	property string snippet
	property bool plainText
	
	onPlainTextChanged: {
		console.log("LatexCodeBlock.plainText=", plainText);
	}
	
	//
	// internal
	//
	id: self
	
	/// @todo center, links und rechts einbauen

	code: {
		if (plainText) {
			return "\\begin{verbatim}" 
				+ self.snippet
				+ "\\end{verbatim}";
		}
		else {
			return escape(self.snippet);
		}
	}
}
