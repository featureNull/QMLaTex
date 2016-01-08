/**
 * @brief FlatButton ist ein button ohne hover Hintergrund
 */
import QtQuick.Controls 1.2
import QtQuick 2.5
import QtQuick.Controls.Styles 1.4
import "../styles"


Button {
    width: 20
    height: 20
    property color defaultcolor: "#606060"
    property color hoverColor: "black"
	property string tooltipText
	
	//
	// internals
	//
	id: self
	
    style: ButtonStyle {
        background: Rectangle {
            anchors.fill: parent
            color: "transparent"
        }

        label: Label {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -1
            font.family: "FontAwesome"
            font.pixelSize: control.height-2
            renderType: Text.QtRendering
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: control.text
            color: control.hovered ? control.hoverColor : control.defaultcolor
        }
    }
	
	onHoveredChanged: {
		if (hovered) {
			// tooltip zeigen, wenn einer angegeben wurde
			if (self.tooltipText.length > 0) {
				tooltipWindow.displayTip(self, tooltipContent, 100);
			}
		}
		else {
			tooltipWindow.hideTip(100);
		}
	}

	onClicked: {
		tooltipWindow.hideTip(0);
	}
	
	property Component tooltipContent: Text {
		text: self.tooltipText
		color: "white"
	}
}

