#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMessageLogContext>
#include <QAbstractListModel>

#include <string>
#include "DynamicArray.h"

class Tile{
public:
    std::string value {};

    Tile& operator = (const std::string newValue){
        value = newValue;
        return *this;
    }

    bool operator == (const std::string other){
        return other == value;
    }
    bool operator != (const std::string other){
        return other != value;
    }
};

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimension READ dimension CONSTANT)

public:
    int result = -1;
    static constexpr size_t defaultPuzzleDimension{3};
    GameBoard(const size_t boardDimension = defaultPuzzleDimension,
              QObject* parent = nullptr);


    Q_INVOKABLE bool move(int index);

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
    QVariant data(const QModelIndex& index,int role = Qt::DisplayRole) const override;

    size_t dimension() const;
    size_t boardSize() const;


private:
    DynamicArray<Tile> m_rawBoard;
    const size_t m_dimension;
    const size_t m_boardSize;
};

#endif // GAMEBOARD_H
