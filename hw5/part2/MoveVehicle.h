//
// Created by Dell on 27/06/2023.
//

#ifndef HW5_MOVEVEHICLE_H
#define HW5_MOVEVEHICLE_H

#include "CellType.h"
#include "Direction.h"
#include "Utilities.h"
#include "TransposeList.h"

template <CellType, Direction, int>
struct Move;

template <typename BOARD, int R, int C, Direction D>
struct MoveVehicleOneStep;

template <CellType TYPE, Direction Dir ,int N>
struct Move  {
    static_assert(TYPE != EMPTY, "can't move empty");

    static constexpr CellType type = TYPE;
    static constexpr Direction direction = Dir;
    static constexpr int amount = N;
};

//
template <typename , int, int, Direction, int>
struct MoveVehicle;

template <typename , int, int, Direction, int>
struct MoveVehicleHelper;


//template <typename BOARD, int R, int C, Direction D ,int A>
//struct MoveVehicle  {
//    static_assert(BOARD::length - 1 >= R, "Wrong row index");
//    static_assert(BOARD::width - 1 >= C, "Wrong column index");
//    static_assert(GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value::type != EMPTY, "Can't move EMPTY");
//    static_assert(GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value::direction == D, "Wrong direction");
//};

template <typename BOARD, int R, int C ,int A>
struct MoveVehicle <BOARD, R, C, Direction::RIGHT , A>  {
    static_assert(BOARD::length - 1 >= R, "Wrong row index");
    static_assert(BOARD::width - 1 >= C, "Wrong column index");
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value object;
    static_assert(object::type != EMPTY, "Can't move EMPTY");
    static_assert(object::direction == RIGHT || object::direction == LEFT, "Wrong direction");

    typedef GameBoard<typename MoveVehicleOneStep<typename MoveVehicle <BOARD, R, C, Direction::RIGHT , A-1>::board::board, R, C+A-1, Direction::RIGHT>::board> board;
};

template <typename BOARD, int R, int C >
struct MoveVehicle <BOARD, R, C, Direction::RIGHT, 1>  {
    static_assert(BOARD::length - 1 >= R, "Wrong row index");
    static_assert(BOARD::width - 1 >= C, "Wrong column index");
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value object;
    static_assert(object::type != EMPTY, "Can't move EMPTY");
    static_assert(object::direction == RIGHT || object::direction == LEFT, "Wrong direction");

    typedef GameBoard<typename MoveVehicleOneStep<typename BOARD::board, R, C, Direction::RIGHT>::board> board;
};

template <typename BOARD, int R, int C ,int A>
struct MoveVehicle <BOARD, R, C, Direction::LEFT , A>  {
    static_assert(BOARD::length - 1 >= R, "Wrong row index");
    static_assert(BOARD::width - 1 >= C, "Wrong column index");
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value object;
    static_assert(object::type != EMPTY, "Can't move EMPTY");
    static_assert(object::direction == RIGHT || object::direction == LEFT, "Wrong direction");

    typedef GameBoard<typename MoveVehicleOneStep<typename MoveVehicle <BOARD, R, C, Direction::LEFT , A-1>::board::board, R, C-A+1, Direction::LEFT>::board> board;
};

template <typename BOARD, int R, int C >
struct MoveVehicle <BOARD, R, C, Direction::LEFT, 1>  {
    static_assert(BOARD::length - 1 >= R, "Wrong row index");
    static_assert(BOARD::width - 1 >= C, "Wrong column index");
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value object;
    static_assert(object::type != EMPTY, "Can't move EMPTY");
    static_assert(object::direction == RIGHT || object::direction == LEFT, "Wrong direction");

    typedef GameBoard<typename MoveVehicleOneStep<typename BOARD::board, R, C, Direction::LEFT>::board> board;
};



template <typename BOARD, int R, int C ,int A>
struct MoveVehicle <BOARD, R, C, Direction::UP , A>  {
    static_assert(BOARD::length - 1 >= R, "Wrong row index");
    static_assert(BOARD::width - 1 >= C, "Wrong column index");
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value object;
    static_assert(object::type != EMPTY, "Can't move EMPTY");
    static_assert(object::direction == UP || object::direction == DOWN, "Wrong direction");
    typedef GameBoard<typename Transpose<typename MoveVehicleHelper<GameBoard<typename Transpose<typename BOARD::board>::matrix>, C, R, LEFT, A>::board::board>::matrix> board;
//    typedef GameBoard<Transpose<typename MoveVehicleOneStep<typename MoveVehicle <BOARD, R, C, Direction::UP , A-1>::board::board, C-A+1, R, Direction::LEFT>::board>> board;
};

