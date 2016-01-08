import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4
import "."

ButtonStyle {
    property color farbeoben: {
        var mycol="transparent"
        if (control.hovered)
            mycol="#cdcdcd"
        if (control.pressed)
            mycol="#e1e1e1"
        return mycol;
    }
    property color farbeunten: {
        var mycol="transparent"
        if (control.hovered)
            mycol="#dcdcdc"
        if (control.pressed)
            mycol="#f5f5f5"
        return mycol;
    }
    property color farbeborder: {
        var mycol="transparent"
        if (control.hovered)
            mycol="#a4a3a3"
        if (control.pressed)
            mycol="#606060"
        return mycol;
    }

    background: Item {
        anchors.centerIn: parent
        height: parent.height
        Rectangle {
            anchors.fill: parent
            radius: 2
            border.color: farbeborder
            border.width: 1
            gradient: Gradient {
               GradientStop { position: 1 ; color: farbeoben}
               GradientStop { position: 0 ; color: farbeunten}
            }
        }
    }
    label: Label {
        anchors.centerIn: parent
        anchors.margins: 2
        font.family: "FontAwesome"
        font.pixelSize: 22 //design icon size
        renderType: Text.QtRendering
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: control.text
    }
}

