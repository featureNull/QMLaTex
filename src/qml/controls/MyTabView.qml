import QtQuick 2.5
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import "../styles"
import "../fontawesome.js" as FontAwesome

/**
 * @brief tabview fuer das hauptfenster
 * @note arbeitet mit MyTab zusammen. Diese koennen mit cancel mit close button und
 * icon verziert werden
 */
TabView {
	
	/** @brief wird emitted wenn user auf den rechten Maus Button drueckt */
	signal contextMenuRequested(int tabindex)

	//
	// internals
	//
	id: self
	
	style: TabViewStyle {
		frameOverlap: 0

		tab:  Rectangle {
			id: tabRect
			color: styleData.selected ? "#313131" : "#ededed"
			border.color: styleData.selected ? "#909090": "#a4a3a3"
			implicitWidth: Math.min(180, control.width/control.count);
			implicitHeight: 26

			Rectangle {
				width: parent.width-2
				height: 1
				anchors.horizontalCenter: parent.horizontalCenter
				anchors.bottom: parent.bottom
				color: styleData.selected ? "#ededed":"#a4a3a3"
			}

			Loader {
				id: thumpnailImage
				
				visible: {
					var curtab = control.getTab(styleData.index);
					if (curtab != null)
						return curtab.thumbnail != null;
					else
						return false;
				}
				sourceComponent: {
					var curtab = control.getTab(styleData.index);
					if (curtab != null)
						return curtab.thumbnail;
					else
						return null;
				}
				anchors.verticalCenter: parent.verticalCenter
				x: 8; height: 18; width: 18
			}

			Text {
				id: tabText
				renderType: Text.NativeRendering
				anchors.verticalCenter: parent.verticalCenter
				anchors.left: thumpnailImage.visible ? thumpnailImage.right : parent.left
				anchors.right: closebtn.visible ? closebtn.left : parent.right
				anchors.leftMargin: 8
				elide: Text.ElideRight
				text: styleData.title
				color: styleData.selected ? "white" : "black"
			}

			//  close button
			CloseButton {
				id: closebtn
				visible: {
					var curtab = control.getTab(styleData.index);
					if (curtab != null)
						return curtab.closeable;
					else
						return false;
				}

				darkBackround: styleData.selected
				anchors.right: parent.right
				anchors.verticalCenter: parent.verticalCenter;
				onClicked: {
					destroyTab(styleData.index);
				}
			}

			MouseArea {
				anchors.fill: tabText
				acceptedButtons: Qt.RightButton | Qt.MiddleButton
				hoverEnabled: true
				onContainsMouseChanged: {
					var curtab = control.getTab(styleData.index);
					
					if (curtab != null) {
						if (containsMouse && !styleData.selected) {
							tooltipWindow.displayTip(tabRect, curtab.tooltipContent, 800);
						}
						else {
							tooltipWindow.hideTip(100);
						}
					}
				}

				onClicked: {
					tooltipWindow.hideTip(0);
					
                    if (mouse.button == Qt.RightButton)
						contextMenuRequested(styleData.index);
                    else if (mouse.button == Qt.MiddleButton) {
						var curtab = control.getTab(styleData.index);
						var closeable = (curtab != null) ? curtab.closeable : false
						if (closeable)
							destroyTab(styleData.index);
					}
					else 
						console.error("MouseArea eigenartiges result");
				}
				
			} // mousearea
			
			function destroyTab(index) {
				console.log("destroyTab:", index);
				control.removeTab(index);
			}
		}

        frame: Rectangle {
            border.width: 1
            border.color: "#a4a3a3"
            color: "white"
            anchors.fill:parent
            anchors.margins: -1
        }

        tabsMovable: true
	}

    // handle stuff wenn der user feste tabs verschiebt (zB.: Produkt uebersicht)
	onCurrentIndexChanged: {
		var curtab = getTab(currentIndex);
		tooltipWindow.hideTip(0);
		
		// note das geht nur, wenn sich nicht mehrere tabs gleichzeitig verschieben
		// behandlung, wenn ein moveabletab in einen nicht moveable reinschieben will
		if (curtab.fixedTabPos >= 0) {
			if (curtab.fixedTabPos != currentIndex) {
				// tab wurde vom user verschoben -> tabs tauschen
				moveTab(currentIndex, curtab.fixedTabPos);
				return;
			}
		}
		
		// fall, wenn wer den nicht moveable tab bewegt hat
		for (var i = 0; i < count; i++) {
			var fixedtabpos = getTab(i).fixedTabPos
			if (fixedtabpos >= 0) {
				if (i != fixedtabpos) {
					moveTab(i, fixedtabpos)
				}
			}
		}
	} // oncurrentIndexChanged
}


 
