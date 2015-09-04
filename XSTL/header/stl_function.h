#ifndef _STL_FUNCTION_H_
#define _STL_FUNCTION_H_
namespace XX {
    //��Ԫ��������
    template<typename Arg1, typename Arg2, typename Result>
    struct binary_function{
        using first_argument_type= Arg1;
        using second_argument_type = Arg2;
        using result_type = Result;
    };

    //һԪ��������
    template<typename Arg, typename Result>
    struct unary {
        using argument_type = Arg;
        using result_type = Result;
    };

    //С�ں���
    template<typename T>
    struct less: public binary_function<T,T,bool>
    {
        bool operator()(const T &x, const T &y) const
        {
            return x < y;
        }
    };

    //ȡΨһ�ģ���set�п��ô˺�����valueȡ��key
    template<typename T>
    struct _Identity: public unary<T, T> {
        const T &operator()(const T &x)
        {
            return x;
        }
    };

}
#endif