#pragma once
#include"stl_tree.h"
void test_tree();
class TestTree:public XX::rb_tree<int, int, int, int> {
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
	void test_rotation() {
		
	
	}
};