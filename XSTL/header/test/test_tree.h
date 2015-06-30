#pragma once
#include"stl_tree.h"
#include"test\test.h"
#include<iostream>
void test_tree();
struct KeyOfValue {
	int operator()(int x)
	{
		return x;
	}
};
struct less {
	bool operator()(int x, int y)
	{
		return x < y;
	}
};
class TestTree{
public:
	void test_node() {

	}
	void test_iterator() {
		using link = XX::_rb_tree_node<int>::_link_type;
		link n1,n2,n3,n4,n5,n6,n7,n8;
		n1 = new XX::_rb_tree_node<int>();
		n2 = new XX::_rb_tree_node<int>();
		n3 = new XX::_rb_tree_node<int>();
		n4 = new XX::_rb_tree_node<int>();
		n5 = new XX::_rb_tree_node<int>();
		n6 = new XX::_rb_tree_node<int>();
		n7 = new XX::_rb_tree_node<int>();
		n8 = new XX::_rb_tree_node<int>();
		n1->_field = 5;
		n2->_field = 3;
		n3->_field = 10;
		n4->_field = 1;
		n5->_field = 4;
		n6->_field = 7;
		n7->_field = 12;
		n8->_field = 11;
		n1->_left = n2;
		n1->_right = n3;
		n2->_parent = n1;
		n3->_parent = n1;
		n2->_left = n4;
		n4->_parent = n2;
		n2->_right = n5;
		n5->_parent = n2;
		n3->_left=n6;
		n6->_parent = n3;
		n3->_right = n7;
		n7->_parent = n3;
		n7->_left = n8;
		n8->_parent=n7;
		XX::_rb_tree_iterator<int,int&,int*> iter;
		iter._node = n4;
		iter++;
		iter++;
		iter++;
		iter++;
		iter++;
		iter++;
		iter++;
		iter--;
		iter--;
		iter--;
		iter--;
		iter--;
		iter--;
		iter--;
	}
	void test_insert() {
		XX::rb_tree<int, int, KeyOfValue, less > tree;
		auto temp = std::less<int>()(7, 10);
		tree.insert_equal(10);
		tree.insert_equal(7);
		tree.insert_equal(8);
		tree.insert_equal(15);
		tree.insert_equal(5);
		tree.insert_equal(6);
		tree.insert_equal(11);
		tree.insert_equal(13);
		tree.insert_equal(12);
		XX::print_container(std::cout,tree);
		auto iter = tree.begin();
		iter++;
		iter++;
		tree.erase(iter);
		XX::print_container(std::cout, tree);
		iter = tree.end();
		--iter;
		--iter;
		tree.erase(iter);
		XX::print_container(std::cout, tree);
		iter = tree.begin();
		tree.erase(iter);
		XX::print_container(std::cout, tree);
		iter = tree.end();
		tree.erase(iter);
		XX::print_container(std::cout, tree);


	
	}
};