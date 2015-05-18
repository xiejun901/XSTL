#ifndef _STL_LIST_H_
#define _STL_LIST_H_
#pragma once
#include"stl_iterator.h"
#include"stl_alloc.h"
#include"stl_construct.h"
/*stl����˫���������ɻ�״�ṹ*/
namespace XX {
	//������ṹ
	template<typename T>
	struct _list_node{
		struct _list_node<T> *prev=0;
		struct _list_node<T> *next=0;
		T                data=0;
	};

	//���������
	template<typename T>
	struct _list_iterator:public iterator<bidirectional_iterator_tag, T> {
		using link_type = _list_node<T> *;
		//���������������Ӧ�Ľ��ָ��
		link_type node;
		//���캯��
		_list_iterator(link_type x):node(x){}//���ڴ˹��캯����linke_type ���Ϳ���ʽת����_list_iterator
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
	//�������ݽṹ
	template<typename T,typename Alloc=alloc>
	class list {
	public:
		using list_node = _list_node<T>;
		using list_link = list_node *;
		using iterator = _list_iterator<T>;
		//���캯��
		list() {
			node=get_node();
			node->next = node;
			node->prev = node;
		};
		//ǰ�պ󿪵�����
		iterator begin() { return node->next; }
		iterator end() { return node; }
		//ͷβ����Ԫ��
		void push_back(const T &x) {
			insert(node, x);
		}
		void push_front(const T&x) {
			insert(node->next, x);
		}
		//ͷβɾ��Ԫ�� 
		void pop_back() {
			iterator temp = end();
			erase(--temp);
		}
		void pop_front() {
			erase(begin());
		}
		//������������Ԫ�أ����ʣ�µ���һ����������ֻ��nodeһ���ڵ㣩
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
		//capacity��غ���
		bool empty() {
			return begin() == end();//node == node->next;
		}
		size_t size() {
			return distance(begin(), end());
		}
		bool max_size() {
			return size_t(-1) / sizeof(list_node);
		}
		//��ָ��������֮ǰ����Ԫ�أ�
		iterator insert(iterator pos, const T &x) {
			list_link temp = creat_node(x);
			temp->prev = pos.node->prev;
			pos.node->prev->next = temp;
			temp->next = pos.node;
			pos.node->prev = temp;
			return temp;
		}
		//�Ƴ���������ָ��Ԫ��
		iterator erase(iterator pos) {
			pos.node->prev->next = pos.node->next;
			pos.node->next->prev = pos.node->prev;
			list_link temp = pos.node->next;
			destroy_node(pos.node);
			return temp;
		}
	private:
		using list_node_allocator = simple_alloc<list_node, Alloc>;
		list_link node;//��Ϊ�������һ����״������ֻ��Ҫһ���ڵ���ܱ�ʾ����
		//����һ���ڵ�
		list_link get_node() {
			return list_node_allocator::allocate();
		}
		//�ͷ�һ���ڵ�
		void put_node(list_link p) {
			list_node_allocator::deallocate(p);
		}
		//����һ������Ԫ��ֵ�ýڵ�
		list_link creat_node(const T &x) {
			list_link p = list_node_allocator::allocate();
			construct(&p->data, x);
			return p;
		}
		//ɾ��node
		void destroy_node(list_link p) {
			destroy(&p->data);
			put_node(p);
		}
		

		
	};
	
}
#endif
