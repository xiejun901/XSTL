#ifndef _TEST_DEQUE_H_
#define _TEST_DEQUE_H_
#include"test\test.h"
#include"stl_deque.h"
#include"stl_vector.h"
#include<windows.h>
#include<deque>
#include<fstream>
void test_deque();
struct Test_Deque {
	using T = XX::TestStruct;
	using std_deque = std::deque<T>;
	using xx_deque = XX::deque<T>;
	using xx_vector = XX::vector<T>;

	void test_push_pop() {
		using std::cout;
		T ts(3);
		//测试析构函数，如果析构函数有问题内存会快速增加
		//for (;;)
		//{
		//	{
		//		xx_deque dq1(105, ts);
		//		//Sleep(10);
		//	}

		//}
		std_deque dq1(5, ts);
		xx_deque dq2(5, ts);
		for (int i = 1;i < 999;i++) {
			T ts_temp = i;
			dq1.push_back(ts_temp);
			dq2.push_back(ts_temp);
			dq1.push_front(ts_temp);
			dq2.push_front(ts_temp);
		}
		for (int i = 1;i < 999;++i) {
			dq1.pop_back();
			dq2.pop_back();
			dq1.pop_front();
			dq2.pop_front();
		}
		//XX::print_container(cout,dq1);
		//cout << std::endl << "------------------------------------------------" << std::endl;
		//XX::print_container(cout,dq2);
		assert(XX::is_container_equal(dq1, dq2));
	}
	void test_ctor() {
		{
			std_deque dq1;
			xx_deque dq2;
			for (int i = 1;i < 999;i++) {
				T ts_temp = i;
				dq1.push_back(ts_temp);
				dq2.push_back(ts_temp);
				dq1.push_front(ts_temp);
				dq2.push_front(ts_temp);
			}
			for (int i = 1;i < 99;++i) {
				dq1.pop_back();
				dq2.pop_back();
				dq1.pop_front();
				dq2.pop_front();
			}
		}
		{
			xx_vector vec;
			for (int i = 1;i < 999;++i) {
				vec.push_back(i);
			}
			std_deque dq1(vec.begin(), vec.end());
			xx_deque dq2(vec.begin(), vec.end());
			assert(XX::is_container_equal(dq1, dq2)&& XX::is_container_equal(dq1, vec));
		}
		{
			std::deque<int> dq1(999, 99);
			XX::deque<int> dq2(999,99);
			//XX::print_container(std::cout, dq1);
			//XX::print_container(std::cout, dq2);
			assert(XX::is_container_equal(dq1, dq2));
		}
		{
			xx_deque dq2;
			for (int i = 1;i < 33;i++) {
				T ts_temp = i;
				dq2.push_back(ts_temp);
				dq2.push_front(ts_temp);
			}
			xx_deque dq1(dq2);
			assert(XX::is_container_equal(dq1, dq2));
		}
	}
	void test_capacity() {
		{
			std_deque dq1;
			xx_deque dq2;
			assert(dq1.empty() == dq2.empty());
			for (int i = 1;i < 99;++i) {
				T ts_temp = i;
				dq1.push_back(ts_temp);
				dq2.push_back(ts_temp);
				dq1.push_front(ts_temp);
				dq2.push_front(ts_temp);
			}
			assert(dq1.size() == dq2.size());
			assert(dq1.empty() == dq2.empty());
		}
	}
	void test_iterator() {
		const xx_deque dq1(5, 77);
		auto iter = dq1.cbegin();
	}
	void test_modifiers() {
		{
			T ts(3);
			xx_deque dq1(77, ts);
			std_deque dq2(77, ts);
			assert(XX::is_container_equal(dq1, dq2));
			dq1.clear();
			dq2.clear();
			assert(XX::is_container_equal(dq1, dq2));
		}
		{
			xx_deque dq1;
			std_deque dq2;
			for (int i = 1;i < 10;++i) {
				T ts_temp = i;
				dq1.push_back(ts_temp);
				dq2.push_back(ts_temp);
				dq1.push_front(ts_temp);
				dq2.push_front(ts_temp);
			}
			dq1.erase(dq1.begin() + 5);
			dq2.erase(dq2.begin() + 5);
			assert(XX::is_container_equal(dq1, dq2));
		}
	}
	void test_element_acess() {
		{
			xx_deque dq1;
			std_deque dq2;
			for (int i = 1;i < 100;++i) {
				T ts_temp = i;
				dq1.push_back(ts_temp);
				dq2.push_back(ts_temp);
				dq1.push_front(ts_temp);
				dq2.push_front(ts_temp);
			}
			assert(dq1.front()==dq2.front());
			assert(dq1.back() == dq2.back());
		}
	}
};


#endif