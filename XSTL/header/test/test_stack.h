#ifndef _TEST_STACK_H_
#define _TEST_STACK_H_
#include"test\test.h"
#include"stl_stack.h"
#include<windows.h>
#include<stack>
#include<fstream>
void test_stack();
struct Test_Stack {
	using T = XX::TestStruct;
	using std_stack = std::stack<T>;
	using xx_stack = XX::stack<T>;

	void test() {
		std_stack st1;
		xx_stack st2;
		for (int i = 1;i <= 99;i++) {
			T ts_temp = i;
			st1.push(ts_temp);
			st2.push(ts_temp);
		}
		while (!st1.empty() && !st2.empty()) {
			assert(st1.top() == st2.top());
			st1.pop();
			st2.pop();
		}
		assert(st1.size() == st2.size());
	}
};
#endif
