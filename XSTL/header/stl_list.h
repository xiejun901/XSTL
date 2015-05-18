#ifndef _STL_LIST_H_
#define _STL_LIST_H_
#pragma once
#include"stl_iterator.h"
#include"stl_alloc.h"
#include"stl_construct.h"
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
	template<typename T>
	struct _list_iterator:public iterator<bidirectional_iterator_tag, T> {
		using link_type = _list_node<T> *;
		//用来保存迭代器对应的结点指针
		link_type node;
		//构造函数
		_list_iterator(link_type x):node(x){}//由于此构造函数，linke_type 类型可隐式转换成_list_iterator
		_list_iterator(){}
		_list_iterator(const _list_iterator &x):node(x.node){}
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

		_list_iterator  &operator++() {
			node = node->next;
			return *this;
		}
		_list_iterator operator++(int) {
			_list_iterator temp = *this;
			node = node->next;
			return temp;
		}
		_list_iterator& operator--() {
			node = node->prev;
			return *this;
		}
		_list_iterator operator--(int) {
			_list_iterator temp = *this;
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
		using iterator = _list_iterator<T>;
		//构造函数
		list() {
			node=get_node();
			node->next = node;
			node->prev = node;
		};
		//前闭后开的区间
		iterator begin() { return node->next; }
		iterator end() { return node; }
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
		//移除迭代器所指的元素
		iterator erase(iterator pos) {
			pos.node->prev->next = pos.node->next;
			pos.node->next->prev = pos.node->prev;
			list_link temp = pos.node->next;
			destroy_node(pos.node);
			return temp;
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
		

		
	};
	
}
#endif
