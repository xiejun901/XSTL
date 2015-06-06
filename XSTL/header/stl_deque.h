#ifndef _STL_DEQUE_H_
#define _STL_DEQUE_H_
#include"stl_iterator.h"
#include"stl_alloc.h"
#include"stl_construct.h"
#include"stl_uninitialized.h"
#include<cstddef>
#ifndef max
#define max(a,b) (a)>(b)?(a):(b)
#endif
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
		T* cur;
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
			++cur;
			if (cur == last) {
				set_node(node + 1);
				cur = first;
			}
			return *this;
		}
		self operator++(int) {
			self temp = *this;
			++*this;
			return temp;
		}
		self &operator--() {
			if (cur == first) {
				set_node(node - 1);
				cur = last;
			}
			--cur;
			return *this;
		}
		self operator--(int) {
			self temp = *this;
			--*this;
			return temp;
		}
		self &operator+=(difference_type n) {
			difference_type offset = cur - first + n;
			if (offset >= 0 && offset < (difference_type)buffer_size()) {
				cur += n;
			}
			else {
				difference_type node_offset = offset > 0 ? (offset / (difference_type)buffer_size())
					: -(difference_type)((-offset - 1) / buffer_size()) - 1;
				set_node(node + node_offset);
				cur = first + (offset - node_offset*difference_type(buffer_size()));
			}
			return *this;
		}
		self operator+(difference_type n) {
			self temp = *this;
			return temp += n;
		}
		self &operator-=(difference_type n) {
			return return *this += -n;
		}
		self operator-(difference_type n) {
			self temp = *this;
			return temp -= n;
		}
		reference &operator[](difference_type n) {
			return *(*this + n);
		}

		bool operator==(const self &x) {
			return cur == x.cur;
		}
		bool operator!=(const self &x) {
			return !(*this == x);
		}
		bool operator<(const self &x) {
			//��һ��buffer���ж�cur������һ��buffer���ж�node
			return (node == x.node) ? (cur < x.cur) : (node < x.node);
		}
		difference_type operator-(const self&x) {
			return difference_type(buffer_size())*(node - x.node - 1) + (cur - first) + (x.last - x.cur);
		}
	};

	template<typename T,typename Alloc=alloc,size_t BufSize=0>
	class deque {
	public:
		using value_type = T;
		using pointer = value_type*;
		using size_type = size_t;

		using iterator = deque_iterator<T, T&, T*, BufSize>;
		using const_iterator = deque_iterator<T, const T&, const T*, BufSize>;

		using data_allocator = simple_alloc<value_type, Alloc>;
		using map_allocator = simple_alloc<pointer, Alloc>;
	private:
		using map_pointer = pointer*;
		iterator start;
		iterator finish;
		map_pointer map;//����map��ַ
		size_type map_size;//����map��С
		enum { initial_map_size = 8 };
	public:
		deque(size_type n, const T &value);
		iterator begin() { return start; }
		iterator end() { return finish; }
		const_iterator cbegin() const { return start; }
		const_iterator cend() const { return finish; }
		void push_back(const T &value);
		void push_back(T&&value);
	private:
		void fill_initialize(size_t n, const value_type&value);
		void cread_map_and_nodes(size_t element_size);
		void push_back_aux(const T&value);
		pointer allocate_node() {
			return data_allocator::allocate(deque_buf_size(BufSize, sizeof(T)));
		}
		void reserve_map_at_back(size_t nodes_to_add=1);//��֤map�Ĵ�С�������С������ʱ�������·���һƬ�ڴ���Ϊmap
		size_type buffer_size() { return deque_buf_size(BufSize, sizeof(T)); }//��ȡ��ǰ���deque��buff��С���������
		void reallocate_map(size_type node_to_add, bool add_at_front);//���·���map������ԭ������
	};

	template<typename T, typename Alloc = alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::push_back(const T&value) {
		if (finish.cur != finish.last - 1) {
			construct(finish.cur, value);
			++finish.cur;
		}
		else {
			push_back_aux(value);
		}
	}
	template<typename T, typename Alloc = alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::push_back_aux(const T&value) {
		reserve_map_at_back();
		*(finish.node + 1) = allocate_node();
		construct(finish.cur, value);
		finish.set_node(finish.node + 1);
		finish.cur = finish.first;
	}

	template<typename T, typename Alloc = alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::deque(size_type n, const T &value) {
		fill_initialize(n, value);
	}
	template<typename T, typename Alloc = alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::fill_initialize(size_t n, const T&value) {
		cread_map_and_nodes(n);
		map_pointer cur;
		for (cur = start.node;cur < finish.node;++cur)
			uninitialized_fill(*cur, *cur + deque_buf_size(BufSize, sizeof(T)), value);
		uninitialized_fill(*cur, finish.cur, value);
	}

	template<typename T, typename Alloc = alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::cread_map_and_nodes(size_t num_elements) {
		//��������Ҫ��node��
		size_t num_nodes = num_elements / deque_buf_size(BufSize,sizeof(T)) + 1;
		map_size = max((size_t)initial_map_size,num_nodes + 2);
		map = map_allocator::allocate(map_size);
		map_pointer nstart=map + (map_size - num_nodes) / 2;
		map_pointer nfinish = nstart + num_nodes;
		map_pointer cur;
		for (cur = nstart;cur != nfinish;++cur) {
			*cur = allocate_node();
		}

		start.set_node(nstart);
		start.cur = start.first;
		finish.set_node(nfinish-1);
		finish.cur = finish.first + num_elements%deque_buf_size(BufSize, sizeof(T));
	}
	template<typename T, typename Alloc = alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::reserve_map_at_back(size_type nodes_to_add=1) {
		if (nodes_to_add + 1 > map_size - (finish.node - map)) {
			reallocate_map(nodes_to_add,false);
		}
	}
	//���·���map�ռ�
	template<typename T, typename Alloc = alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::reallocate_map(size_type nodes_to_add, bool add_at_front) {
		//������������������ʣ��Ŀռ����2����Ҫ�Ŀռ䣬���ռ����ܲ�ƽ�⣬ĳһ�������ˣ�����һ�߻�û�ã���ʱֻ��Ҫ���ռ����·��伴��
		size_type old_num_nodes = finish.node - start.node + 1;//�Ѿ�ʹ�õ�node��
		size_type new_num_nodes = old_num_nodes + nodes_to_add;
		map_pointer new_nstart;
		if (map_size > 2 * new_num_nodes) {
			new_nstart = map + (map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
			if (new_nstart > start.node)
				copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
			else
				copy(start.node, finish.node + 1, new_nstart);
		}
		else {
			//�·����С��ԭ���������������ڴ�С����������ӵ�node���ڵ�ǰ��С�������������ӵ�node��ô��Ŀռ�
			size_type new_map_size = map_size + max(map_size, nodes_to_add)+2;
			map_pointer new_map = map_allocator::allocate(new_map_size);
			 new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
			copy(start.node, finish.node + 1, new_nstart);
			map_allocator::deallocate(map, map_size);
			map = new_map;
			map_size = new_map_size;
		}
	}
	inline size_t deque_buf_size(size_t n, size_t sz) {
		//n�����ڱ�ʾ��������СΪ�����nֵ
		//nΪ0��ʾ��������СΪĬ��ֵ�����sizeof(value_type)����512��Ϊ1��С��512Ϊ5112/sz
		return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));

	}
};
#endif