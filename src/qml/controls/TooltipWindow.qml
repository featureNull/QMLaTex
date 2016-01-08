/** 
 * @brief singletone toltip
 * 
 * @note sehr viele controls setzen voraus, dass es eine instanz mit der 
 * id \c tooltipWindow gibt.
 */
import QtQuick 2.5
//import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

Window {
	property Component content
	property color backgroundColor: "#313131"
	property Window rootWindow
	
	/** @brief tooltip zeigen
	  * @param targetitem item fuer das der tip sein soll
	  * @param contentItem item das wo im tip gezeigt werden soll
	  * @param delay verzoegerung beim zeigen in msecs
	  */
	function displayTip(targetitem, contentItem, delay) {
		if (contentItem == null) {
			// do nothing. hats das man nicht ueberall im code das abfragen muss
			return;
		}
		timer.stop();
		
		content = contentItem;
		var xp = targetitem.width/2 - width/2;
		var yp = targetitem.height;
		var pos = targetitem.mapToItem(null, xp, yp);

		x = pos.x + rootWindow.x;
        y = pos.y + rootWindow.y;
		//console.log("displayTip: x=", x, ", y=", y);
		
		if (visible) {
			// wenn der tip sichtbar ist brauchts nichts
		}
		else if (delay > 0) {
			_aboutToShow = true;
			timer.interval = delay;
			timer.start();
		}
		else {
			visible = true;
		}
	}
	
	/** @brief tip wieder verstecken. 
	  * @param delay verzoegerung beim ausschalten
	  */
	function hideTip(delay) {
		timer.stop();

		if (delay > 0) {
			_aboutToShow = false;
			timer.interval = delay;
			timer.start();
		}
		else {
			visible = false;
		}
	}

	//
	// internals
	//
	id: self
	property bool _aboutToShow
	
	width: loader.width + 20 + 6
	height: loader.height + 20 + 4
	color: "transparent"
	modality: Qt.NonModal
	flags: "Qt::ToolTip"
	
    Timer {
        id: timer

        onTriggered: {
            visible = _aboutToShow;
        }
    }

	// kleins dreieckchen, das gedreht ist und die spitze bildet
	Rectangle {
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: contentRect.top
		smooth: true
		width: 10; height: 10; 
		z: 1
		color: self.backgroundColor

		transform: Rotation {
			origin.x: 5; origin.y: 5; angle:45
		}
	}
	
	Rectangle {
		id: contentRect
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 5
		width: loader.width + 10
		height: loader.height + 10
		color: self.backgroundColor
		border.color: "white"
		border.width: 1
		
		Loader {
			anchors.centerIn: parent
			id: loader
			sourceComponent: self.content
		}
	}
}