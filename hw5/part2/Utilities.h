//
// Created by Dell on 27/06/2023.
//

#ifndef HW5_UTILITIES_H
#define HW5_UTILITIES_H

template <bool, typename X, typename Y>
struct Conditional;

template <typename X, typename Y>
struct Conditional<true,X,Y> {
    using value = X;
};

template <typename X, typename Y>
struct Conditional<false,X,Y> {
    using value = Y;
};

template <bool, int, int>
struct ConditionalInteger;

template <int X, int Y>
struct ConditionalInteger<true,X,Y> {
    static constexpr int value = X;
};

template <int X, int Y>
struct ConditionalInteger<false,X,Y> {
    static constexpr int value = Y;
};

#endif //HW5_UTILITIES_H
