#include "stl_tree.h"
#include<iostream>
using std::cout;
using std::endl;
struct KeyOfValue {
    int operator()(int x)
    {
        return x;
    }
};
struct less {
    bool operator()(int x, int y)
    {
        return x < y;
    }
};
int main()
{
    while (true)
    {
        XX::rb_tree<int, int, KeyOfValue, less > tree;
        tree.insert_equal(10);
        tree.insert_equal(7);
        tree.insert_equal(8);
        tree.insert_equal(15);
        tree.insert_equal(5);
        tree.insert_equal(6);
        tree.insert_equal(11);
        tree.insert_equal(13);
        tree.insert_equal(12);
        //cout << tree.size() << endl;
        tree.clear();
    }
    return 0;
}