import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0


Window {
    id:root

    width: 640
    height: 480
    visible: true
    title: qsTr("Tic - tac - toe")


    GameBoard{//инкапсуляции нашего класса
        anchors.fill: parent //тк доска занимает всё окно
    }

}


