#pragma once
#include"stl_queue.h"
#include"test/test.h"
#include<queue>
#include<fstream>
void test_queue();
struct Test_Queue {
	using T = XX::TestStruct;
	using std_queue = std::queue<T>;
	using xx_queue = XX::queue<T>;

	void test() {
		std_queue q1;
		xx_queue q2;
		for (int i = 1;i <= 99;i++) {
			T ts_temp = i;
			q1.push(ts_temp);
			q2.push(ts_temp);
			assert(q1.front() == q2.front());
		}
		assert(q1.size() == q2.size());
		while (!q1.empty() && !q2.empty()) {
			assert(q1.front() == q2.front());
			q1.pop();
			q2.pop();
		}
		assert(q1.size() == q2.size());
	}
};


