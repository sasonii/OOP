//
// Created by Dell on 27/06/2023.
//

#ifndef HW5_GAMEBOARD_H
#define HW5_GAMEBOARD_H

#include "BoardCell.h"
#include "List.h"

//template<typename BOARDListList>
//struct GameBoard;
//
//template<typename T>
//struct GameBoard <List<List<T>>>{
//    using board = List<List<T>>;
//};

template<typename BoardCells>
struct GameBoard {
    using board = BoardCells;
    static constexpr int width = sizeof(board);
    static constexpr int length = sizeof(board::head);
};

#endif //HW5_GAMEBOARD_H
