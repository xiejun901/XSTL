#include"test_deque.h"
#include"stl_deque.h"
#include"test.h"
#include<iostream>
#include<assert.h>
using std::cin;
using std::cout;
using std::endl;
void test_deque() {
	Test_Deque tdq;
	tdq.test_push_pop();
	tdq.test_ctor();
	tdq.test_capacity();
	tdq.test_iterator();
}