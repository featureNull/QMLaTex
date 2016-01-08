//
// fuer reichhaltige tableviews eine moeglichkeit die 
// columns zu gruppieren
//
import QtQuick 2.2
import QtQuick.Controls 1.2
import "../fontawesome.js" as FontAwesome

Rectangle {
	/// @brief ueber wieviele spalten soll das ding gehen
	property int columnSpan
	
	/// @brief Titel text
	property alias title: textitem.text

	/// @brief ist das ding kollabiert auf das plus zeichen
	/// @note use setCollapsed in respect of animations
	property bool collapsed: false

	/// @brief minimale breite um den content anzuzueigen
	property int minimumWidth: {
		collapsed ? btn.width : textitem.width + btn.width
	}
	
	///  @brief freundlicher farbiger streifen oben
	property color indicatorColor: "transparent"
	
	property bool collapseable: true
	
	signal recomputeRequested()

	id: self
    y: 0; height: 30;
    color: "#909090"

	
	/** */
	function setCollapsed(collapsed) {
		if (!transition.running) {
			// breiten nur merken, wenn gerade keine animation laeuft
			__popColumnWidths();
		}

		if (collapsed)
			self.state = "collapsed";
		else 
			self.state = "notcollapsed";
	}
	
	//
	// internal
	//
	property int __startColumn
	property TableView __tableView
	property var __columnWithArray
	property var __columnWitdhs: []
	property real animColumnMutltip: 1.0

	// button, der wo columns hift und asnzeigt
	FlatToolbutton {
		visible: collapseable
		id: btn
		anchors.left: parent.left
		anchors.verticalCenter: parent.verticalCenter
		anchors.verticalCenterOffset: 1
		defaultcolor: "#606060"
		hoverColor: "black"

		text: {
			if (!collapsed)
				return 	FontAwesome.Icon.minus
			else
				return 	FontAwesome.Icon.plus
		}

		onClicked: {
			setCollapsed(!self.collapsed);
		}
		
		tooltipText: self.collapsed ? title : ""
	}
	
	Text {
		anchors.margins: 10
		id: textitem
		visible: !collapsed
        anchors.left: collapseable ? btn.right : parent.left
		anchors.right: parent.right
		anchors.verticalCenter: parent.verticalCenter
		renderType: Text.NativeRendering		
		elide: Text.ElideMiddle
		color: "black"
	}
	
	// indicator rechteck
	Rectangle {
		height: 4
		z: 1
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: parent.top
		color: self.indicatorColor
	}
	
	// rechter rand
	Rectangle {
		anchors.right: parent.right
		anchors.top: parent.top
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 1
		anchors.topMargin: 1
		width: 2
		color: "white"
	}
	

	function __init(startColumn, tableView) {
		self.__startColumn = startColumn;
		self.__tableView = tableView;
		__popColumnWidths();
		
		for(var ii = 0; ii < columnSpan; ii++) {
			var col = tableView.getColumn(startColumn + ii);
			console.log("col.widthChanged.connect: col=", col);
			col.widthChanged.connect(recomputeRequested);
		}
	}
	
	// berechnet die breite ueber den column span, oder breite = 28, wenn collapsed
	function __computeWidth() {
		var width = 0;
		if (collapsed) {
			width = 28;
		}
		else {
			for(var ii = 0; ii < columnSpan; ii++) {
				width += __tableView.getColumn(ii + __startColumn).width;
			}
		}
		return width;
	}
	
	// animationen! das tut so dass man zu beginn die breiten merkt und 
	// anschliessend dies breiten im tableview animiert.
	states: [
		State {
			name: "collapsed"
			PropertyChanges { target: self; animColumnMutltip: 0.0 }
			PropertyChanges { target: self; collapsed: true }
		},
		State {
			name: "notcollapsed"
			PropertyChanges { target: self; animColumnMutltip: 1.0 }
			PropertyChanges { target: self; collapsed: false }
		}
	]
	
	transitions: Transition {
		id: transition
		SequentialAnimation {
			ScriptAction { script: __popColumnWidths(); }
			ScriptAction { script: __showColumns(true); }

			NumberAnimation { properties: "animColumnMutltip"; duration: 150 }
			PropertyAction { target: self; property: "collapsed" }

			ScriptAction { script: __showColumns(!collapsed); }
			ScriptAction { script: __pushColumnWidths(); }
		}
    }
	
	function __popColumnWidths() {
		__columnWitdhs = [];
		for(var ii = 0; ii < columnSpan; ii++) {
			var curcol = __tableView.getColumn(ii + __startColumn);
			if (curcol == null) {
				console.log("__popColumnWidths: title=", title, 
					", __startColumn=", __startColumn,
					", columnSpan=", columnSpan);
			}
			__columnWitdhs.push(curcol.width);
		}
	}
	
	function __pushColumnWidths() {
		for(var ii = 0; ii < columnSpan; ii++) {
			var curcol = __tableView.getColumn(ii + __startColumn);
			curcol.width = __columnWitdhs[ii];
		}
	}

	function __showColumns(show) {
		for(var ii = 0; ii < columnSpan; ii++) {
			var curcol = __tableView.getColumn(ii + __startColumn);
			curcol.visible = show;
		}
	}
	
	onAnimColumnMutltipChanged: {
		for(var ii = 0; ii < columnSpan; ii++) {
			var curcol = __tableView.getColumn(ii + __startColumn);
			curcol.width = Math.max(__columnWitdhs[ii] * animColumnMutltip, 28/columnSpan);
		}
	}
}	
