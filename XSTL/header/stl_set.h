#ifndef _STL_SET_H_
#define _STL_SET_H_
#include"stl_tree.h"
namespace XX {
    template<typename value_type>
    struct _Identity
    {
        const value_type &operator()(const value_type &x) const
        {
            return x;
        }
    };
    template<typename T>
    struct less {
        bool operator()(T x, T y)
        {
            return x < y;
        }
    };
    template <typename _Key, typename _Compare=less<_Key>, typename _Alloc=alloc>
    class set {
    public:
        using value_type = _Key;
        using key_type = _Key;
        using key_compare = _Compare;
        using value_compare = _Compare;
    private:
        using _Rep_type = rb_tree<key_type, value_type,_Identity<value_type>, key_compare, _Alloc> ;
        _Rep_type t;
    public:
        using pointer = typename _Rep_type::pointer;
        using iterator = typename _Rep_type::iterator;
        void insert(value_type x)
        {
            t.insert_equal(x);
        }
        iterator begin() {
            return t.begin();
        }
        iterator end() {
            return t.end();
        }
    };
}

#endif
