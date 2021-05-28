import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: applicationWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("histogram")



    Histogram{
        anchors.fill: parent

        model: histogramModel


    }




}


