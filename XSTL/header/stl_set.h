#ifndef _STL_SET_H_
#define _STL_SET_H_
#include"stl_tree.h"
#include"stl_function.h"
namespace XX {
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
        using size_type = typename _Rep_type::size_type;
        void insert(value_type x);
        iterator begin();
        iterator end();
        bool empty();
        size_type size();      
    };
    template<typename _Key, typename _Compare, typename _Alloc>
    inline void set<_Key, _Compare, _Alloc>::insert(value_type x)
    {
        t.insert_equal(x);
    }
    template<typename _Key, typename _Compare, typename _Alloc>
    inline typename set<_Key, _Compare, _Alloc>::iterator set<_Key, _Compare, _Alloc>::begin() {
        return t.begin();
    }
    template<typename _Key, typename _Compare, typename _Alloc>
    inline typename set<_Key, _Compare, _Alloc>::iterator set<_Key, _Compare, _Alloc>::end() {
        return t.end();
    }
    template<typename _Key, typename _Compare, typename _Alloc>
    inline bool set<_Key, _Compare, _Alloc>::empty()
    {
        return t.empty();
    }
    template<typename _Key, typename _Compare, typename _Alloc>
    inline typename set<_Key, _Compare, _Alloc>::size_type set<_Key, _Compare, _Alloc>::size()
    {
        return t.size();
    }
}

#endif
