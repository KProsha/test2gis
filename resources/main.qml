import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: applicationWindow
    minimumWidth: 640
    minimumHeight: 480
    visible: true
    title: qsTr("histogram")

    Button {
        id: button
        width: 144
        height: 40
        text: qsTr("Пуск")
        anchors.right: parent.right
        anchors.top: parent.top

        onClicked: {
            backend.setFileName(fileNameInput.text);
        }

    }

    Rectangle {
        id: rectangle
        y: 6
        height: 20
        color: "#ffffff"
        border.width: 2
        anchors.verticalCenter: button.verticalCenter
        anchors.left: parent.left
        anchors.right: button.left
        anchors.rightMargin: 10
        anchors.leftMargin: 10

        TextInput {
            id: fileNameInput
            text: qsTr("Имя файла")
            anchors.fill: parent
            font.pixelSize: 12
            anchors.leftMargin: 10
        }
    }


    Histogram{
        anchors.left: parent.left
        anchors.top: button.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        model: histogramModel
    }

}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1}D{i:3}D{i:2}
}
##^##*/
