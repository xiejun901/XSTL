#ifndef _STL_FUNCTION_H_
#define _STL_FUNCTION_H_
namespace XX {
    //二元函数基类
    template<typename Arg1, typename Arg2, typename Result>
    struct binary_function{
        using first_argument_type= Arg1;
        using second_argument_type = Arg2;
        using result_type = Result;
    };

    //一元函数基类
    template<typename Arg, typename Result>
    struct unary {
        using argument_type = Arg;
        using result_type = Result;
    };

    //小于函数
    template<typename T>
    struct less: public binary_function<T,T,bool>
    {
        bool operator()(const T &x, const T &y) const
        {
            return x < y;
        }
    };

    //取唯一的，在set中可用此函数从value取出key
    template<typename T>
    struct _Identity: public unary<T, T> {
        const T &operator()(const T &x)
        {
            return x;
        }
    };

}
#endif