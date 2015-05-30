#include"stl_list.h"
#include"test_list.h"
#include<vector>
#include<iostream>
using XX::_list_node;
using XX::_list_iterator;
using std::vector;
using std::cout;
using std::endl;
bool test_list_iterator() {
	bool ret = true;
	_list_node<int> *head = new _list_node<int>;
	head->data = 0;
	vector<int> vec{ 1,2,3,4,5,6,7,8,9 };
	_list_node<int> *node = head;
	for (auto i : vec) {
		node->next = new _list_node<int>;
		node->next->prev = node;
		node = node->next;
		node->data = i;
	}
	_list_iterator<int,int&,int*> iter1(head->next);
	_list_iterator<int, int&, int*> end(nullptr);
	int i = 0;
	while (iter1 != end) {
		if (*iter1 != vec[i++]) {
			cout << "test no pass" << endl;
			return false;
		}
		cout << *iter1 << ',';
		++iter1;
	}
	iter1 = head->next;
	advance(iter1, 8);
	if (*iter1 != 9)
		ret = false;
	if(*(iter1--)!=9)
		ret=false;
	if (*(iter1--) != 8)
		ret = false;
	if (*(--iter1) != 6)
		ret = false;
	if (*(--iter1) != 5)
		ret = false;
	if (*(iter1++) != 5)
		ret = false;
	advance(iter1, -3);
	if (*iter1 != 3)
		ret = false;
	if (ret)
		cout << "test pass" << endl;
	else
		cout << "test no pass" << endl;
	return ret;

}
bool test_list() {
	cout << "测试链表相关功能：" << endl;
	bool ret = true;
	XX::list<int> list1;
	XX::list<int>::iterator iter1,iter2;
	iter1 = list1.begin();
	iter2 = list1.end();
	if (iter1 != iter2)
		ret = false;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	iter1 = list1.begin();
	iter2 = list1.end();
	for (int i = 1;i <= 3;i++)
	{
		if (*iter1 != i)
			ret = false;
		++iter1;
	}
	if (iter1 != iter2)
		ret = false;
	//测试push_back;push_front;当前list={1,2,3}
	for (int i = 1;i <= 5;i++) {
		list1.push_back(i);
		list1.push_front(i);
	}
	iter1 = list1.begin();
	iter2 = list1.end();
	vector<int> vec = { 5,4,3,2,1,1,2,3,1,2,3,4,5 };
	for (auto i : vec) {
		if (*iter1 != i)
			ret = false;
		iter1++;
	}
	if (iter1 != iter2)
		ret = false;

	//测试erase
	iter1 = list1.begin();
	iter2 = list1.end();
	advance(iter1, 5);
	vec = { 5,4,3,2,1,2,3,1,2,3,4,5 };
	list1.erase(iter1);
	iter1 = list1.begin();
	for (auto i : vec) {
		if (*iter1 != i)
			ret = false;
		iter1++;
	}
	if (iter1 != iter2)
		ret = false;
	//测试pop_back;pop_front
	for (int i = 1;i <= 5;++i) {
		list1.pop_back();
		list1.pop_front();
	}
	vec = { 2,3};
	iter1 = list1.begin();
	for (auto i : vec) {
		if (*iter1 != i)
			ret = false;
		iter1++;
	}
	if (iter1 != iter2)
		ret = false;
	//测试clear()
	list1.clear();
	iter1 = list1.begin();
	if (iter1 != iter2)
		ret = false;
	//测试容量相关size().empty(),max_size()
	if (!list1.empty())
		ret = false;
	for (int i = 1;i <= 5;i++) {
		list1.push_back(i);
		list1.push_front(i);
	}
	if(list1.size()!=10)
		ret = false;
	if (ret)
		cout << "test pass" << endl;
	else
		cout << "test no pass" << endl;
	return ret;
}

bool test_list_protype() {
	Test_List<int> tlist(cout);
	tlist.print_list( tlist.creat_list_from_vector(XX::vector<int>{1, 2, 3, 4, 5, 6}));
	cout << endl;
	tlist.test_transfer();
	tlist.test_remove();
	tlist.test_unique();
	tlist.test_splice();
	tlist.test_merge();
	tlist.test_ctor();
	tlist.test_operator();
	tlist.test_assign();
	tlist.test_front();
	tlist.test_insert();
	return true;
}

