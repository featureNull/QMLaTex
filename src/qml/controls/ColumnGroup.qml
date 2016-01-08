import QtQuick 2.2
import QtQuick.Controls 1.2

Item {
	// zu wekchem table ist das gespaxt
	property TableView tableView
	
	/** The current Item count */
	readonly property int count: __groupitems.count	
	
	function clear() {
		while (count > 0)
			removeGroup(count-1);
	}
	
	/** nimmt ein scheissding raus */
	function removeGroup(index) {
		var item = __groupitems.get(index).item;
		__groupitems.remove(index, 1)
		item.destroy();
	}
	
	/*! Returns the \l Tab item at \a index. */
    function getGroup(index) {
        var data = __groupitems.get(index)
        return data && data.item
    }
	
	/** */
	function redraw() {
		__computeChildrenSize();
	}
	
	/** erweitert die group um ein item am ende
	  * @param title in string wie der anzeige name 
	  * @param columnspan int ueber wieviele spalten geht es
	  * @returns erstelltes neues ColumnGroupItem
	  */
	function appendGroup(title, columnspan) {
		// walk through all parents and figure out start column
		var colstart = 0;

		for (var ii = 0; ii < __groupitems.count; ii++) {
			var item = __groupitems.get(ii).item;
			colstart += item.columnSpan;
		}
			
		console.debug("create Columngroup: title=", title, 
			", tableView.columnCount=", tableView.columnCount,
			", columnspan=", columnspan, ", colstart=", colstart);

		var component = Qt.createComponent("ColumnGroupItem.qml");
		console.assert(component.status == Component.Ready, "ColumnGroupItem.qml may broken");

		var groupi = component.createObject();
		groupi.parent = self;
		groupi.title = title;
		groupi.columnSpan = columnspan;
		groupi.collapsedChanged.connect(__computeChildrenSize);
		groupi.__init(colstart, tableView);
		groupi.recomputeRequested.connect(__computeChildrenSize);
		
		__groupitems.append({item: groupi});
		return groupi;
	}
	
	// nicht aus dem kontext malen
	layer.enabled: true
	
	id: self
	height: 25;

	//
	// internals
	//
    property ListModel __groupitems: ListModel { }
	property bool __completed: false

	Component.onCompleted: {
		console.log("ColumnGroup.onComplete");

		tableView.flickableItem.contentXChanged.connect(__computeChildrenSize);
		/*

		for(var ii = 0; ii < tableView.columnCount; ii++) {
			var col = tableView.getColumn(ii);
			col.widthChanged.connect(__computeChildrenSize);
		}

		var curcol = 0;
		for (var ii in children) {
			var child = children[ii];
			child.collapsedChanged.connect(__computeChildrenSize);
			child.__init(curcol, self.tableView);
			curcol += child.columnSpan;
			
			// in listmodel reinpaxn
			__groupitems.append({item: child});
		}
		*/
		__computeChildrenSize();
		__completed = true
	}

	function __computeChildrenSize() {
		var startx = -tableView.flickableItem.contentX;		
		var stealPlace = 0;
		
		for (var ii = 0; ii < __groupitems.count; ii++) {
			var item = __groupitems.get(ii).item;
			var width = 0;
			
			if (item.collapsed) {
				width = item.__computeWidth();
				stealPlace += width;
			}
			else {
				width = item.__computeWidth() - stealPlace;
				stealPlace = 0;
			}

			// ding ist vollends sichtbar
			item.visible = true;
			item.x = startx;
			item.width = width;

			startx = startx + width;
		}
	}
}
