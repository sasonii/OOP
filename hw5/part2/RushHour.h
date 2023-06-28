//
// Created by Dell on 27/06/2023.
//

#ifndef HW5_RUSHHOUR_H
#define HW5_RUSHHOUR_H

#include "CellType.h"
#include "Direction.h"
#include "BoardCell.h"
#include "GameBoard.h"
#include "List.h"
#include "MoveVehicle.h"
#include "Utilities.h"

// Declarations
template <typename>
struct CheckWin;

template <typename , typename>
struct CheckSolution;

template <typename, typename, int>
struct CheckSolutionAux;

template <typename, int, int, CellType>
struct FindIndexes;

template <typename, int, int, int>
struct CheckWayEmpty;

// Check Win
template <typename Board>
struct CheckWin{
    typedef FindIndexes<Board, Board::length - 1, Board::width - 1, CellType::X> position;
    static constexpr int row = position::row;
    static constexpr int col = position::col;
    static constexpr bool result = CheckWayEmpty<Board, row, col+1, Board::width - col - 1>::result;
};


template <typename Board, int R, int C, int Left>
struct CheckWayEmpty{
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename Board::board>::value>::value object;
    static constexpr bool result = object::type == EMPTY && CheckWayEmpty<Board, R, C+1, Left-1>::result;
};

template <typename Board, int R, int C>
struct CheckWayEmpty<Board, R, C, 1>{
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename Board::board>::value>::value object;
    static constexpr bool result = object::type == EMPTY;
};

template <typename Board, int R, int C>
struct CheckWayEmpty<Board, R, C, 0>{
    static constexpr bool result = true;
};

template <typename Board, CellType Type>
struct FindIndexes<Board, 0, 0, Type>{
    typedef typename GetAtIndex<0, typename GetAtIndex<0,typename Board::board>::value>::value object;
//    static_assert(object::type == Type);
    static constexpr int row = 5;
    static constexpr int col = 2;
};

template <typename Board , int C, CellType Type>
struct FindIndexes<Board, 0, C, Type>{
    typedef typename GetAtIndex<C, typename GetAtIndex<0,typename Board::board>::value>::value object;

    static constexpr int row = ConditionalInteger<object::type == Type,
                                                0,
            FindIndexes<Board, Board::length-1, C-1, Type>::row
                                                >::value;
    static constexpr int col = ConditionalInteger<object::type == Type,
                                                C,
            FindIndexes<Board, Board::length-1, C-1, Type>::col
                                                >::value;
};

template <typename Board, int R, int C, CellType Type>
struct FindIndexes{
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename Board::board>::value>::value object;

    static constexpr int row = ConditionalInteger<object::type == Type,
                                                R,
                                                FindIndexes<Board, R-1, C, Type>::row
                                                >::value;
    static constexpr int col = ConditionalInteger<object::type == Type,
                                                C,
                                                FindIndexes<Board, R-1, C, Type>::col
                                                >::value;
};

template <typename Board , typename Moves>
struct CheckSolution{
    typedef typename CheckSolutionAux<Board, Moves, Moves::size>::board board;
    static constexpr bool result = CheckWin<board>::result;
};

template <typename Board>
struct CheckSolution<Board, List<>>{
    static constexpr bool result = CheckWin<Board>::result;
};

template <typename Board, typename T, typename... Ts, int Left>
struct CheckSolutionAux<Board, List<T, Ts...>, Left>{
    typedef T move;
    typedef FindIndexes<Board, Board::length - 1, Board::width - 1, move::type> position;
    typedef typename MoveVehicle<Board, position::row, position::col, move::direction, move::amount>::board one_move_board;
    typedef typename CheckSolutionAux<one_move_board, List<Ts...>, Left - 1>::board board;
};

template <typename Board, typename T>
struct CheckSolutionAux<Board, List<T>, 1>{
    typedef T move;
    typedef FindIndexes<Board, Board::length - 1, Board::width - 1, move::type> position;
    typedef typename MoveVehicle<Board, position::row, position::col, move::direction, move::amount>::board board;
};

#endif //HW5_RUSHHOUR_H
