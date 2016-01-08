import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import "."


TableViewStyle {

	id: self

	headerDelegate: Rectangle {
		height: 25
		width: textItem.implicitWidth
        color: "#909090"
		
		Text {
			id: textItem
			anchors.fill: parent
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: styleData.textAlignment
			anchors.leftMargin: 12
			text: styleData.value
			elide: Text.ElideRight
            color: "white"
            renderType: Text.NativeRendering
		}
		
		Component.onCompleted: {
			styleData.containsMouseChanged.connect(tooltipHandler);
		}
		
		function tooltipHandler() {
			if (styleData.containsMouse && textItem.truncated) {
				tooltipWindow.displayTip(parent, tooltipContent, 300);
			}
			else {
				tooltipWindow.hideTip(100);
			}
		}
		
		property Component tooltipContent: Text {
			text: styleData.value
			color: "white"
		}	
		
		Rectangle {
			anchors.right: parent.right
			anchors.top: parent.top
			anchors.bottom: parent.bottom
			anchors.bottomMargin: 1
			anchors.topMargin: 1
            width: 2
            color: "white"
		}
	}

    rowDelegate: Rectangle {
        height: 26
        color: {
			if (styleData.selected)
				return "#313131"
			else if (styleData.alternate)
				return "white"
			else 
				return "#ededed"
		}
    }
}
