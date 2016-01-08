import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4
import "../fontawesome.js" as FontAwesome

SpinBoxStyle {

    padding {
        left: 2
        top: 2
        right: 8
        bottom: 2
    }

    background: Rectangle {
        id: rectA
        implicitWidth: 100
        implicitHeight: 25
        color: "white"

        Rectangle {
            id: rectB
            anchors.left: rectA.right
            implicitWidth: rectA.height/2
            implicitHeight: 25
        }
        Rectangle { //Border for A&B
            anchors.left: rectA.left
            anchors.right: rectB.right
            implicitHeight: 25
            border.color: "#808080"
            border.width: 1
        }
    }

    decrementControl: Rectangle {
        width: control.height/2
        height: control.height/2
        color: "transparent"
        Rectangle {
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 1
            width: parent.width+3
            height: control.height/2-2
            color: maDec.containsMouse ? maDec.pressed ? "white":"#dcdcdc":"#c8c8c8"

            Label {
                anchors.centerIn: parent
				font.family: "FontAwesome"
                text: FontAwesome.Icon.caret_down
				renderType: Text.QtRendering
                font.pixelSize: 15
            }
            MouseArea {
                id: maDec
                hoverEnabled: true
                anchors.fill: parent
                onClicked: { control.value -= control.stepSize }
            }
        }
    }

    incrementControl: Rectangle {
        width: control.height/2
        height: control.height/2
        color: "transparent"
        Rectangle {
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 1
            width: parent.width+3
            height: control.height/2-2
            color: maInc.containsMouse ? maInc.pressed ? "white":"#dcdcdc":"#c8c8c8"
            Label {
                anchors.centerIn: parent
				font.family: "FontAwesome"
                anchors.verticalCenterOffset: -1
                text: FontAwesome.Icon.caret_up
				renderType: Text.QtRendering
                font.pixelSize: 15
            }
            MouseArea {
                id: maInc
                hoverEnabled: true
                anchors.fill: parent
                onClicked: { control.value+=control.stepSize }
            }
        }
    }
}

