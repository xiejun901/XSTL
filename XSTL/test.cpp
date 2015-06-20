#include"test.h"
#include"stl_vector.h"
#include"stl_heap.h"
#include<iostream>
namespace XX {
	std::ostream &operator<<(std::ostream& os, const TestStruct &x) {
		os << "<"<<x.a << ' ' << x.b<<">";
		return os;
	}
};