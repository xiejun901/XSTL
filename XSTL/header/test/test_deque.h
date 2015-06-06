#ifndef _TEST_DEQUE_H_
#define _TEST_DEQUE_H_
#include"test\test.h"
#include"stl_deque.h"
#include<deque>
void test_deque();
struct Test_Deque {
	using T = XX::TestStruct;
	using std_deque = std::deque<T>;
	using xx_deque = XX::deque<T>;

	void test_push_back() {
		T ts(3, 4);
		std_deque dq1(5, ts);
		xx_deque dq2(5, ts);
		for (int i = 1;i < 99;i++) {
			T ts_temp(i, i*i);
			dq1.push_back(ts_temp);
			dq2.push_back(ts_temp);
		}
		XX::print_container(dq1);
		assert(XX::is_container_equal(dq1, dq2));
	}
};


#endif