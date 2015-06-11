#ifndef _STL_DEQUE_H_
#define _STL_DEQUE_H_
#include"stl_iterator.h"
#include"stl_alloc.h"
#include"stl_construct.h"
#include"stl_uninitialized.h"
#include"type_traits.h"
#include<cstddef>
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
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
		self operator-(difference_type n) const{
			self temp = *this;
			return temp -= n;
		}
		reference &operator[](difference_type n) {
			return *(*this + n);
		}

		bool operator== (const self &x) const {
			return cur == x.cur;
		}
		bool operator!=(const self &x) const{
			return !(*this == x);
		}
		bool operator<(const self &x) const{
			//��һ��buffer���ж�cur������һ��buffer���ж�node
			return (node == x.node) ? (cur < x.cur) : (node < x.node);
		}
		difference_type operator-(const self&x) const{
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

		using const_reverse_iterator = reverse_iterator<const_iterator>;
		using reverse_iterator = reverse_iterator<iterator>;
		

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
		//ctor
		deque();
		deque(size_type n, const T &value);
		template<typename InputIter>
		deque(InputIter first, InputIter last);
		deque(const deque& other);
		deque(deque && other);
		~deque();
		//iterators
		iterator begin() { return start; }
		iterator end() { return finish; }
		const_iterator cbegin() const { return start; }
		const_iterator cend() const { return finish; }
		const_iterator begin() const { return start; }
		const_iterator end() const { return finish; }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator crbegin() const { return reverse_iterator(cend()); }
		const_reverse_iterator crend() const { return reverse_iterator(cbegin()); }
		const_reverse_iterator rbegin() const { return reverse_iterator(cend()); }
		const_reverse_iterator rend() const { return reverse_iterator(cbegin()); }

		//Modifiers
		void push_back(const T &value);
		//void push_back(T&&value);
		void pop_back();
		void push_front(const T &value);
		void pop_front();
		size_type size() const { return finish - start; }
		size_type max_size() const { return size_type(-1); }
		bool empty() const { return finish == start; }
	private:
		void fill_initialize(size_t n, const value_type&value);
		void creat_map_and_nodes(size_t element_size);
		void push_back_aux(const T&value);
		void push_front_aux(const T&value);
		pointer allocate_node() {
			return data_allocator::allocate(deque_buf_size(BufSize, sizeof(T)));
		}
		void deallocate_node(T* p) {
			data_allocator::deallocate(p, deque_buf_size(BufSize, sizeof(T)));
		}
		void reserve_map_at_back(size_t nodes_to_add=1);//��֤map�Ĵ�С�������С������ʱ�������·���һƬ�ڴ���Ϊmap
		void reserve_map_at_front(size_t nodes_to_add = 1);
		size_type buffer_size() { return deque_buf_size(BufSize, sizeof(T)); }//��ȡ��ǰ���deque��buff��С���������
		void reallocate_map(size_type node_to_add, bool add_at_front);//���·���map������ԭ������
		template<typename Integer>
		void initial_deque_dispatch(Integer n, Integer value,_true_type);
		template<typename InputIter>
		void initial_deque_dispatch(InputIter first,InputIter last,_false_type);
		template<typename InputIter>
		void deque_range_initial(InputIter first, InputIter last, input_iterator_tag);
		template<typename InputIter>
		void deque_range_initial(InputIter first, InputIter last, forward_iterator_tag);
	};
	template<typename T, typename Alloc = alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::deque(size_type n, const T &value) {
		fill_initialize(n, value);
	}
	template<typename T, typename Alloc = alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::deque(const deque &other) {
		size_type n = other.size();
		creat_map_and_nodes(n);
		uninitialized_copy(other.begin(), other.end(), start);
	}
	template<typename T, typename Alloc = alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::deque() {
		creat_map_and_nodes(0);
	}

	template<typename T, typename Alloc , size_t BufSize>
	template<typename InputIter>
	deque<T, Alloc, BufSize>::deque(InputIter first,InputIter last) {
		using integral = typename is_integer<InputIter>::_integral;
		initial_deque_dispatch(first, last, integral());
	}

	template<typename T, typename Alloc, size_t BufSize>
	template<typename Integer>
	void deque<T, Alloc, BufSize>::initial_deque_dispatch(Integer n, Integer value, _true_type) {
		creat_map_and_nodes(n);
		map_pointer cur;
		for (cur = start.node;cur < finish.node;++cur)
			uninitialized_fill(*cur, *cur + deque_buf_size(BufSize, sizeof(T)), value);
		uninitialized_fill(*cur, finish.cur, value);
		//deque(size_type(n), value_type(value));
	}
	template<typename T, typename Alloc, size_t BufSize>
	template<typename InputIter>
	void deque<T, Alloc, BufSize>::initial_deque_dispatch(InputIter first, InputIter last, _false_type) {
		//��Χ��ʼ��,��������������Ƿ���������ʽ��в�ͬ�Ĳ���
		deque_range_initial(first, last, iterator_category(first));
	}

	template<typename T, typename Alloc , size_t BufSize> template<typename InputIter>
	void deque<T, Alloc, BufSize>::deque_range_initial(InputIter first, InputIter last, input_iterator_tag) {
		creat_map_and_nodes(0);
		for (;first != last;++first)
			push_back(*first);
	}

	template<typename T, typename Alloc, size_t BufSize> template<typename InputIter>
	void deque<T, Alloc, BufSize>::deque_range_initial(InputIter first, InputIter last, forward_iterator_tag) {
		size_t n = 0;
		n=distance(first, last);
		creat_map_and_nodes(n);
		map_pointer cur= start.node;
		InputIter mid = first;
		for (;cur < finish.node;++cur) {
			advance(mid, deque_buf_size(BufSize, sizeof(T)));
			uninitialized_copy(first, mid, *cur);
			first = mid;
		}
		uninitialized_copy(first, last, finish.first);
	}


	template<typename T, typename Alloc = alloc, size_t BufSize>
	deque<T, Alloc, BufSize>::~deque() {
		if (start.node == finish.node) {
			destroy(start.cur, finish.cur);
			deallocate_node(*(start.node));
		}
		else {
			destroy(start.cur, start.last);
			map_pointer temp = start.node;
			while (++temp != finish.node)
				destroy(*temp, *temp + deque_buf_size(BufSize, sizeof(T)));
			destroy(finish.first, finish.cur);
			temp = start.node;
			for (;temp <= finish.node;++temp)
				deallocate_node(*temp);
		}
		map_allocator::deallocate(map, map_size);
	}
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
	void deque<T, Alloc, BufSize>::pop_back() {
		if (finish.cur == finish.first) {
			map_pointer temp = finish.node;
			finish.set_node(finish.node - 1);
			finish.cur = finish.last;
			deallocate_node(*temp);
		}
		--finish;
		destroy(finish.cur);
	}
	template<typename T, typename Alloc = alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::push_front(const T&value) {
		if (start.cur != start.first)
			construct(--start.cur, value);
		else
			push_front_aux(value);
	}
	template<typename T, typename Alloc = alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::pop_front() {
		destroy(start.cur);
		++start;
		if (start.cur == start.first) {
			deallocate_node(*(start.node - 1));
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
	void deque<T, Alloc, BufSize>::push_front_aux(const T&value) {
		reserve_map_at_front();
		*(start.node - 1) = allocate_node();
		start.set_node(start.node - 1);
		start.cur = start.last;
		construct(--start.cur, value);
	}
	template<typename T, typename Alloc = alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::fill_initialize(size_t n, const T&value) {
		creat_map_and_nodes(n);
		map_pointer cur;
		for (cur = start.node;cur < finish.node;++cur)
			uninitialized_fill(*cur, *cur + deque_buf_size(BufSize, sizeof(T)), value);
		uninitialized_fill(*cur, finish.cur, value);
	}

	template<typename T, typename Alloc = alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::creat_map_and_nodes(size_t num_elements) {
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
	template<typename T, typename Alloc = alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::reserve_map_at_front(size_type nodes_to_add = 1) {
		if (start.node==map) {
			reallocate_map(nodes_to_add, true);
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
		start.set_node(new_nstart);
		finish.set_node(new_nstart + old_num_nodes - 1);
	}
	inline size_t deque_buf_size(size_t n, size_t sz) {
		//n�����ڱ�ʾ��������СΪ�����nֵ
		//nΪ0��ʾ��������СΪĬ��ֵ�����sizeof(value_type)����512��Ϊ1��С��512Ϊ5112/sz
		return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));

	}
};
#endif