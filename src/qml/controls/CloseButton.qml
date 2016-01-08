import QtQuick 2.2

// close button
// used at tab control und  bei den filterboxen
//
Image {
	id: closeButton
	anchors.margins: 4
	/// wenn \c true, sind die icons hell, sonst dunkel
	property bool darkBackround
	
	///< wenn einer gedrueckt hat
	signal clicked()

	source: {
		if (darkBackround) {
			if (area.containsPress)
				return 	"qrc:///res/png/close-clicked-hell.png"
			else if (area.containsMouse)
				return 	"qrc:///res/png/close-hovered-hell.png"
			else
				return 'qrc:///res/png/close-hell.png'
		}
		else {
			if (area.containsPress)
				return 	"qrc:///res/png/close-clicked.png"
			else if (area.containsMouse)
				return 	"qrc:///res/png/close-hovered.png"
			else
				return 'qrc:///res/png/close.png'
		}
	}
		
	MouseArea {
		id: area
		anchors.fill: parent
		hoverEnabled: true
		onClicked: closeButton.clicked()
	}
}
