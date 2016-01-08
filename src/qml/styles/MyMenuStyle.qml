import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4
import "../fontawesome.js" as FontAwesome
import "."

MenuStyle {
	submenuOverlap: 4

	frame: Rectangle{
		border.width: 1
		border.color: "#808080"
		color: "white"
	}

	itemDelegate {
		background: Rectangle {
			color: styleData.selected ? "#808080":"white"
		}

		label: Text {
			id: textlabel
			renderType: Text.NativeRendering
			verticalAlignment: Text.AlignVCenter
			color: styleData.selected ? "white":"black"
			text: styleData.text
		}
		submenuIndicator: Text {
			font.family: "FontAwesome"
			font.pixelSize: parent.pixelSize+2
			text: FontAwesome.Icon.CaretRight
			color: styleData.selected ? "white" : "black"
		}
	}

	separator: Rectangle {
		width: parent.width
		anchors.fill: parent
		anchors.leftMargin: 10
		anchors.rightMargin: 5
		implicitHeight: 1
		color: "#808080"
	}
}
