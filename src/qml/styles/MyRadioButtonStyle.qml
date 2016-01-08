import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4

RadioButtonStyle {
	indicator: Image {
		mipmap: true
		smooth: true
		anchors.centerIn: parent
		anchors.margins: 2
		source: {
			if (!control.enabled && !control.checked)
				return "../../res/png/deselect_radiobutton64mal64_ohne.png"
			if (!control.enabled && control.checked)
				return "../../res/png/deselect_radiobutton64mal64.png"
			if (control.checked)
				return "../../res/png/radiobutton64mal64.png";
			else
				return "../../res/png/radiobutton64mal64_ohne.png"
		}
		width: 13
		height: 13
	}

	label: Label {
		anchors.centerIn: parent
		color: control.enabled ? "black" : "gray"
		text: control.text
	}
}
