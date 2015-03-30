#pragma once
#ifndef _VECTOR_H_
#define _VECTOR_H_
#include<memory>
#include<iostream>
#include<cstddef>
namespace XSTL{
	template<typename T>
	class Vector
	{
	public:
		typedef size_t		  size_type;
		typedef T             value_type;
		typedef T*            iterator;
		typedef const T*	  const_iterator;
		typedef T&			  reference;
		typedef const T&	  const_reference;

		Vector() :first(0), last(0), endOfStorage(0)
		{
		}
		explicit Vector(const size_type n)
		{
			first = alloc.allocate(n);
			last = first;
			endOfStorage = first + n;
		}
		Vector(const size_type n, const value_type &value)
		{
			first = alloc.allocate(n);
			last = first;
			for (size_type i = 0; i < n;i++)
				alloc.construct(last++,value);
			endOfStorage = first + n;
		}
		~Vector()
		{
			while (last != first)
				alloc.destroy(--last);
			alloc.deallocate(first, this->max_size());
		}
		void push_back(const value_type &value)
		{
			if (last >= endOfStorage)
			{
					size_type maxSize = this->max_size();
					iterator newfirst = alloc.allocate(2 * maxSize + 1);
					iterator newlast = std::uninitialized_copy(first, last, newfirst);
					while (last != first)
						alloc.destroy(--last);
					alloc.deallocate(first, maxSize);
					first = newfirst;
					last = newlast;
					endOfStorage = first + 2*maxSize+1;

			}
			alloc.construct(last++, value);
		}
		void pop_back()
		{
			alloc.destroy(--last);
		}
		iterator begin()
		{
			return first;
		}
		iterator end()
		{
			return last;
		}
		size_type size()
		{
			return last - first;
		}
		size_type max_size()
		{
			return endOfStorage - first;
		}
		size_type capacity()
		{
			return endofStorage - last;
		}
		bool empty()
		{
			return(first == last);
		}
		//element access
		reference operator[] (size_type n)
		{
			return *(first + n);
		}
		reference at(size_type n)
		{
			return *(first + n);
		}
		reference front()
		{
			return *first;
		}
		reference back()
		{
			return *(last - 1);
		}
		/*const_iterator begin(){ return start; }
		const_iterator end_(){ return end; }*/

	private:
		iterator first;//起始地址，指向第一个元素的地址
		iterator last;//结束地址,指向最后一个元素的下一个地址
		iterator endOfStorage;//分配的存储空间结束地址，指向分配给容器的空间之后的第一个地址
		std::allocator<value_type> alloc;
	};
}
#endif