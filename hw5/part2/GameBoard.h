//
// Created by Dell on 27/06/2023.
//

#ifndef HW5_GAMEBOARD_H
#define HW5_GAMEBOARD_H

#include "BoardCell.h"
#include "List.h"

template<typename List>
struct GameBoard ;

template <typename List>
struct GameBoard {
    using board = List;
    static constexpr int width = board::head::size;
    static constexpr int length = List::size;
};
#endif //HW5_GAMEBOARD_H
