import QtQuick 2.0
import Game 1.0;


GridView {
    id: root
    model: GameBoardModel{

    }

    cellHeight: height / root.model.dimension
    cellWidth: width / root.model.dimension

    delegate: Item{
        id: _backgroundDelegate
        width: root.cellWidth
        height: root.cellHeight

        Tile{
            anchors.fill: _backgroundDelegate
            anchors.margins: 5

            displayText: display //в runtime происходит поиск такой роли у делегата
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    root.model.move(index);
                }
            }
        }

    }
}

