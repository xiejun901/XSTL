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
		T* cur;
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
			//在一个buffer内判断cur，不在一个buffer内判断node
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
		map_pointer map;//保存map地址
		size_type map_size;//保存map大小
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
		void reserve_map_at_back(size_t nodes_to_add=1);//保证map的大小，如果大小不够的时候负责重新分配一片内存作为map
		void reserve_map_at_front(size_t nodes_to_add = 1);
		size_type buffer_size() { return deque_buf_size(BufSize, sizeof(T)); }//获取当前这个deque的buff大小，方便调用
		void reallocate_map(size_type node_to_add, bool add_at_front);//重新分配map并复制原有数据
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
		//范围初始化,根据输入迭代器是否能随机访问进行不同的策略
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
		//计算所需要的node数
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
	//重新分配map空间
	template<typename T, typename Alloc = alloc, size_t BufSize>
	void deque<T, Alloc, BufSize>::reallocate_map(size_type nodes_to_add, bool add_at_front) {
		//分两种情况，如果现在剩余的空间大于2倍需要的空间，即空间分配很不平衡，某一边用完了，另外一边还没用，此时只需要将空间重新分配即可
		size_type old_num_nodes = finish.node - start.node + 1;//已经使用的node数
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
			//新分配大小的原则是至少两倍现在大小，如果新增加的node大于当前大小，则增加新增加的node那么大的空间
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
		//n不等于表示缓冲器大小为定义的n值
		//n为0表示缓冲器大小为默认值，如果sizeof(value_type)大于512，为1，小于512为5112/sz
		return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));

	}
};
#endif