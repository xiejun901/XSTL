#include"test.h"
#include"stl_vector.h"
#include<vector>
#include<iostream>
bool vector_compare(XX::vector<int> &xxv, std::vector<int> &stdv)
{
	XX::vector<int>::iterator iter1_xxv = xxv.begin();
	XX::vector<int>::iterator iter2_xxv = xxv.end();
	std::vector<int>::iterator iter1_stdv = stdv.begin();
	std::vector<int>::iterator iter2_stdv = stdv.end();
	while (iter1_xxv != iter2_xxv&&iter1_stdv != iter2_stdv)
	{
		if (*iter1_xxv != *iter1_stdv)
			return false;
		++iter1_stdv;
		++iter1_xxv;
	}
	if (iter1_xxv == iter2_xxv&&iter1_stdv == iter2_stdv)
		return true;
	else
		return false;
}
bool test_construtor(){
	bool result = true;
	{
		//构造一个空的构造函数
		std::cout << "测试默认构造函数：";
		XX::vector<int> xxv;
		std::vector<int> stdv;
		result = vector_compare(xxv, stdv);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
	}
	{
		//构造一个含有17个42的vector
		std::cout << "测试构造函数vector(17,42)：";
		XX::vector<int> xxv2(17,42);
		std::vector<int> stdv2(17,42);
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
	}
	{
		XX::vector<int> xxv1(17, 42);
		std::vector<int> stdv1(17, 42);
		//拷贝构造函数
		std::cout << "测试拷贝构造函数：";
		XX::vector<int> xxv2(xxv1);
		std::vector<int> stdv2(stdv1);
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
	}

	{
		//c初始化列表构造函数
		std::cout << "测试初始化列表构造函数：";
		XX::vector<int> xxv2{1,2,3,4,5,6,7,8,9};
		std::vector<int> stdv2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
	}

	{
		//赋值运算符
		std::cout << "测试赋值运算符：";
		XX::vector<int> xxv1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::vector<int> stdv1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		XX::vector<int> xxv2;
		std::vector<int> stdv2;
		xxv2 = xxv1;
		stdv2 = stdv1;
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
	}

	{
		//赋值运算符
		std::cout << "测试赋值运算符,将初始化列表赋值给vector：";
		XX::vector<int> xxv2;
		std::vector<int> stdv2;
		xxv2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		stdv2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
	}
	

	return result;
}

bool test_assign(){
	bool result = true;
	{
		//assign()
		std::cout << "测试assign():" << std::endl;
		XX::vector<int> xxv2;
		std::vector<int> stdv2;
		xxv2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		stdv2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::cout << "当前vector的大小：" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
		std::cout << "assign的大小大于原始大小的2倍:";
		xxv2.assign(20, 7);
		stdv2.assign(20, 7);
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		std::cout << "当前vector的大小：" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
		std::cout << "assign的大小小于原始大小:";
		xxv2.assign(9, 8);
		stdv2.assign(9, 8);
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		std::cout << "当前vector的大小：" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
		std::cout << "assign的大小大于原始大小，小于原始大小的2倍:";
		xxv2.assign(35, 8);
		stdv2.assign(35, 8);
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		std::cout << "当前vector的大小：" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
	}
	{
		//assign(),采用初始化列表给assign赋值
		std::cout << "测试assign():" << std::endl;
		XX::vector<int> xxv2;
		std::vector<int> stdv2;
		xxv2 = { 1, 2, 3 };
		stdv2 = { 1, 2, 3 };
		std::cout << "当前vector的大小：" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
		std::cout << "assign的大小大于原始大小的2倍:";
		xxv2.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
		stdv2.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		std::cout << "当前vector的大小：" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
		std::cout << "assign的大小小于原始大小:";
		xxv2.assign({ 1, 2, 3, 4, 5 });
		stdv2.assign({ 1, 2, 3, 4, 5 });
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		std::cout << "当前vector的大小：" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
		std::cout << "assign的大小大于原始大小，小于原始大小的2倍:";
		xxv2.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 });
		stdv2.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 });
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		std::cout << "当前vector的大小：" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
	}
	return result;
}

bool test_at()
{
	bool result = true;
	std::cout << "测试at():" << std::endl;
	XX::vector<int> xxv2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (int i = 0; i < 9; i++)
		std::cout << xxv2.at(i)<<',';
	//xxv2.at(11);
	std::cout << std::endl;
	std::cout << "测试[]:" << std::endl;
	for (int i = 0; i < 9; i++)
		std::cout << xxv2[i] << ',';
	std::cout << std::endl;
	std::cout << "测试front():" << std::endl;
	std::cout << xxv2.front() << std::endl;
	//xxv2.front() = 5;
	//std::cout << xxv2.front() << std::endl;
	std::cout << "测试data():" << std::endl;
	int * p = xxv2.data();
	std::cout << *(p+2) << std::endl;

	std::cout << "测试reserve():" << std::endl;
	std::cout <<"当前大小:"<<xxv2.capacity() << std::endl;
	xxv2.reserve(100);
	std::cout << "改成100之后:" << xxv2.capacity() << std::endl;
	xxv2.reserve(50);
	std::cout << "改成50之后:" << xxv2.capacity() << std::endl;
	return result;
}

