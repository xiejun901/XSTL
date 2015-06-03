#ifndef _STL_DEQUE_H_
#define _STL_DEQUE_H_
#include"stl_iterator.h"
#include<cstddef>
namespace XX {
	//deque ������
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
		//��ǰָ���Ԫ��
		T* curr;
		//ָ��ǰ��������ͷ
		T* first;
		//ָ��ǰ��������β
		T* last;
		//ָ��ܿ�����
		map_pointer node;

		//��һ������������Ϊ������ǰ�����������Ҫ�������
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
	//n�����ڱ�ʾ��������СΪ�����nֵ
	//nΪ0��ʾ��������СΪĬ��ֵ�����sizeof(value_type)����512��Ϊ1��С��512Ϊ5112/sz
	return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}
#endif