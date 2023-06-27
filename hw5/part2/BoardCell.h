//
// Created by Dell on 27/06/2023.
//

#ifndef HW5_BOARDCELL_H
#define HW5_BOARDCELL_H

#include "Direction.h"
#include "CellType.h"

//template<typename TYPE, Direction, int>
//struct BoardCell;

template <CellType TYPE,Direction Y, int X>
struct BoardCell {
    static constexpr CellType type = TYPE;
    static constexpr Direction direction = Y;
    static constexpr int length = X;
};

#endif //HW5_BOARDCELL_H
