//
// Created by Dell on 27/06/2023.
//
#include <iostream>
#include "temp.h"
#include "RushHour.h"
#include "Printer.h"
#include "TransposeList.h"

void list_printing(){
    std::cout << "---LIST PRINTING---" << std::endl << std::endl;

    // PART 1
    std::cout << "PART 1" << std::endl;
    typedef List<Int<1>, Int<2>, Int<3>> list;
    std::cout << list::head() << std::endl; // = Int<1>

    typedef typename list::next listTail; // = List<Int<2>, Int<3>>
    std::cout << list::size << std::endl; // = 3

    // PART 2
    std::cout << std::endl << "PART 2" << std::endl;
    typedef List<Int<1>, Int<2>, Int<3>> list;
    typedef typename PrependList<Int<4>, list>::list newList; // = List< Int<4>, Int<1>, Int<2>, Int<3>>
    Printer<newList>::print(std::cout);

    // PART 3
    std::cout << std::endl << "PART 3" << std::endl;
    typedef List<Int<1>, Int<2>, Int<3>> list;
    Printer<list>::print(std::cout);

    // PART 4
    std::cout << std::endl << "PART 4" << std::endl;
    typedef List<Int<1>, Int<2>, Int<3>> list;
    Printer<GetAtIndex<0, list>::value>::print(std::cout);// = Int<1>
    std::cout << std::endl;
    Printer<GetAtIndex<2, list>::value>::print(std::cout);// = Int<3>
    std::cout << std::endl;

    // PART 5
    std::cout << std::endl << "PART 5" << std::endl;
    typedef List<Int<1>, Int<2>, Int<3>> list;
    typedef typename SetAtIndex<0, Int<5>, list>::list listA; // = List<Int<5>, Int<2>, Int<3>>
    Printer<listA>::print(std::cout);
    typedef typename SetAtIndex<2, Int<7>, list>::list listB; // = List<Int<1>, Int<2>, Int<7>
    Printer<listB>::print(std::cout);

    // Example 1: Empty list
    typedef List<> EmptyList;
    std::cout << "EmptyList::size = " << EmptyList::size << std::endl;

    // Example 2: Single-item list
    typedef List<int> SingleItemList;
    std::cout << "SingleItemList::size = " << SingleItemList::size << std::endl;
    std::cout << "SingleItemList::head = " << typeid(SingleItemList::head).name() << std::endl;

    // Example 3: Multi-item list
    typedef List<int, double, char> MultiItemList;
    std::cout << "MultiItemList::size = " << MultiItemList::size << std::endl;
    std::cout << "MultiItemList::head = " << typeid(MultiItemList::head).name() << std::endl;
    typedef typename MultiItemList::next NextList;
    std::cout << "NextList::head = " << typeid(NextList::head).name() << std::endl;
}

void utilities_printing(){
    std::cout << "---UTILITIES PRINTING---" << std::endl << std::endl;
    int val = ConditionalInteger<(0 != 1), 0, 1>::value; // = 0
    std::cout << "Val 1: " << val << std::endl;
    val = ConditionalInteger<(0 == 1), 0, 1>::value; // = 1
    std::cout << "Val 2: " << val << std::endl;

    typedef typename Conditional<(0 != 1), Int<0>, Int<1>>::value test1; // = Int<0>
    Printer<test1>::print(std::cout);
    typedef typename Conditional<(0 == 1), Int<0>, Int<1>>::value test2; // = Int<1>
    Printer<test2>::print(std::cout);
}

void move_printing(){
    std::cout << "---Move PRINTING---" << std::endl << std::endl;
//    int amount = Move<EMPTY, UP, 1>::amount; // should not compile

    int amount2 = Move<X, RIGHT, 1>::amount;
    std::cout << "Val 1: " << amount2 << std::endl;
}

