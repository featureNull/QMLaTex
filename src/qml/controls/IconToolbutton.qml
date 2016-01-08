/** 
 * @brief standard toolbutton der wo mit fontawaysome tut
 */
import QtQuick.Controls 1.2
import QtQuick 2.3
import "../styles"

Button {
	/** */
    property string tooltipText

    width: 26
    height: 26
	
	//
	// internals
	//
	id: self
    style: IconButtonStyle {}
	
	onHoveredChanged: {
		if (hovered) {
			// tooltip zeigen, wenn einer angegeben wurde
			if (self.tooltipText.length > 0) {
				tooltipWindow.displayTip(self, tooltipContent, 800);
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

