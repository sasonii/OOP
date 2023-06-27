//
// Created by Dell on 27/06/2023.
//
#include <iostream>
#include "temp.h"
#include "List.h" // Include the List header file
#include "Utilities.h"

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

int main() {
    //list_printing();

    utilities_printing();

    return 0;
}