#include "DynamicArray.h"
#include <string>
#include<limits>

const std::string user_char = "X";
const std::string AI_char = "O";
const std::string empty_cell = " ";
const int N = 5;
const int win_length = 3;
const int max_depth = 3;

template <typename T>
bool is_valid_move(int index,DynamicArray<T>& map){
    return map[index] == empty_cell;
}


template <typename T>
int is_over(DynamicArray<T>& map, std::string c){
    for (int i = 0; i < (N - win_length + 1) * N; i += N) {// главные диагонали 3 на 3
        for (int j = 0; j < N - win_length + 1; ++j) {
            if(map[i + j] == c && map[i + j + (N + 1)] == c && map[i + j + (N + 1) * 2] == c && c == user_char)
                return 1;
            if(map[i + j] == c && map[i + j + (N + 1)] == c && map[i + j + (N + 1) * 2] == c && c == AI_char)
                return 2;
        }
    }

    for (int i = 2; i < (N - win_length + 1) * N; i += N) {// побочные диагонали 3 на 3
        for (int j = 0; j < N - win_length + 1; ++j) {
            if(map[i + j] == c && map[i + j + (N - 1)] == c && map[i + j + (N - 1) * 2] == c && c == user_char)
                return 1;
            if(map[i + j] == c && map[i + j + (N - 1)] == c && map[i + j + (N - 1) * 2] == c && c == AI_char)
                return 2;
        }
    }

    for (int i = 0; i < map.GetSize(); i += N) {// строки длины 3
        for (int j = 0; j < N - win_length + 1; ++j) {
            if(map[i + j] == c && map[i + j + 1] == c && map[i + j + 2] == c && c == user_char)
                return 1;
            if(map[i + j] == c && map[i + j + 1] == c && map[i + j + 2] == c && c == AI_char)
                return 2;
        }
    }

    for (int i = 0; i < (N - win_length + 1) * N; i += N) {// столбцы длины 3
        for (int j = 0; j < N; ++j) {
            if(map[i + j] == c && map[i + j + N] == c && map[i + j + N * 2] == c && c == user_char)
                return 1;
            if(map[i + j] == c && map[i + j + N] == c && map[i + j + N * 2] == c && c == AI_char)
                return 2;
        }
    }
    return 0;
}


template <typename T>
bool is_draw(DynamicArray<T>& map){
    int count = 0;
    for (int i = 0; i < map.GetSize(); ++i) {
        if(map[i] != empty_cell)
            ++count;
    }
    return count == N * N;
}

template <typename T>
int minimax(DynamicArray<T>& board,int depth,bool AI_or_USER){
    if(depth < max_depth){
        if(is_over(board,AI_char))
            return 100;
        if(is_over(board,user_char))
            return -100;
        if(is_draw(board))
            return 0;
        int best_score = std::numeric_limits<int>::min();
        if(AI_or_USER){
             best_score = std::numeric_limits<int>::min();
            for (int i = 0; i < board.GetSize(); ++i) {
                if(board[i] == empty_cell){
                    board[i] = AI_char;
                    int score = minimax(board,depth + 1,false);
                    board[i] = empty_cell;
                    best_score = std::max(best_score,score);
                }
            }
        }else{
            best_score = std::numeric_limits<int>::max();
            for (int i = 0; i < board.GetSize(); ++i) {
                if(board[i] == empty_cell){
                    board[i] = user_char;
                    int score = minimax(board,depth + 1,true);
                    board[i] = empty_cell;
                    best_score = std::min(best_score,score);
                }
            }
        }

        return best_score;
    }
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
        if(board[i] == empty_cell){
            board[i] = AI_char;
            int score = minimax(board,0,false);
            board[i] = empty_cell;
            if(score > best_score){
                best_score = score;
                move = i;
            }
        }
    }
    if(move != -1)
        map[move] = AI_char;

}
