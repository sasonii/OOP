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

int main() {
    //list_printing();

//    utilities_printing();

    move_printing();

    typedef GameBoard<List< List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
            List< BoardCell<X, RIGHT, 1>, BoardCell<A, UP, 1>>,
            List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>>> gameBoard;
    Printer<gameBoard>::print(std::cout);

    Printer<gameBoard>::print(std::cout);
    std::cout << gameBoard::width << std::endl;
    std::cout << gameBoard::length << std::endl;
    
    typedef Transpose<gameBoard::board>::matrix flipBoard;
    Printer<flipBoard>::print(std::cout);
//    typedef MoveVehicle<gameBoard, > name;
    return 0;
}