//template <typename BOARD, int R, int C >
//struct MoveVehicle <BOARD, R, C, Direction::UP, 1>  {
//    static_assert(BOARD::length - 1 >= R, "Wrong row index");
//    static_assert(BOARD::width - 1 >= C, "Wrong column index");
//    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value object;
//    static_assert(object::type != EMPTY, "Can't move EMPTY");
//    static_assert(object::direction == UP || object::direction == DOWN, "Wrong direction");
//
//    typedef GameBoard<typename Transpose<typename MoveVehicleOneStep<typename Transpose<typename BOARD::board>::matrix, C, R, Direction::LEFT>::board>::matrix> board;
//};

template <typename BOARD, int R, int C ,int A>
struct MoveVehicle <BOARD, R, C, Direction::DOWN , A>  {
    static_assert(BOARD::length - 1 >= R, "Wrong row index");
    static_assert(BOARD::width - 1 >= C, "Wrong column index");
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value object;
    static_assert(object::type != EMPTY, "Can't move EMPTY");
    static_assert(object::direction == UP || object::direction == DOWN, "Wrong direction");
    typedef GameBoard<typename Transpose<typename MoveVehicleHelper<GameBoard<typename Transpose<typename BOARD::board>::matrix>, C, R, RIGHT, A>::board::board>::matrix> board;

//    typedef GameBoard<Transpose<typename MoveVehicleOneStep<typename MoveVehicle <BOARD, C, R, Direction::DOWN , A-1>::board::board, R, C+A-1, Direction::RIGHT>::board>> board;
};

//template <typename BOARD, int R, int C >
//struct MoveVehicle <BOARD, R, C, Direction::DOWN, 1>  {
//    static_assert(BOARD::length - 1 >= R, "Wrong row index");
//    static_assert(BOARD::width - 1 >= C, "Wrong column index");
//    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value object;
//    static_assert(object::type != EMPTY, "Can't move EMPTY");
//    static_assert(object::direction == UP || object::direction == DOWN, "Wrong direction");
//
//    typedef GameBoard<typename Transpose<typename MoveVehicleOneStep<typename Transpose<typename BOARD::board>::matrix, C, R, Direction::RIGHT>::board>::matrix> board;
//};

// HELPERS

template <typename BOARD, int R, int C ,int A>
struct MoveVehicleHelper <BOARD, R, C, Direction::RIGHT , A>  {
    static_assert(BOARD::length - 1 >= R, "Wrong row index");
    static_assert(BOARD::width - 1 >= C, "Wrong column index");
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value object;
    static_assert(object::type != EMPTY, "Can't move EMPTY");
    static_assert(object::direction == UP || object::direction == DOWN, "Wrong direction");

    typedef GameBoard<typename MoveVehicleOneStep<typename MoveVehicleHelper <BOARD, R, C, Direction::RIGHT , A-1>::board::board, R, C+A-1, Direction::RIGHT>::board> board;
};

template <typename BOARD, int R, int C>
struct MoveVehicleHelper <BOARD, R, C, Direction::RIGHT, 1>  {
    static_assert(BOARD::length - 1 >= R, "Wrong row index");
    static_assert(BOARD::width - 1 >= C, "Wrong column index");
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value object;
    static_assert(object::type != EMPTY, "Can't move EMPTY");
    static_assert(object::direction == UP || object::direction == DOWN, "Wrong direction");

    typedef GameBoard<typename MoveVehicleOneStep<typename BOARD::board, R, C, Direction::RIGHT>::board> board;
};

template <typename BOARD, int R, int C ,int A>
struct MoveVehicleHelper <BOARD, R, C, Direction::LEFT , A>  {
    static_assert(BOARD::length - 1 >= R, "Wrong row index");
    static_assert(BOARD::width - 1 >= C, "Wrong column index");
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value object;
    static_assert(object::type != EMPTY, "Can't move EMPTY");
    static_assert(object::direction == UP || object::direction == DOWN, "Wrong direction");

    typedef GameBoard<typename MoveVehicleOneStep<typename MoveVehicleHelper <BOARD, R, C, Direction::LEFT , A-1>::board::board, R, C-A+1, Direction::LEFT>::board> board;
};

template <typename BOARD, int R, int C>
struct MoveVehicleHelper <BOARD, R, C, Direction::LEFT, 1>  {
    static_assert(BOARD::length - 1 >= R, "Wrong row index");
    static_assert(BOARD::width - 1 >= C, "Wrong column index");
    typedef typename GetAtIndex<C, typename GetAtIndex<R,typename BOARD::board>::value>::value object;
    static_assert(object::type != EMPTY, "Can't move EMPTY");
    static_assert(object::direction == UP || object::direction == DOWN, "Wrong direction");

    typedef GameBoard<typename MoveVehicleOneStep<typename BOARD::board, R, C, Direction::LEFT>::board> board;
};