bool test_modify(){
	bool result = true;
	{
		std::cout << "测试插入一个元素:" << std::endl;
		std::vector<int> stdv = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		XX::vector<int> xxv = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::cout << "原始情况:" << std::endl;
		std::cout << "std:";
		for (auto i : stdv)
			std::cout << i << ',';
		std::cout << "XX:";
		for (auto i : xxv)
			std::cout << i << ',';
		stdv.reserve(100);
		xxv.reserve(100);
		std::vector<int>::iterator it1 = stdv.begin() + 5;
		XX::vector<int>::iterator it2 = xxv.begin() + 5;
		int value = 17;
		stdv.insert(it1, { 3, 7, 2, 1, 9, 9, 9, 9 });
		xxv.insert(it2, { 3, 7, 2, 1, 9, 9, 9, 9 });
		it1 = stdv.end();
		it2 = xxv.end();
		value = 99;
		stdv.insert(it1, { 8, 9, 8, 9, 10, 11, 12 });
		xxv.insert(it2, { 8, 9, 8, 9, 10, 11, 12 });
		std::cout << "在第五个位置插入17，最后位置插入99之后:" << std::endl;
		std::cout << "std:";
		for (auto i : stdv)
			std::cout << i << ',';
		std::cout << "XX:";
		for (auto i : xxv)
			std::cout << i << ',';
		result = vector_compare(xxv, stdv);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;

	}
	{
		std::cout << "测试erase元素:" << std::endl;
		std::vector<int> stdv = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		XX::vector<int> xxv = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		std::cout << "原始情况:" << std::endl;
		std::cout << "std:";
		for (auto i : stdv)
			std::cout << i << ',';
		std::cout << "XX:";
		for (auto i : xxv)
			std::cout << i << ',';
		std::cout << std::endl << "删除第五个:" << std::endl;
		std::vector<int>::iterator it1 = stdv.begin() + 5;
		XX::vector<int>::iterator it2 = xxv.begin() + 5;
		stdv.erase(it1);
		xxv.erase(it2);
		std::cout << "删除后:" << std::endl;
		std::cout << "std:";
		for (auto i : stdv)
			std::cout << i << ',';
		std::cout << "XX:";
		for (auto i : xxv)
			std::cout << i << ',';
		result = vector_compare(xxv, stdv);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		it1 = stdv.begin() + 5;
		it2 = xxv.begin() + 5;
		std::cout << std::endl << "删除第五到8个:" << std::endl;
		std::vector<int>::iterator it11 = stdv.begin() + 8;
		XX::vector<int>::iterator it22 = xxv.begin() + 8;
		stdv.erase(it1, it11);
		xxv.erase(it2, it22);
		std::cout << "删除后:" << std::endl;
		std::cout << "std:" << stdv.size() << ",,";
		for (auto i : stdv)
			std::cout << i << ',';
		std::cout << "XX:" << xxv.size() << ",,";
		for (auto i : xxv)
			std::cout << i << ',';
		result = vector_compare(xxv, stdv);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
	}
	{
		std::cout << "测试push_back:" << std::endl;
		XX::vector<int> xxv;
		std::vector<int> stdv;
		for (int i = 0; i < 10; i++)
		{
			xxv.push_back(i);
			stdv.push_back(i);
		}
		for (auto i : stdv)
			std::cout << i << ',';
		std::cout << "XX:" << xxv.size() << ",,";
		for (auto i : xxv)
			std::cout << i << ',';
		xxv.push_back(77);
		stdv.push_back(77);
		xxv.push_back(88);
		stdv.push_back(88);
		xxv.push_back(99);
		stdv.push_back(99);
		xxv.push_back(100);
		stdv.push_back(100);
		std::cout << std::endl;
		for (auto i : stdv)
			std::cout << i << ',';
		std::cout << "XX:" << xxv.size() << ",,";
		for (auto i : xxv)
			std::cout << i << ',';
		result = vector_compare(xxv, stdv);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		xxv.pop_back();
		stdv.pop_back();
		xxv.pop_back();
		stdv.pop_back();
		xxv.pop_back();
		stdv.pop_back();
		xxv.pop_back();
		stdv.pop_back();
		std::cout << std::endl;
		for (auto i : stdv)
			std::cout << i << ',';
		std::cout << "XX:" << xxv.size() << ",,";
		for (auto i : xxv)
			std::cout << i << ',';
		result = vector_compare(xxv, stdv);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;

	}

	return result;

}


