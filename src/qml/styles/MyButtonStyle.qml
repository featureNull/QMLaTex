import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4
import "."

ButtonStyle {
    property color farbeoben: {
        var mycol="#c8c8c8"
        if (control.hovered)
            mycol="#cdcdcd"
        if (control.pressed)
            mycol="#e1e1e1"
        return mycol;
    }
    property color farbeunten: {
        var mycol="#d3d3d3"
        if (control.hovered)
            mycol="#dcdcdc"
        if (control.pressed)
            mycol="#f5f5f5"
        return mycol;
    }
    property color farbeborder: {
        var mycol="#808080"
        if (control.hovered)
            mycol="#a4a3a3"
        if (control.pressed)
            mycol="#606060"
        return mycol;
    }

    background: Item {
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
//        font.family: Style.fontFamily
//        font.pixelSize: Style.fontSize
        text: control.text
    }
}

