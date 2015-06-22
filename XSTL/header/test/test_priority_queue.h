#pragma once
#include"stl_priority_queue.h"
#include"stl_vector.h"
#include"test.h"
#include<queue>
class Test_Priority_Queue {
public:
	void test() {
		XX::vector<int> vec{ 0,1,2,3,4,8,9,3,5 };
		XX::priority_queue<int> ipq(vec.begin(), vec.end());
		std::priority_queue<int> ipq2(vec.begin(), vec.end());
		while (!ipq.empty() && !ipq2.empty())
		{
			assert(ipq.top() == ipq2.top());
			ipq.pop();
			ipq2.pop();
		}
		assert(ipq.size() == ipq2.size());
	}
};