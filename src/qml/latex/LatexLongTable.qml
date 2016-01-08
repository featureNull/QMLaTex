import QtQuick 2.3
import lisa.reports 1.0

/** 
 * @brief long latex table (totally untested and sure buggy)
 */
LatexCodeBlock {
	property var model
	
	//
	// internal
	//
	id: self
	packages: [ "{longtable}" ]

	code: {
		return "\\begin{longtable}" + getTableSchema()
			+ "\r\n\\hline\r\n"
			+ getHeaderRow() + "\\\\"
			+ "\r\n\\hline"
			+ childCode
			+ "\\hline"
			+ "\r\n\\end{longtable}";
	}
	
	LatexModelMapper {
		id: mapstmi
		model: self.model
	}
	
	function getHeaderRow() {
		if (self.model == null)
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
		if (self.model == null)
			return;
		
		var text = "|";
		var roles = self.model.roleNums();
		for (var ii in roles) {
			console.log("buildHeader#", roles[ii])
			text += " l |";
		}
		return "{" + text + "}";
	}
}
