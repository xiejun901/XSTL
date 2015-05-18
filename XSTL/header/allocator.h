#ifndef _XX_ALLOCATOR_H_
#define _XX_ALLOCATOR_H_
/*һ��������Ŀռ�������*/
#include<new>
#include<cstddef>
#include<cstdlib>
#include<iostream>

namespace XX
{
	template<typename T>
	inline T* _allocate(ptrdiff_t size, T*){
		std::set_new_handler(0);
		T *tmp = (T*)(::operator new((size_t)(size*sizeof(T))));
		if (tmp == 0){
			std::cerr << "out of memory" << std::endl;
			exit(1);
		}
		return tmp;
	}
	template<typename T>
	inline void _deallocate(T* buffer){
		::operator delete (buffer);
	}

	template<typename T1, typename T2>
	inline void _construct(T1 *p, T2 &value){
		new(p)T1(value);
	}
	template<typename T>
	inline void _destroy(T *ptr){
		ptr->~T();
	}
	template<class T>
	class allocator{
	public:
		//��Ա����
		using value_type=T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		//��Ա����
		//���캯��
		//allocator() = default;
		//allocator(const allocator&);
		//������copy constructor
		//template<typename U>
		//allocator::allocator(const allocator<U> &);
		//destructor
		//~allocator()=default;
		pointer address(reference X) { return (pointer)&X; }
		const_pointer address(const_reference X) const { return (const_pointer)&X; }

		//���ÿռ�,����ȫ�ֵ�::operator new()������ռ�
		pointer allocate(size_type n, const void *hint = 0)
		{
			return _allocate((difference_type)n, (pointer)0);
		}
		//���ؿռ䣬����::operator delete()
		void deallocate(pointer p, size_type n)
		{
			_deallocate(p);
		}

		size_type max_size() const{ return size_type(UINT_MAX / sizeof(T)); }
		
		//construct ���
		//����placement new�ڷ���õĿռ��Ϲ������ new (p) T(value);
		void construct(pointer p, const_reference x){ _construct(p, x); }
		//���ö���������������ٶ���
		void destroy(pointer p){ _destroy(p); }
	};
}
#endif