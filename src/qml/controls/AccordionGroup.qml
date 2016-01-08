import QtQuick 2.2;
import QtQuick.Layouts 1.1;
import QtQuick.Controls 1.2;
import QtQuick.Controls.Styles 1.2;
import "../fontawesome.js" as FontAwesome

Column {
    id: self;
    anchors.left: parent.left;
    anchors.right: parent.right;

    default property alias groupContent: containerContent.data;
    property alias headerContent: layoutSubItems.data;
    property alias title: lblTitle.text;
    property bool expanded: false
    property alias indicatorColor: indicator.color;

    property Accordion __accordion: parent

    MouseArea {
        id: header;
        hoverEnabled: true
        height: __accordion.barSize;
        anchors {
            left: parent.left;
            right: parent.right;
        }
        onClicked: { __accordion.relayout (self); }

        Rectangle {
            color: expanded ? "#a4a3a3" : "#cdcdcd"
            anchors.fill: parent;

            Rectangle {
                id: indicator
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: expanded ? 6 : 4
                color: "transparent"
            }
        }
        Label {
            id: lblTitle;
            font.bold: expanded ? true : false
            color: expanded ? "white" : "black"
            anchors {
                left: parent.left;
                margins: 32;
                verticalCenter: parent.verticalCenter;
            }
        }
        Row {
            id: layoutSubItems;
            anchors {
                right: parent.right;
                margins: 12;
                verticalCenter: parent.verticalCenter;
            }
        }
    }

    FocusScope {
        id: containerContent;
        clip: true
        height: __accordion.contentHeight
        anchors.left: parent.left
        anchors.right: parent.right
        visible: self.expanded
        enabled: self.expanded

        /* CONTENT HERE */
    }
}

