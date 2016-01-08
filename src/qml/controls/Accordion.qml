import QtQuick 2.2;
import QtQuick.Layouts 1.1;
import QtQuick.Controls 1.2;
import QtQuick.Controls.Styles 1.2;

Column {
    id: accordion;
    onHeightChanged:   { relayout (currentGroupItem); }
    onChildrenChanged: { relayout (currentGroupItem); }

    property int barSize: 36;
    property int contentHeight: (height - barSize);
    property Item currentGroupItem: null;

    function relayout (groupItem) {
        currentGroupItem = groupItem;
        var totalGroups    = 0;
        var expandedGroups = 0;
        for (var idx = 0; idx < children.length; idx++) {
            var item = children [idx];
            if ("expanded" in item) {
                totalGroups++;
                item ["expanded"] = (currentGroupItem === item);
                if (item ["expanded"]) {
                    expandedGroups++;
                }
            }
        }
        var tmp = height;
        tmp -= (barSize * totalGroups);
        if (expandedGroups) {
            tmp /= expandedGroups;
        }
        contentHeight = tmp;
    }
}
