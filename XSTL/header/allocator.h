#ifndef _XX_ALLOCATOR_H_
#define _XX_ALLOCATOR_H_
/*一个最基本的空间配置器*/
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
		//成员类型
		using value_type=T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		//成员函数
		//构造函数
		//allocator() = default;
		//allocator(const allocator&);
		//泛化的copy constructor
		//template<typename U>
		//allocator::allocator(const allocator<U> &);
		//destructor
		//~allocator()=default;
		pointer address(reference X) { return (pointer)&X; }
		const_pointer address(const_reference X) const { return (const_pointer)&X; }

		//配置空间,采用全局的::operator new()来分配空间
		pointer allocate(size_type n, const void *hint = 0)
		{
			return _allocate((difference_type)n, (pointer)0);
		}
		//还回空间，采用::operator delete()
		void deallocate(pointer p, size_type n)
		{
			_deallocate(p);
		}

		size_type max_size() const{ return size_type(UINT_MAX / sizeof(T)); }
		
		//construct 相关
		//采用placement new在分配好的空间上构造对象 new (p) T(value);
		void construct(pointer p, const_reference x){ _construct(p, x); }
		//调用对象的析构函数销毁对象
		void destroy(pointer p){ _destroy(p); }
	};
}
#endif