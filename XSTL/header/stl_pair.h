#ifndef _STL_PAIR_H_
#define _STL_PAIR_H_
namespace XX {
    template <typename T1, typename T2>
    struct pair {
        using first_type = T1;
        using second_type = T2;
        T1 first;
        T2 second;
        pair() :first(T1()), second(T2()) {}
        pair(const T1 &a, const T2 &b) :first(a), second(b) {}
    };

}
#endif