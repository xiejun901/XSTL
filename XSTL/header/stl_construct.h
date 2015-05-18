#ifndef _STL_CONSTRUCT_H_
#define _STL_CONSTRUCT_H_
/*�ڴ˶�����construt()������destroy()����,��SGI ��׼������������ʱ�Ȱ�������������XX namespace ��*/
#include<new> //Ϊ����ʹ��placement new
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
	//���char *��wchar_t *���ػ��汾
	inline void destroy(char * pc1, char* pc2){}
	inline void destroy(wchar_t *pwc1, wchar_t *pwc2){}

}
#endif