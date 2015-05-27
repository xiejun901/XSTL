#ifndef _TEST_LIST_H_
#define _TEST_LIST_H_
#pragma once
#include "stl_vector.h"
#include"stl_list.h"
#include<iostream>
bool test_list_iterator();
bool test_list();
bool test_list_protype();

//用个类来做测试吧
template<typename T>
class Test_List {
private:
	using list_type = typename XX::list<T>;
	using vector_type = typename XX::vector<T>;
	using iterator = typename XX::list<T>::iterator;
	using const_iterator = typename XX::list<T>::const_iterator;
	std::ostream &os;
public:
	list_type creat_list_from_vector(const vector_type &vec) {
		list_type list;
		for (auto v : vec) {
			list.push_back(v);
		}
		return list;
	}
	void print_list(list_type &list) {
		iterator iter_begin = list.begin();
		iterator iter_end = list.end();
		while (iter_begin != iter_end) {
			os << *iter_begin << ' ';
				++iter_begin;
		}
	}
	bool compare_with_vector(const list_type &list, const vector_type vec) {
		const_iterator iter = list.begin();
		for (auto v : vec) {
			if (*iter != v)
				return false;
			++iter;
		}
		return true;
	}
public:
	Test_List(std::ostream &o):os(o){}
	void test_transfer() {
		//os << "测试void transfer(position,first,last):"<<std::endl;
		//list_type list1 = creat_list_from_vector(vector_type{ 1,2,3,4,5,6,7,8,9 });
		//list_type list2 = creat_list_from_vector(vector_type{ 13,14,15,16,17,18,19,20 });
		//iterator position = list1.begin(), first = list2.begin(), last = first;
		//XX::advance(position,4);//position指向5;
		//XX::advance(first, 2);//first指向15;
		//XX::advance(last, 6);//last指向19;
		//os << "list1: ";
		//print_list(list1);
		//os << std::endl;
		//os << "list2: ";
		//print_list(list2);
		//os << std::endl;
		//os << "将list2的[15,19)区间转移到list1的位置5"<<std::endl;
		//list1.transfer(position, first, last);
		//os << "list1: ";
		//print_list(list1);
		//os << std::endl;
		//os << "list2: ";
		//print_list(list2);
		//os << std::endl;
		//if (compare_with_vector(list1, vector_type{ 1,2,3,4,15,16,17,18,5,6,7,8,9 }) && compare_with_vector(list2, vector_type{ 13,14,19,20 }))
		//	os << "XX::list::transfer() test succeed." << std::endl;
		//else
		//	os << "XX::list::transfer() test failed." << std::endl;
	}
	void test_remove() { 
		os << "测试void remove(const T &x):" << std::endl;
		list_type list = creat_list_from_vector(vector_type{ 1,2,3,7,9,6,3,4,5,6,7,8,9,3,5,3 });
		os << "list: ";
		print_list(list);
		os << std::endl;
		os << "将值为3的元素移除掉" << std::endl;
		list.remove(3);
		os << "list: ";
		print_list(list);
		os << std::endl;
		if (compare_with_vector(list, vector_type{ 1,2,7,9,6,4,5,6,7,8,9,5 }))
			os << "XX::list::remove() test succeed." << std::endl;
		else
			os << "XX::list::remove() test failed." << std::endl;
	}
	void test_unique() {
		os << "测试void unique():" << std::endl;
		list_type list = creat_list_from_vector(vector_type{ 1,2,3,3,3,3,4,5,5,6,6,6,7,8,9 });
		os << "list: ";
		print_list(list);
		os << std::endl;
		os << "将重复的元素移除掉" << std::endl;
		list.unique();
		os << "list: ";
		print_list(list);
		os << std::endl;
		if (compare_with_vector(list, vector_type{ 1,2,3,4,5,6,7,8,9 }))
			os << "XX::list::unique() test succeed." << std::endl;
		else
			os << "XX::list::unique() test failed." << std::endl;
	}
	void test_splice() {
		os << "测试splice():" << std::endl;
		list_type list = creat_list_from_vector(vector_type{ 1,2,3,3,3,3,4,5,5,6,6,6,7,8,9 });
		list_type list2 = creat_list_from_vector(vector_type{ 9,8,9,6,3,2,1,5,8,6 });
		os << "list: ";
		print_list(list);
		os << std::endl;
		os << "list2: ";
		print_list(list2);
		os << std::endl;
		os << "将list2的第五个元素拼接到list第6个位置" << std::endl;
		iterator iter = list.begin();
		XX::advance(iter, 6);
		iterator iter2 = list2.begin();
		XX::advance(iter2, 5);
		list.splice(iter, list2, iter2);
		os << "list: ";
		print_list(list);
		os << std::endl;
		os << "list2: ";
		print_list(list2);
		os << std::endl;
		os << "将list2拼接到list第6个位置" << std::endl;
		iter = list.begin();
		XX::advance(iter, 6);
		list.splice(iter, list2);
		os << "list: ";
		print_list(list);
		os << std::endl;
		os << "list2: ";
		print_list(list2);
		os << std::endl;
		if (compare_with_vector(list, vector_type{ 1,2,3,3,3,3, 9,8,9,6,3,1,5,8,6,2,4,5,5,6,6,6,7,8,9 }))
			os << "XX::list::unique() test succeed." << std::endl;
		else
			os << "XX::list::unique() test failed." << std::endl;
	}
	void test_merge() {
		os << "测试merge():" << std::endl;
		list_type list = creat_list_from_vector(vector_type{ 1,4,6,7,9,13,14,16 });
		list_type list2 = creat_list_from_vector(vector_type{ 1,2,5,6,8,14,18,19 });
		os << "list: ";
		print_list(list);
		os << std::endl;
		os << "list2: ";
		print_list(list2);
		os << std::endl;
		os << "将list2合并到list中" << std::endl;
		list.merge(list2);
		os << "list: ";
		print_list(list);
		os << std::endl;
		os << "list2: ";
		print_list(list2);
		os << std::endl;
		if (compare_with_vector(list, vector_type{ 1,1,2,4,5,6,6,7,8,9,13,14,14,16,18,19 }))
			os << "XX::list::unique() test succeed." << std::endl;
		else
			os << "XX::list::unique() test failed." << std::endl;
	}
};
#endif
