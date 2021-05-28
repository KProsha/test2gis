import QtQuick 2.15
import QtQuick.Controls 2.15
import HistogramModel 1.0

Rectangle {
    id:root

    color: "white"
    property color columnColor: "lightblue"
    property color borderColor: "blue"

    property HistogramModel model: ;

    property int axisX: 200
    property int axisY: 40
    property int margin: 40
    property int spacing: 2

    property var fontName: "Courier"
    property int fontHeight: 14

    Text {
        id: fileName
        text: root.model.fileName
        anchors.top: parent.top
        anchors.topMargin: margin
        anchors.horizontalCenter: parent.horizontalCenter

        font.family: fontName
        font.pixelSize: fontHeight
    }

    Column{
        id:field

        spacing: root.spacing

        height: root.height - axisY - margin * 2
        width: root.width - axisX - margin
        x: margin
        y: margin + fileName.height

        Repeater{
            model: root.model

            Rectangle {
                height: (field.height - (field.spacing * root.model.rowCount())) / root.model.count
                width: field.width - 80

                Rectangle{
                    x: axisX - margin
                    height: parent.height
                    width: parent.width / root.model.maxValue * valueRole

                    border.color: root.borderColor
                    border.width: 3

                    color: root.columnColor

                    Text {
                        text: valueRole
                        x: parent.parent.width + 10
                        font.family: fontName
                        font.pixelSize: fontHeight
                    }

                }

                Text {
                    TextMetrics {
                       id: textMetrics
                       font.family: fontName
                       font.pixelSize: fontHeight
                       text: root.model.headerData(index, Qt.Horizontal)
                    }

                    font: textMetrics.font
                    text: textMetrics.text
                    x: axisX - margin - textMetrics.width - 10
                }
            }
        }
    }

    Rectangle{
        color: "transparent"
        border.color:  "black"
        border.width: 2
        x: axisX - 2
        width: field.width - 75
        y: field.y
        height:  field.height
    }

    ProgressBar {
        id: progressBar
        x: margin
        y: parent.height - margin - height
        width: parent.width - margin * 2

        from: 0
        to: 100

        value: 0.5
    }


}