void move_vehicle_printing(){
    std::cout << "---MoveVehicle PRINTING---" << std::endl << std::endl;

    // PART 1
    std::cout << "PART 1" << std::endl;
    typedef GameBoard<List< List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
            List< BoardCell<X, RIGHT, 1>, BoardCell<EMPTY, UP, 0>>,
            List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>>> gameBoard;

    Printer<gameBoard>::print(std::cout);
    std::cout << gameBoard::width << std::endl;
    std::cout << gameBoard::length << std::endl << std::endl;

    typedef GameBoard<Transpose<gameBoard::board>::matrix> flipBoard;
    Printer<flipBoard>::print(std::cout);

    typedef MoveVehicleOneStep<gameBoard::board, 1, 0, RIGHT, X>::board updated_board;
    Printer<updated_board>::print(std::cout);

    // PART 2
    std::cout << "PART 2" << std::endl;
    typedef GameBoard<List<
            List< BoardCell<EMPTY, UP, 0>, BoardCell<A, UP, 1>, BoardCell<EMPTY, UP, 0>>,
            List< BoardCell<X, RIGHT, 1>, BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
            List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
            >> gameBoard2;
    Printer<gameBoard2>::print(std::cout);

    typedef MoveVehicleOneStep<gameBoard2::board, 0, 1, RIGHT, A>::board updated_board2;
    Printer<updated_board2>::print(std::cout);

    // PART 3
    std::cout << "PART 3" << std::endl;
    typedef GameBoard<List<
            List< BoardCell<A, RIGHT, 2>, BoardCell<A, UP, 2>, BoardCell<EMPTY, UP, 0>>,
            List< BoardCell<X, RIGHT, 1>, BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
            List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
    >> gameBoard3;
    Printer<gameBoard3>::print(std::cout);

    typedef GameBoard<Transpose<gameBoard3::board>::matrix> flipBoard3;
    Printer<flipBoard3>::print(std::cout);

    typedef MoveVehicle<gameBoard3, 0, 0, RIGHT,1>::board updated_board3;
    Printer<updated_board3>::print(std::cout);


    // PART 4
    std::cout << "PART 4" << std::endl;
    typedef GameBoard<List<
            List< BoardCell<EMPTY, UP, 0>, BoardCell<A, UP, 1>, BoardCell<EMPTY, UP, 0>>,
            List< BoardCell<X, RIGHT, 1>, BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
            List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
    >> gameBoard4;
    Printer<gameBoard4>::print(std::cout);

    typedef MoveVehicleOneStep<gameBoard4::board, 0, 1, LEFT, A>::board updated_board4;
    Printer<updated_board4>::print(std::cout);

    // PART 5
    std::cout << "PART 5" << std::endl;
    typedef GameBoard<List<
            List< BoardCell<EMPTY, UP, 0>, BoardCell<A, LEFT, 2>, BoardCell<A, LEFT, 2>>,
            List< BoardCell<X, RIGHT, 1>, BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
            List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
    >> gameBoard5;
    Printer<gameBoard5>::print(std::cout);

    typedef MoveVehicleOneStep<gameBoard5::board, 0, 1, LEFT, A>::board updated_board5;
    Printer<updated_board5>::print(std::cout);
    typedef MoveVehicleOneStep<gameBoard5::board, 0, 2, LEFT, A>::board updated_board5_2;
    Printer<updated_board5_2>::print(std::cout);

    // PART 6
    std::cout << "PART 6" << std::endl;
    typedef GameBoard<List<
            List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>, BoardCell<A, LEFT, 1>>,
            List< BoardCell<X, RIGHT, 1>, BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
            List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>, BoardCell<B, LEFT, 1>>
    >> gameBoard6;
    Printer<gameBoard6>::print(std::cout);

    typedef MoveVehicle<gameBoard6, 0, 2, LEFT,2>::board updated_board6;
    Printer<updated_board6>::print(std::cout);

    typedef MoveVehicle<gameBoard6, 0, 2, LEFT,1>::board updated_board6_2;
    Printer<updated_board6_2>::print(std::cout);

    typedef MoveVehicle<gameBoard6, 2, 2, LEFT,1>::board updated_board6_3;
    Printer<updated_board6_3>::print(std::cout);

    typedef MoveVehicle<gameBoard6, 2, 2, LEFT,2>::board updated_board6_4;
    Printer<updated_board6_4>::print(std::cout);

    // PART 7
    std::cout << "PART 7" << std::endl;
    typedef GameBoard<List<
            List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
            List< BoardCell<X, RIGHT, 1>, BoardCell<EMPTY, UP, 0>, BoardCell<A, UP, 2>>,
            List< BoardCell<EMPTY, UP, 0>, BoardCell<B, UP, 1>, BoardCell<A, UP, 2>>
    >> gameBoard7;
    Printer<gameBoard7>::print(std::cout);

    typedef GameBoard<Transpose<gameBoard7::board>::matrix> flipBoard7;
    Printer<flipBoard7>::print(std::cout);

    typedef MoveVehicle<gameBoard7, 2, 1, UP,1>::board updated_board7;
    Printer<updated_board7>::print(std::cout);

    typedef MoveVehicle<gameBoard7, 2, 1, UP,2>::board updated_board7_2;
    Printer<updated_board7_2>::print(std::cout);

    typedef MoveVehicle<updated_board7_2, 0, 1, DOWN,1>::board updated_board7_3;
    Printer<updated_board7_3>::print(std::cout);

    typedef MoveVehicle<updated_board7_2, 0, 1, DOWN,2>::board updated_board7_4;
    Printer<updated_board7_4>::print(std::cout);

    typedef MoveVehicle<gameBoard7, 2, 2, UP,1>::board updated_board7_5;
    Printer<updated_board7_5>::print(std::cout);

    typedef GameBoard<Transpose<updated_board7_5::board>::matrix> flipBoard7_2;
    Printer<flipBoard7_2>::print(std::cout);

    typedef MoveVehicle<updated_board7_5, 1, 2, DOWN,1>::board updated_board7_6;
    Printer<updated_board7_6>::print(std::cout);
}

