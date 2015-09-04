#include<iostream>
#include"stl_set.h"
using namespace XX;
using std::cin;
using std::cout;
using std::endl;
//template<typename value_type>
//struct _Identity
//{
//    value_type &operator()(const value_type &x) const
//    {
//        return x;
//    }
//};
//template<typename T>
//struct less {
//    bool operator()(T x, T y)
//    {
//        return x < y;
//    }
//};
int main()
{
    set<int> s;
    s.insert(15);
    s.insert(13);
    s.insert(56);
    s.insert(77);
    s.insert(2);
    s.insert(99);
    for (auto iter = s.begin(); iter != s.end(); ++iter)
    {
        cout << *iter << endl;
    }
    cout << s.size() << endl;
    while (true)
    {
        set<int> s;
        s.insert(15);
        s.insert(13);
        s.insert(56);
        s.insert(77);
        s.insert(2);
        s.insert(99);
    }
    return 0;
}