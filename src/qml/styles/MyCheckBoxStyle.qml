import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4

CheckBoxStyle {
	indicator: Image {
		anchors {centerIn: parent; margins: 2}
		width: 13; height: 13
		mipmap: true; smooth: true

		source: {
			if (!control.enabled && !control.checked)
				return "../../res/png/deselect_checkbox64mal64_ohne.png"
			if (!control.enabled && control.checked)
				return "../../res/png/deselect_checkbox64mal64.png"
			if (control.checked)
				return "../../res/png/checkbox64mal64.png";
			else
				return "../../res/png/checkbox64mal64_ohne.png"
		}
	}

	label: Label {
		anchors.centerIn: parent
		color: control.enabled ? "black" : "gray"
		text: control.text
	}
}
