//
// Created by Dell on 27/06/2023.
//

#ifndef HW5_LIST_H
#define HW5_LIST_H

template <typename... Ts>
struct List {
    static constexpr int size = sizeof...(Ts);
};

template <typename T, typename... Ts>
struct List<T, Ts...> {
    typedef T head;
    typedef List<Ts...> next;
    static constexpr int size = sizeof...(Ts) + 1;
};

template <typename T, typename List>
struct PrependList;

template <typename T, typename... Ts>
struct PrependList<T, List<Ts...>> {
    typedef List<T, Ts...> list;
    static constexpr int size = sizeof...(Ts) + 1;
};

template <int N, typename List>
struct GetAtIndex;

template <int N, typename T, typename... Ts>
struct GetAtIndex<N, List<T, Ts...>> {
    using value = typename GetAtIndex<N - 1, List<Ts...>>::value;
};

template <typename T, typename... Ts>
struct GetAtIndex<0, List<T, Ts...>> {
    using value = T;
};

template <int N, typename T, typename List>
struct SetAtIndex;

template <int N, typename NEW, typename T, typename... Ts>
struct SetAtIndex<N,NEW, List<T, Ts...>> {
    using list =  typename PrependList<T,typename SetAtIndex<N - 1,NEW, List<Ts...>>::list>::list;
};

template <typename NEW, typename T, typename... Ts>
struct SetAtIndex<0, NEW, List<T, Ts...>> {
    using list = typename PrependList<NEW, List<Ts...>>::list;
};
#endif //HW5_LIST_H
