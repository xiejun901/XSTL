#ifndef _TEST_H_
#define _TEST_H_
#include<assert.h>
#include<iostream>
namespace XX {
	struct TestStruct {
		friend std::ostream &operator<<(std::ostream& os, const TestStruct &x);
		TestStruct(int _a,int _b):a(_a),b(_b){}
		int a;
		int b;
		bool operator==(const TestStruct other) {
			if (a == other.a&&b == other.b)
				return true;
			return false;
		}
		bool operator!=(const TestStruct other) {
			return !operator==(other);
		}
	};
	template<typename Container1,typename Container2>
	bool is_container_equal(Container1 c1, Container2 c2) {
		typename Container1::iterator iter1 = c1.begin();
		typename Container2::iterator iter2 = c2.begin();
		while (iter1 != c1.end() && iter2 != c2.end()) {
			if (*iter1 != *iter2)
				return false;
			++iter1;
			++iter2;
		}
		if (iter1 != c1.end() || iter2 != c2.end())
			return false;
		return true;
	}
	template<typename Container>
	void print_container(Container c) {
		typename Container::iterator iter = c.begin();
		while (iter != c.end()) {
			std::cout << *iter << ' ';
			++iter;
		}
		std::cout << std::endl;
	}
};
#endif
