#include "gameboard.h"
#include <algorithm>
#include <random>
#include <stdlib.h>

GameBoard::GameBoard(const size_t boardDimension, QObject *parent) :
    QAbstractListModel {parent},
    m_dimension {boardDimension},
    m_boardSize {m_dimension * m_dimension}
{
    m_rawBoard.Resize(m_boardSize);
    for(int i = 0; i < m_rawBoard.GetSize(); ++i){
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

    if(result != -1){
        for(int i = 0;i<m_rawBoard.GetSize();++i){
            m_rawBoard[i] = empty_cell;
        }
        result = -1;
        emit dataChanged(createIndex(0,0),createIndex(m_boardSize,0));
        return true;
    }



    if(is_valid_move(index,m_rawBoard)){

        m_rawBoard[index].value = user_char;
        if(is_over(m_rawBoard,user_char)){
            result = 1;
            emit dataChanged(createIndex(0,0),createIndex(m_boardSize,0));
            return true;
        }

        AI_move(m_rawBoard);
        if(is_over(m_rawBoard,AI_char)){
            result = 2;
            emit dataChanged(createIndex(0,0),createIndex(m_boardSize,0));
            return true;
        }

        if(is_draw(m_rawBoard)){
            result = 0;
            emit dataChanged(createIndex(0,0),createIndex(m_boardSize,0));
            return true;
        }




        emit dataChanged(createIndex(0,0),createIndex(m_boardSize,0));
        return true;

    }

}

int GameBoard::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_rawBoard.GetSize();
}

QVariant GameBoard::data(const QModelIndex &index, int role) const
{
    const int rowIndex{index.row()};// index.row() - ???????????? ???????????????? ???????????? ????????????,???? ?????????????? ?????????? ????????????????????????,?????? ?????? ???????????? ???? ?????????? ?? ?????????? ???????????? ?????????? ???????? ????????????
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
