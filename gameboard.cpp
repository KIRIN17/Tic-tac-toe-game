#include "gameboard.h"
#include <algorithm>
#include <random>
#include "Functions.h"
#include <stdlib.h>

GameBoard::GameBoard(const size_t boardDimension, QObject *parent) :
    QAbstractListModel {parent},
    m_dimension {boardDimension},
    m_boardSize {m_dimension * m_dimension}
{
    m_rawBoard.Resize(m_boardSize);
    for(int i = 0;i<m_rawBoard.GetSize();i++){
        m_rawBoard[i].value = " ";
    }

}

bool GameBoard::move(int index)
{
    if(result == 0){
        for(int i = 0; i < m_rawBoard.GetSize(); ++i){
            m_rawBoard[i].value = "DRAW";
        }
        result = 3;
        emit dataChanged(createIndex(0,0),createIndex(m_boardSize,0));
        return true;
    }

    if(result == 1){
        for(int i = 0; i < m_rawBoard.GetSize(); ++i){
            m_rawBoard[i].value = "WIN";
        }
        result = 3;
        emit dataChanged(createIndex(0,0),createIndex(m_boardSize,0));
        return true;
    }
    if(result == 2){
        for(int i = 0; i < m_rawBoard.GetSize(); ++i){
            m_rawBoard[i].value = "LOSE";
        }
        result = 3;
        emit dataChanged(createIndex(0,0),createIndex(m_boardSize,0));
        return true;
    }

    if(result != -1)
        exit(0);


    if(is_valid_move(index,m_rawBoard)){

        m_rawBoard[index].value = "X";
        AI_move(m_rawBoard);

        if(is_draw(m_rawBoard))
            result = 0;

        if(is_over(m_rawBoard,"X"))
            result = 1;

        if(is_over(m_rawBoard,"O"))
            result = 2;


        emit dataChanged(createIndex(0,0),createIndex(m_boardSize,0));

    }

}

int GameBoard::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_rawBoard.GetSize();
}

QVariant GameBoard::data(const QModelIndex &index, int role) const
{
    const int rowIndex{index.row()};// index.row() - способ получить индекс ячейки,на которую нажал пользователь,так как каждая из ячеек в нашей модели имеет свой индекс
    return QString::fromStdString(m_rawBoard.Get(rowIndex).value);
}


size_t GameBoard::dimension() const
{
    return m_dimension;
}

size_t GameBoard::boardSize() const
{
    return m_boardSize;
}
