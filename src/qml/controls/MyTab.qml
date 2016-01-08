import QtQuick 2.2
import QtQuick.Controls 1.2

/** 
 * @brief ein einzelner tab in einem MyTabView
 */
 Tab {
	///< man kann den tab bewegen, wenn nicht gesetz, ansonsten hat er einen festen platz 
	/// @note limitation das heisst das feste tabs immaer am anfang vor schliessbaren sein duerfen
	property int fixedTabPos: -1

	///< hat dieser tab einen close button
	property bool closeable: true

	///< icon links oben
	property Component thumbnail

    property Component tooltipContent
	
	/// @todo more or less a quick hack to identify type
	property string type
	
	/// @brief datenmodell von dem tab (optional)
    property var model
}
