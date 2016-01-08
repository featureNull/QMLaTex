/**
 * @brief RoundButton wird als overlay button von den Reports genutzt
 */
import QtQuick 2.5
import QtGraphicalEffects 1.0

Item {
	/// @brief image das mit fontawaysome angezeigt wird 
	property alias fontAwesomeIconTextSchmarn: imageText.text
	
	/// @brief is button hovered
	property alias hovered: mouseArea.containsMouse
	
	property alias pressed: mouseArea.containsPress

	/// @brief in ui manier wenn der user druckt und dann loslaesst
	signal clicked
	
	//
	// internals
	//
	id: self
	implicitWidth: 40
	implicitHeight: 40
	
	Rectangle {
		id: kreis
		anchors.fill: parent
		anchors.margins: 6
		radius: Math.min(width, height)

		color: {
			if (self.pressed)
				return "#313131";
			else if (self.hovered)
				return "#606060";
			else if (self.hovered)
				return "#a4a3a3";
			else 
				return "#cdcdcdcc"
		}
	
		Text {
			id: imageText
			anchors.fill: parent
			font.family: "FontAwesome"
			renderType: Text.QtRendering
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			color: "white"
		}

		MouseArea {
			id: mouseArea
			anchors.fill: parent
			hoverEnabled: true
			onReleased: {
				if (mouse.button == Qt.LeftButton) {
					console.log("mouse clicked");
					self.clicked();
				}
			}
		}
	}

	/* geh scheissen deppats qml
	DropShadow {
		anchors.fill: kreis
		radius: 8.0
		samples: 16
		color: kreis.color; //"#80000000"
		source: kreis
	}
	*/
}

