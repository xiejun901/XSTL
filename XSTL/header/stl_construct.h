#ifndef _STL_CONSTRUCT_H_
#define _STL_CONSTRUCT_H_
/*在此定义了construt()函数和destroy()函数,与SGI 标准库有所区别，暂时先把两个函数放在XX namespace 中*/
#include<new> //为了能使用placement new
namespace XX
{
	template<class T1, class T2>
	inline void construct(T1 *p, T2 &value){
		new (p)T2(value);
	}
	template<class T1, class T2>
	inline void construct(T1 *p, T2 &&value){
		new (p)T2(value);
	}
	template<class T>
	inline void destroy(T *p){
		p->~T();
	}

	template<typename ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last)
	{
		while (first!=last)
		{
			destroy(first);
			++first;
		}
	}
	//针对char *和wchar_t *的特化版本
	inline void destroy(char * pc1, char* pc2){}
	inline void destroy(wchar_t *pwc1, wchar_t *pwc2){}

}
#endif