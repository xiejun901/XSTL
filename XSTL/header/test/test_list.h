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
//	using const_iterator = typename XX::list<T>::const_iterator;
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
	bool compare_with_vector(list_type &list, const vector_type vec) {
		iterator iter = list.begin();
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
		list_type list1 = creat_list_from_vector(vector_type{ 1,2,3,4,5,6,7,8,9 });
		list_type list2 = creat_list_from_vector(vector_type{ 13,14,15,16,17,18,19,20 });
		iterator position = list1.begin(), first = list2.begin(), last = first;
		XX::advance(position,4);//position指向5;
		XX::advance(first, 2);//first指向15;
		XX::advance(last, 6);//last指向19;
		os << "list1: ";
		print_list(list1);
		os << std::endl;
		os << "list2: ";
		print_list(list2);
		os << std::endl;
		os << "将list2的[15,19)区间转移到list1的位置5"<<std::endl;
		list1.transfer(position, first, last);
		os << "list1: ";
		print_list(list1);
		os << std::endl;
		os << "list2: ";
		print_list(list2);
		os << std::endl;
		if (compare_with_vector(list1, vector_type{ 1,2,3,4,15,16,17,18,5,6,7,8,9 }) && compare_with_vector(list2, vector_type{ 13,14,19,20 }))
			os << "XX::list::transfer() test succeed." << std::endl;
		else
			os << "XX::list::transfer() test failed." << std::endl;
	}
};
#endif
