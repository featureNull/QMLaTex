import QtQuick 2.3
import lisa.reports 1.0

/** @brief geomtrie fuer seitenlayout
  * @sa http://www.namsu.de/Extra/pakete/Geometry.html
  */
LatexCodeBlock {
	property int top: 10
	property int left: 10
	property int right: 10
	property int bottom: 10
	property int headsep: 10
	property int footskip: 10

	//
	// internals
	//
	packages: [ "{geometry}" ]

	code: {
		return "\\geometry{"
			+ "top=" + inttommstring(top)
			+ ", left=" + inttommstring(left)
			+ ", right=" + inttommstring(right)
			+ ", bottom=" + inttommstring(bottom)
			+ ", footskip=" + inttommstring(footskip)
			+ "}";
	}
		
	function inttommstring(value) {
		return value.toString() + "mm";
	}
}
