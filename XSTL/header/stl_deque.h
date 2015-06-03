#ifndef _STL_DEQUE_H_
#define _STL_DEQUE_H_
#include"stl_iterator.h"
#include<cstddef>
namespace XX {
	//deque 迭代器
	template<typename T, typename Ref, typename Ptr, size_t BufSize>
	struct deque_iterator {
		using iterator = deque_iterator<T, T&, T*, BufSize>;
		using const_iterator = deque_iterator<T, const T&, const T*, BufSize>;

		static size_t buffer_size() { return deque_buf_size(BufSize, sizeof(T)); }

		using iterator_category = random_acess_iterator_tag;
		using value_type = T;
		using pointer = Ptr;
		using reference = Ref;
		using difference_type = ptrdiff_t;
		using size_type = size_t;

		using map_pointer = T**;
		using self = deque_iterator;
		//当前指向的元素
		T* curr;
		//指向当前缓冲器的头
		T* first;
		//指向当前缓冲器的尾
		T* last;
		//指向管控中心
		map_pointer node;

		//跳一个缓冲区，因为可能向前或者向后，所以要传入参数
		void set_node(map_pointer new_node) {
			node = new_node;
			first = *new_node;
			last = first + difference_type(buffer_size());
		}
		//deference
		reference operator*() const { return *cur; }
		pointer operator->() const { return &(operator*()); }

		self &operator++() {
			++curr;
			if (curr == last) {
				set_node(node + 1);
				curr = first;
			}
			return *this;
		}
		self operator++(int) {
			self temp = *this;
			++*this;
			return temp;
		}
		self &operator--() {
			if (curr == first) {
				set_node(node - 1);
				curr =last;
			}
			--curr;
			return *this;
		}
		self operator--(int) {
			self temp = *this;
			--*this;
			return temp;
		}
	};
}

inline size_t deque_buf_size(size_t n, size_t sz){
	//n不等于表示缓冲器大小为定义的n值
	//n为0表示缓冲器大小为默认值，如果sizeof(value_type)大于512，为1，小于512为5112/sz
	return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}
#endif