void rush_hour_printing(){
    typedef GameBoard< List<
            List < BoardCell< X , RIGHT , 2>, BoardCell< X , LEFT , 2>, BoardCell< EMPTY , RIGHT , 0> >,
            List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< A , RIGHT , 1> >
    > > gameBoard;
    Printer<gameBoard>::print(std::cout);
    static_assert(CheckWin<gameBoard>::result, "Fail");

    typedef GameBoard< List<
            List < BoardCell< EMPTY , RIGHT , 1>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< O , DOWN , 3>, BoardCell< EMPTY , RIGHT , 0> >,
            List < BoardCell< EMPTY , RIGHT , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< A , RIGHT , 2>, BoardCell< A , LEFT , 2>, BoardCell< O , DOWN , 3>, BoardCell< EMPTY , RIGHT , 0> >,
            List < BoardCell< EMPTY , RIGHT , 3>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< X , RIGHT , 2>, BoardCell< X , LEFT , 2>, BoardCell< O , UP , 3>, BoardCell< EMPTY , RIGHT , 0> >,
            List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >,
            List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , DOWN , 2>, BoardCell< P , RIGHT , 3>, BoardCell< P , RIGHT , 3>, BoardCell< P , LEFT , 3> >,
            List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , UP , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< C , RIGHT , 2>, BoardCell< C , LEFT , 2> >
    > > gameBoard2;
    Printer<gameBoard2>::print(std::cout);
    typedef List<
            Move < B, UP, 1 > , Move < C, LEFT, 4 > , Move < A, LEFT, 2 > , Move < X, LEFT, 2 > , Move < B, UP, 3 > , Move < P, LEFT, 3 > , Move < O, DOWN, 3 >
    > moves;
//
//
    static_assert(List<BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>>::size == 3, "Fail");
    static_assert(List<>::size == 0, "Fail");
    typedef MoveVehicle<gameBoard2, 2, 3, LEFT, 2>::board b1; // Valid move
    typedef MoveVehicle<gameBoard2, 5,2,UP, 1>::board b2;
    typedef MoveVehicle<b2, 5,5,LEFT, 4>::board b3;
    static_assert(CheckSolution<gameBoard2, moves>::result, "Fail"); // Game should be solved

    typedef GameBoard< List<
            List < BoardCell< X , RIGHT , 2>, BoardCell< X , LEFT , 2>, BoardCell< A , DOWN , 1> >,
            List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >
    > > gameBoard3;
    Printer<gameBoard3>::print(std::cout);
    typedef List<
            Move<A,DOWN,1>
    > moves3;
    static_assert(CheckWin<gameBoard>::result, "Fail");
    static_assert(CheckSolution<gameBoard3, moves3>::result, "Fail");
}

int main() {
    list_printing();

    utilities_printing();

    move_printing();

    move_vehicle_printing();

    rush_hour_printing();

    return 0;
}