#pragma once
#include"stl_tree.h"
#include"test\test.h"
#include"test_vector.h"
#include"stl_queue.h"
#include<stdio.h>
#include<vector>
#include<iostream>
void test_tree();
using std::vector;
using std::cout;
using std::endl;
using std::cin;
class Loger {
	Loger() = delete;
	Loger(Loger &) = delete;
public:
	static FILE * get_fp()
	{
		static FILE *fp = nullptr;
		if (fp == nullptr)
		{
			fp = fopen("log.txt", "a+");
		}
		return fp;
	}
};
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
struct TreeSolution {
	using tree_type=XX::rb_tree<int, int, KeyOfValue, less >;
	using link_type = XX::rb_tree<int, int, KeyOfValue, less >::link_type;
	vector<vector<link_type>> treeToVector(tree_type tree)
	{
		vector<vector<link_type>> result;
		XX::queue<link_type> q;
		if (tree.empty())
			return vector<vector<link_type>>(1, vector<link_type>(1, nullptr));
		q.push(tree.root());
		q.push(nullptr);
		result.push_back(vector<link_type>());
		while (q.size()>1)
		{
			link_type n = q.front();
			q.pop();
			if (n == nullptr)
			{
				result.push_back(vector<link_type>());
				q.push(nullptr);
			}
			else
			{
				result.back().push_back(n);
				if (tree.left(n) != nullptr)
				{
					q.push(tree.left(n));
				}
				if (tree.right(n) != nullptr)
				{
					q.push(tree.right(n));
				}
			}
		}
		for (auto v : result)
		{
			for (auto l : v)
			{
				fprintf(Loger::get_fp(), "%p: parent(%p) left(%p) right(%p) color(%5s) value(%5d);", l, l->_parent, l->_left, l->_right, l->_color ? "black" : "red", l->_field);
			}
			fprintf(Loger::get_fp(),"\n");
		}
		fprintf(Loger::get_fp(), "\n\n");
		fflush(Loger::get_fp());
		return result;
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
		auto iter1 = tree.begin();
		while (iter1 != tree.end())
		{
			cout << *iter1;
			++iter1;
		}
		auto result = TreeSolution().treeToVector(tree);
		XX::print_container(std::cout,tree);
		auto iter = tree.begin();
		tree.erase(iter);
		result = TreeSolution().treeToVector(tree);
		XX::print_container(std::cout, tree);
		iter = tree.begin();
		tree.erase(iter);
		result = TreeSolution().treeToVector(tree);
		XX::print_container(std::cout, tree);
		iter = tree.begin();
		tree.erase(iter);
		result = TreeSolution().treeToVector(tree);
		XX::print_container(std::cout, tree);
		iter = tree.begin();
		tree.erase(iter);
		result = TreeSolution().treeToVector(tree);
		XX::print_container(std::cout, tree);
		iter = tree.begin();
		tree.erase(iter);
		result = TreeSolution().treeToVector(tree);
		XX::print_container(std::cout, tree);
		iter = tree.begin();
		tree.erase(iter);
		result = TreeSolution().treeToVector(tree);
		XX::print_container(std::cout, tree);
		iter = tree.begin();
		tree.erase(iter);
		result = TreeSolution().treeToVector(tree);
		XX::print_container(std::cout, tree);
		iter = tree.begin();
		tree.erase(iter);
		result = TreeSolution().treeToVector(tree);
		XX::print_container(std::cout, tree);
		iter = tree.begin();
		tree.erase(iter);
		result = TreeSolution().treeToVector(tree);
		XX::print_container(std::cout, tree);
		//iter++;
		//iter++;
		//tree.erase(iter);
		//XX::print_container(std::cout, tree);
		//iter = tree.end();
		//--iter;
		//--iter;
		//tree.erase(iter);
		//XX::print_container(std::cout, tree);
		//iter = tree.begin();
		//tree.erase(iter);
		//XX::print_container(std::cout, tree);
		//iter = tree.end();
		//tree.erase(iter);
		//XX::print_container(std::cout, tree);


	
	}
};