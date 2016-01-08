import QtQuick 2.5
import "../styles"

/**
 * @brief gibt dem Benutzer eine idee, welchen tab mit welcher test art er gerade bewundert
 * @details Dabei gibt die Hintergrund Farbe eine Idee der Test Art (PullTest, Sheartest, etc..)
 * Ein zuseatzliches Icon beschreibt die Sicht (Werkzeug, Trend Ansicht, Los Ansicht)
 */
Item {
    id: self
    /** setup des tests, beinhaltet kopf und ob die Tests zerstoerend oder nicht zerstoerend sind
      * \li	InvalidEnvironment = 0,
      * \li	PulltestDestruct = 1
      * \li	PulltestNoneDestruct = 2
      * \li	SheartestDestruct = 3
      * \li	SheartestNoneDestruct = 4
      * \li	TweezertestDestruct = 5
      * \li	TweezertestNoneDestruct = 6
      */
    property int environment

    /** gibt die ansicht auf man dabei verwendet
      * \li "tool" entsprechendes Werkzeug
      * \li "trend" Losuebersicht
      * \li "lot" Verteilung eines einzelnen Loses
      */
    property string view

    Rectangle {
        id: tabIcon
        anchors.fill: parent
        anchors.margins: 0
        color: {
            if (self.environment==0)
                return "transparent"
            if (self.environment==1)
                return "#f3af00"
            if (self.environment==2)
                return "#f3af00"
            if (self.environment==3)
                return "#b93ae0"
            if (self.environment==4)
                return "#b93ae0"
            if (self.environment==5)
                return "#006488"
            if (self.environment==6)
                return "#006488"
            return "transparent"
        }

        Image {
            id: thumbnail
            anchors.fill:parent
            source: {
                if (self.view=="tool") {
                    if (self.environment==0)
                        return "http://images.clipshrine.com/getimg/PngMedium-praying-hands-2992.png"
                    if (self.environment==1)
                        return "qrc:/res/hook.svg";
                    if (self.environment==2)
                        return "qrc:/res/hook.svg";
                    if (self.environment==3)
                        return "qrc:/res/wedge.svg"
                    if (self.environment==4)
                        return "qrc:/res/wedge.svg"
                    if (self.environment==5)
                        return "qrc:/res/tweezer.svg"
                    if (self.environment==6)
                        return "qrc:/res/tweezer.svg"
                }
                if (self.view=="trend")
                    return "qrc:/res/chart.svg"
                if (self.view=="lot")
                    return "qrc:/res/bars.svg"
                return null
            }
        }
    }
}

