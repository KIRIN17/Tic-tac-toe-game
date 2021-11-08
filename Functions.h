#include "DynamicArray.h"
#include <string>
#include<limits>

template <typename T>
bool is_valid_move(int index,DynamicArray<T>& map){
    return map[index] == " ";
}


template <typename T>
int is_over(DynamicArray<T>& map, std::string c){
    int count;
    for (int i = 0; i < map.GetSize(); i += 3) {
        count = 0;
        for (int j = i; j < i + 3; ++j) {
            if (map[j] == c)
                ++count;
        }
        if(count == 3 && c == "X")
            return 1;
        if(count == 3 && c == "O")
            return 2;

    }

    for (int i = 0; i < 3; ++i) {
        count = 0;
        for (int j = i; j < map.GetSize(); j += 3) {
            if (map[j] == c)
                ++count;
        }
        if(count == 3 && c == "X")
            return 1;
        if(count == 3 && c == "O")
            return 2;
    }

    if(map[2] == c && map[4] == c && map[6] == c || map[0] == c && map[4] == c && map[8] == c){
        if(c == "X")
            return 1;
        if(c == "O")
            return 2;
    }


    return 0;
}


template <typename T>
bool is_draw(DynamicArray<T>& map){
    int count = 0;
    for (int i = 0; i < map.GetSize(); ++i) {
        if(map[i] != " ")
            ++count;
    }
    return count == 9;
}

template <typename T>
int minimax(DynamicArray<T>& board,bool AI_or_USER){
    if(is_over(board,"O"))
        return 100;
    if(is_over(board,"X"))
        return -100;
    if(is_draw(board))
        return 0;
    int best_score = std::numeric_limits<int>::min();
    if(AI_or_USER){
         best_score = std::numeric_limits<int>::min();
        for (int i = 0; i < board.GetSize(); ++i) {
            if(board[i] == " "){
                board[i] = "O";
                int score = minimax(board, false);
                board[i] = " ";
                best_score = std::max(best_score,score);
            }
        }
    }else{
        best_score = std::numeric_limits<int>::max();
        for (int i = 0; i < board.GetSize(); ++i) {
            if(board[i] == " "){
                board[i] = "X";
                int score = minimax(board, true);
                board[i] = " ";
                best_score = std::min(best_score,score);
            }
        }
    }

    return best_score;
}

template <typename T>
void AI_move(DynamicArray<T>& map){

    int move = -1;
    int best_score = std::numeric_limits<int>::min();


    DynamicArray<T> board(map.GetSize());
    for(int i = 0;i < map.GetSize(); ++i){
        board[i] = map[i];
    }


    for (int i = 0; i < board.GetSize(); ++i) {
        if(board[i] == " "){
            board[i] = "O";
            int score = minimax(board, false);
            board[i] = " ";
            if(score > best_score){
                best_score = score;
                move = i;
            }
        }
    }
    if(move != -1)
        map[move] = "O";

}
