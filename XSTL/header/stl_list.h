#ifndef _STL_LIST_H_
#define _STL_LIST_H_
#pragma once
#include"stl_iterator.h"
#include"stl_alloc.h"
#include"stl_construct.h"
#include"type_traits.h"
/*stl链表，双向链表，构成环状结构*/
namespace XX {
	//链表结点结构
	template<typename T>
	struct _list_node{
		struct _list_node<T> *prev=0;
		struct _list_node<T> *next=0;
		T                data=0;
	};

	//链表迭代器
	template<typename T,typename Ref,typename Ptr>
	struct _list_iterator{

		using iterator_category = bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = Ptr;
		using reference = Ref;

		using iterator = _list_iterator<T, T&, T*>;
		using const_iterator = _list_iterator<T, const T&, const T*>;
		using self = _list_iterator<T, Ref, Ptr>;

		using link_type = _list_node<T> *;
		//用来保存迭代器对应的结点指针
		link_type node;
		//构造函数
		_list_iterator(link_type x):node(x){}//由于此构造函数，linke_type 类型可隐式转换成_list_iterator
		_list_iterator(){}
		_list_iterator(const iterator &x):node(x.node){}
		bool operator==(const _list_iterator &x) {
			return node == x.node;
		}
		bool operator!=(const _list_iterator &x) {
			return node != x.node;
		}
		reference operator*() {
			return (*node).data;
		}
		pointer operator->() {
			return &(operator*());
		}

