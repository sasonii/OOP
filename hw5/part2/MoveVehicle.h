//
// Created by Dell on 27/06/2023.
//

#ifndef HW5_MOVEVEHICLE_H
#define HW5_MOVEVEHICLE_H

#include "CellType.h"
#include "Direction.h"

template <CellType, Direction, int>
struct Move;


template <CellType TYPE, Direction Dir ,int N>
struct Move  {
    static_assert(TYPE != EMPTY);

    static constexpr CellType type = TYPE;
    static constexpr Direction direction = Dir;
    static constexpr int amount = N;
};

//
//template <typename BOARD, Direction, int>
//struct MoveVehicle;


template <typename BOARD, int R, int C, Direction D ,int A>
struct MoveVehicle  {
    static_assert(BOARD::length - 1 >= R, "Wrong row index");
    static_assert(BOARD::width - 1 >= C, "Wrong column index");
    static_assert(GetAtIndex<C, typename GetAtIndex<R,BOARD>::value>::value::type != EMPTY, "Can't move EMPTY");
    static_assert(GetAtIndex<C, typename GetAtIndex<R,BOARD>::value>::value::direction == D, "Wrong direction");

};

#endif //HW5_MOVEVEHICLE_H
