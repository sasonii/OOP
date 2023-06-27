//
// Created by Dell on 27/06/2023.
//

#ifndef HW5_TEMP_H
#define HW5_TEMP_H

#include <ostream>
#include "List.h"

template <int N>
struct Int {
    static constexpr int value = N;  // Integer value represented by Int<N>

    friend std::ostream& operator<<(std::ostream& os, const Int<N>& integer) {
        os << integer.value;
        return os;
    }
};

template<typename>
struct Printer;

template<>
struct Printer<List<>>{
    static void print(std::ostream& output){
        output << std::endl;
    }
};

template<typename Head, typename... Tail>
struct Printer<List<Head, Tail...>>{
static void print(std::ostream& output){
    Printer<Head>::print(output);
    output << " ";
    Printer<List<Tail...>>::print(output);
}
};

//template<typename Head, typename... Tail>
//struct Printer<PrependList<Head, List<Tail...>>>{
//    static void print(std::ostream& output){
//        Printer<Head>::print(output);
//        output << " ";
//        Printer<List<Tail...>>::print(output);
//    }
//};

template <int N>
struct Printer<Int<N>> {
    static void print(std::ostream& output) {
        output << N;
    }
};
#endif //HW5_TEMP_H
