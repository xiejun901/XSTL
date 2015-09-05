#ifndef _STL_MAP_H_
#define _STL_MAP_H_
#include"stl_tree.h"
#include"stl_function.h"
namespace XX {
    template<typename Key, typename T, typename Compare = less<key>, typename Alloc = alloc>
    class map {
        using key_type = Key;
        using data_type = T;
        using value_type = pair<const Key, T>;
    };
}
#endif