		self  &operator++() {
			node = node->next;
			return *this;
		}
		self operator++(int) {
			self temp = *this;
			node = node->next;
			return temp;
		}
		self& operator--() {
			node = node->prev;
			return *this;
		}
		self operator--(int) {
			self temp = *this;
			node = node->prev;
			return temp;
		}
	};
	//链表数据结构
	template<typename T,typename Alloc=alloc>
	class list {
	public:
		using list_node = _list_node<T>;
		using list_link = list_node *;
		using iterator = _list_iterator<T,T&,T*>;
		using const_iterator = _list_iterator<T, const T&, const T*>;
		using size_type = size_t;
		//using const_iterator = const iterator;
		//构造函数
		list() {
			node=get_node();
			node->next = node;
			node->prev = node;
		};
		list(size_type count,const T&value) {
			node = get_node();
			list_link temp = node;
			while (count--) {
				temp->next = creat_node(value);
				temp->next->prev = temp;
				temp = temp->next;
			}
			temp->next = node;
			node->prev = temp;
		}
		list(const list& other){
			node = get_node();
			list_link temp = node;
			const_iterator first = other.cbegin();
			const_iterator last = other.cend();
			while (first != last){
				temp->next = creat_node(*first);
				temp->next->prev = temp;
				temp = temp->next;
				++first;
			}
			temp->next = node;
			node->prev = temp;
		}
		list(list && other) {
			node = other.node;
			other.node = nullptr;
		}
		list(std::initializer_list<T> ilist) {
			node = get_node();
			list_link temp = node;
			typename std::initializer_list<T>::iterator first = ilist.begin();
			typename std::initializer_list<T>::iterator last = ilist.end();
			while (first != last) {
				temp->next = creat_node(*first);
				temp->next->prev = temp;
				temp = temp->next;
				++first;
			}
			temp->next = node;
			node->prev = temp;
		}
		//operat=
		list& operator=(const list&other) {
			if (this != &other) {
				iterator first1 = begin();
				iterator last1 = end();
				const_iterator first2 = other.cbegin();
				const_iterator last2 = other.cend();
				while (first1 != last1&&first2 != last2) {
					*first1++ = *first2++;
				}
				if (first2 == last2) {
					erase(first1, last1);
				}
				else
				{
					insert(last1, first2, last2);
				}
			}
			return *this;
		}
		list& operator=(list &&other) {
			node = other.node;
			other.node = nullptr;
			return *this;
		}
		list& operator=(std::initializer_list<T> ilist) {
			iterator first1 = begin();
			iterator last1 = end();
			typename std::initializer_list<T>::iterator first2 = ilist.begin();
			typename std::initializer_list<T>::iterator last2 = ilist.end();
			while (first1 != last1&&first2 != last2) {
				*first1++ = *first2++;
			}
			if (first2 == last2) {
				erase(first1, last1);
			}
			else
			{
				insert(last1, first2, last2);
			}
			return *this;
		}
		//assign
		void assign(size_type count, const T&value) {
			iterator first = begin();
			iterator last = end();
			while (first != last&&count--) {
				*first++ = value;
			}
			if (count == 0)
				erase(first, last);
			else
				insert(last, count, value);
		}
		template<typename InputIter>
		void assign(InputIter first, InputIter last) {
			using integral = typename is_integer<InputIter>::_integral;
			_assign(first, last, integral());
		}
		//析构函数
		~list() {
			if (node != nullptr) {
				list_link curr = node->next;
				while (curr != node) {
					list_link next = curr->next;
					destroy_node(curr);
					curr = next;
				}
				destroy(node);
			}
		}
		//前闭后开的区间
		iterator begin() { return node->next; }
		iterator end() { return node; }
		const_iterator begin() const { return node->next; }
		const_iterator end() const { return node; }
		const_iterator cbegin() const { return node->next; }
		const_iterator cend() const { return node; }
		//头尾插入元素
		void push_back(const T &x) {
			insert(node, x);
		}
		void push_front(const T&x) {
			insert(node->next, x);
		}
		//头尾删除元素 
		void pop_back() {
			iterator temp = end();
			erase(--temp);
		}
		void pop_front() {
			erase(begin());
		}
		//清空整个链表的元素，最后剩下的是一个空链表（即只有node一个节点）
		void clear() {
			list_link curr = node->next;
			while (curr != node) {
				list_link next = curr->next;
				destroy_node(curr);
				curr = next;
			}
			node->next = node;
			node->prev = node;
		}
		//capacity相关函数
		bool empty() {
			return begin() == end();//node == node->next;
		}
		size_t size() {
			return distance(begin(), end());
		}
		bool max_size() {
			return size_t(-1) / sizeof(list_node);
		}
		//在指定迭代器之前插入元素，
		iterator insert(iterator pos, const T &x) {
			list_link temp = creat_node(x);
			temp->prev = pos.node->prev;
			pos.node->prev->next = temp;
			temp->next = pos.node;
			pos.node->prev = temp;
			return temp;
		}
		template<typename InputIter>
		void insert(iterator pos, InputIter first, InputIter last) {
			while (first != last) {
				insert(pos, *first++);
			}
		}
		void insert(iterator pos, size_type count, const T&value) {
			while (count--)
				insert(pos, value);
		}
		//移除迭代器所指的元素
		iterator erase(iterator pos) {
			pos.node->prev->next = pos.node->next;
			pos.node->next->prev = pos.node->prev;
			list_link temp = pos.node->next;
			destroy_node(pos.node);
			return temp;
		}
		iterator erase(iterator first, iterator last) {
			while (first != last){
				erase(first++);
			}
			return last;
		}
		//remove指定元素
		void remove(const T&x) {
			iterator first = begin();
			iterator last = end();
			while (first != last) {
				iterator next = first;
				++next;
				if (*first == x)
					erase(first);
				first=next;
			}
		}
		//移除连续的相同元素，使只剩下一个
		void unique() {
			iterator first = begin();
			iterator last = end();
			if (first == last)
				return;
			iterator next = first;
			while (next!=last) {
				++next;
				if (*first == *next) {
					erase(next);
				}
				else {
					first = next;
				}
				next = first;
			}
		}
		//splice拼接链表
		void splice(iterator pos, list &other) {
			if(!other.empty())
				transfer(pos, other.begin(), other.end());
		}
		void splice(iterator pos, list &other, iterator i) {
			iterator j = i;
			++j;
			if (i == pos || j == pos)
				return;
			transfer(pos, i, j);
		}
		//合并，将两个已经排序的链表合成一个链表
		void merge(list &x) {
			iterator first1 = begin();
			iterator last1 = end();
			iterator first2 = x.begin();
			iterator last2 = x.end();
			while (first1 != last1&&first2 != last2) {
				if (*first2 < *first1) {
					iterator next = first2;
					transfer(first1, first2, ++next);
					first2 = next;
				}
				else
					++first1;
			}
			if (first2 != last2) {
				transfer(last1, first2, last2);
			}
		}
	private:
		using list_node_allocator = simple_alloc<list_node, Alloc>;
		list_link node;//因为链表组成一个环状，所以只需要一个节点就能表示链表
		//产生一个节点
		list_link get_node() {
			return list_node_allocator::allocate();
		}
		//释放一个节点
		void put_node(list_link p) {
			list_node_allocator::deallocate(p);
		}
		//配置一个带有元素值得节点
		list_link creat_node(const T &x) {
			list_link p = list_node_allocator::allocate();
			construct(&p->data, x);
			return p;
		}
		//删除node
		void destroy_node(list_link p) {
			destroy(&p->data);
			put_node(p);
		}
	//public:
		//迁移操作
		void transfer(iterator position, iterator first, iterator last) {
			if (position != last) {
				last.node->prev->next = position.node;
				position.node->prev->next = first.node;
				list_link temp = position.node->prev;
				position.node->prev = last.node->prev;
				first.node->prev->next = last.node;
				last.node->prev = first.node->prev;
				first.node->prev = temp;
			}
		}
		template<typename InputIter>
		void _assign(InputIter first, InputIter last, _false_type) {
			iterator first1 = begin();
			iterator last1 = end();
			while (first1 != last1&&first != last) {
				*first1 = *first;
				++first1;
				++first;
			}
			if (first == last)
				erase(first1, last1);
			else
				insert(last1, first, last);
		}
		template<typename InputIter>
		void _assign(InputIter first, InputIter last, _true_type) {
			assign((size_type)first, (T)last);
		}
	};
	
}
#endif
