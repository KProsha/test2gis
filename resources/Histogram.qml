import QtQuick 2.15

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



    Column{
        id:field

        spacing: root.spacing

        height: root.height - axisY - margin * 2
        width: root.width - axisX - margin
        x: margin
        y: margin

        Repeater{
            model: root.model

            Rectangle {
                height: (field.height - (field.spacing * root.model.rowCount())) / root.model.count
                width:field.width

                Rectangle{
                    x: axisX - margin
                    height: parent.height
                    width: parent.width / root.model.maxValue * valueRole

                    border.color: root.borderColor
                    border.width: 3

                    color: root.columnColor

                    Text {
                        text: valueRole
                        x:parent.width / 2
                        font.family: "Courier"
                        font.pixelSize: 14
                    }

                }

                Text {
                    TextMetrics {
                       id: textMetrics
                       font.family: "Courier"
                       font.pixelSize: 14
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
        width: field.width + 4
        y: margin
        height:  field.height
    }


}