// ONE STEP

template <typename BOARD, int R, int C>
struct MoveVehicleOneStep <BOARD, R, C, Direction::RIGHT>  {
    typedef typename GetAtIndex<R, BOARD>::value list_to_update;
    typedef typename GetAtIndex<C, list_to_update>::value object;
    typedef typename GetAtIndex<C-1, list_to_update>::value close_object;

    // POSSIBLE UPDATE IF IT IS THE FIRST ELEMENT
    static constexpr int object_lentgh = object::length;

    static constexpr int index = ConditionalInteger<close_object::type != object::type,
                                                    object_lentgh + C,
                                                    C
                                                    >::value;
    static_assert(index <= BOARD::head::size - 1, "can't move out of bounds");
    typedef typename GetAtIndex<index, list_to_update>::value object_to_replace;
    static_assert(!(close_object::type != object::type && object_to_replace::type != EMPTY), "can't move because there is another object in the way");

    typedef typename SetAtIndex<index, object, list_to_update>::list first_updated_list;
    typedef typename SetAtIndex<C, object_to_replace, first_updated_list>::list updated_list;
    typedef typename SetAtIndex<R, updated_list, BOARD>::list possible_updated_board;

    typedef typename Conditional<close_object::type == object::type,
                                typename MoveVehicleOneStep <BOARD, R, C-1, Direction::RIGHT>::board,
                                possible_updated_board
                                >::value board;

};

template <typename BOARD, int R>
struct MoveVehicleOneStep <BOARD, R, 0, Direction::RIGHT >  {
    typedef typename GetAtIndex<R, BOARD>::value list_to_update;
    typedef typename GetAtIndex<0, list_to_update>::value object;
    static constexpr int object_lentgh = object::length;

    static_assert(object_lentgh <= BOARD::head::size - 1, "can't move out of bounds");
    typedef typename GetAtIndex<object_lentgh, list_to_update>::value object_to_replace;
    static_assert(object_to_replace::type == EMPTY, "can't move because there is another object in the way");

    typedef typename SetAtIndex<object_lentgh, object, list_to_update>::list first_updated_list;
    typedef typename SetAtIndex<0, object_to_replace, first_updated_list>::list updated_list;
    typedef typename SetAtIndex<R, updated_list, BOARD>::list board;
};

template <typename BOARD, int R, int C>
struct MoveVehicleOneStep <BOARD, R, C, Direction::LEFT>  {
    typedef typename GetAtIndex<R, BOARD>::value list_to_update;
    typedef typename GetAtIndex<C, list_to_update>::value object;
    typedef typename GetAtIndex<C-1, list_to_update>::value close_object;

    // POSSIBLE UPDATE IF IT IS THE FIRST ELEMENT
    static constexpr int object_length = object::length;

    static constexpr int index = ConditionalInteger<close_object::type != object::type,
                                                    object_length + C - 1,
                                                    C
                                                    >::value;

//    static_assert(C + object_length >= 0);
    typedef typename GetAtIndex<index, list_to_update>::value object_to_replace;

//    static_assert(C+1 <= BOARD::width - 1);
//    typedef typename GetAtIndex<C+1, list_to_update>::value close_object;
    static_assert(!(close_object::type != EMPTY && close_object::type != object::type), "can't move because there is another object in the way");

    typedef typename SetAtIndex<index, close_object, list_to_update>::list first_updated_list;
    typedef typename SetAtIndex<C - 1, object, first_updated_list>::list updated_list;
    typedef typename SetAtIndex<R, updated_list, BOARD>::list possible_updated_board;

    typedef typename Conditional<close_object::type == object::type,
                                            typename MoveVehicleOneStep <BOARD, R, C-1, Direction::LEFT>::board,
                                            possible_updated_board
                                            >::value board;

};

template <typename BOARD, int R>
struct MoveVehicleOneStep <BOARD, R, 1, Direction::LEFT >  {
    typedef typename GetAtIndex<R, BOARD>::value list_to_update;
    typedef typename GetAtIndex<1, list_to_update>::value object;
    typedef typename GetAtIndex<0, list_to_update>::value close_object;
    static constexpr int object_length = object::length;

//    static_assert(object_lentgh <= BOARD::width - 1);
//    typedef typename GetAtIndex<object_lentgh, list_to_update>::value object_to_replace;
    static_assert(close_object::type == EMPTY, "can't move because there is another object in the way");

    typedef typename SetAtIndex<object_length, close_object, list_to_update>::list first_updated_list;
    typedef typename SetAtIndex<0, object, first_updated_list>::list updated_list;
    typedef typename SetAtIndex<R, updated_list, BOARD>::list board;
};

#endif //HW5_MOVEVEHICLE_H
