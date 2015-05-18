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
		//����һ���յĹ��캯��
		std::cout << "����Ĭ�Ϲ��캯����";
		XX::vector<int> xxv;
		std::vector<int> stdv;
		result = vector_compare(xxv, stdv);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
	}
	{
		//����һ������17��42��vector
		std::cout << "���Թ��캯��vector(17,42)��";
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
		//�������캯��
		std::cout << "���Կ������캯����";
		XX::vector<int> xxv2(xxv1);
		std::vector<int> stdv2(stdv1);
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
	}

	{
		//c��ʼ���б��캯��
		std::cout << "���Գ�ʼ���б��캯����";
		XX::vector<int> xxv2{1,2,3,4,5,6,7,8,9};
		std::vector<int> stdv2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
	}

	{
		//��ֵ�����
		std::cout << "���Ը�ֵ�������";
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
		//��ֵ�����
		std::cout << "���Ը�ֵ�����,����ʼ���б�ֵ��vector��";
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
		std::cout << "����assign():" << std::endl;
		XX::vector<int> xxv2;
		std::vector<int> stdv2;
		xxv2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		stdv2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::cout << "��ǰvector�Ĵ�С��" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
		std::cout << "assign�Ĵ�С����ԭʼ��С��2��:";
		xxv2.assign(20, 7);
		stdv2.assign(20, 7);
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		std::cout << "��ǰvector�Ĵ�С��" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
		std::cout << "assign�Ĵ�СС��ԭʼ��С:";
		xxv2.assign(9, 8);
		stdv2.assign(9, 8);
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		std::cout << "��ǰvector�Ĵ�С��" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
		std::cout << "assign�Ĵ�С����ԭʼ��С��С��ԭʼ��С��2��:";
		xxv2.assign(35, 8);
		stdv2.assign(35, 8);
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		std::cout << "��ǰvector�Ĵ�С��" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
	}
	{
		//assign(),���ó�ʼ���б��assign��ֵ
		std::cout << "����assign():" << std::endl;
		XX::vector<int> xxv2;
		std::vector<int> stdv2;
		xxv2 = { 1, 2, 3 };
		stdv2 = { 1, 2, 3 };
		std::cout << "��ǰvector�Ĵ�С��" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
		std::cout << "assign�Ĵ�С����ԭʼ��С��2��:";
		xxv2.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
		stdv2.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		std::cout << "��ǰvector�Ĵ�С��" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
		std::cout << "assign�Ĵ�СС��ԭʼ��С:";
		xxv2.assign({ 1, 2, 3, 4, 5 });
		stdv2.assign({ 1, 2, 3, 4, 5 });
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		std::cout << "��ǰvector�Ĵ�С��" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
		std::cout << "assign�Ĵ�С����ԭʼ��С��С��ԭʼ��С��2��:";
		xxv2.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 });
		stdv2.assign({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 });
		result = vector_compare(xxv2, stdv2);
		if (result)
			std::cout << "test pass" << std::endl;
		else
			std::cout << "test not pass" << std::endl;
		std::cout << "��ǰvector�Ĵ�С��" << xxv2.capacity() << "," << stdv2.capacity() << std::endl;
	}
	return result;
}

bool test_at()
{
	bool result = true;
	std::cout << "����at():" << std::endl;
	XX::vector<int> xxv2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (int i = 0; i < 9; i++)
		std::cout << xxv2.at(i)<<',';
	//xxv2.at(11);
	std::cout << std::endl;
	std::cout << "����[]:" << std::endl;
	for (int i = 0; i < 9; i++)
		std::cout << xxv2[i] << ',';
	std::cout << std::endl;
	std::cout << "����front():" << std::endl;
	std::cout << xxv2.front() << std::endl;
	//xxv2.front() = 5;
	//std::cout << xxv2.front() << std::endl;
	std::cout << "����data():" << std::endl;
	int * p = xxv2.data();
	std::cout << *(p+2) << std::endl;

	std::cout << "����reserve():" << std::endl;
	std::cout <<"��ǰ��С:"<<xxv2.capacity() << std::endl;
	xxv2.reserve(100);
	std::cout << "�ĳ�100֮��:" << xxv2.capacity() << std::endl;
	xxv2.reserve(50);
	std::cout << "�ĳ�50֮��:" << xxv2.capacity() << std::endl;
	return result;
}

bool test_modify(){
	bool result = true;
	{
		std::cout << "���Բ���һ��Ԫ��:" << std::endl;
		std::vector<int> stdv = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		XX::vector<int> xxv = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::cout << "ԭʼ���:" << std::endl;
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
		std::cout << "�ڵ����λ�ò���17�����λ�ò���99֮��:" << std::endl;
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
		std::cout << "����eraseԪ��:" << std::endl;
		std::vector<int> stdv = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		XX::vector<int> xxv = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		std::cout << "ԭʼ���:" << std::endl;
		std::cout << "std:";
		for (auto i : stdv)
			std::cout << i << ',';
		std::cout << "XX:";
		for (auto i : xxv)
			std::cout << i << ',';
		std::cout << std::endl << "ɾ�������:" << std::endl;
		std::vector<int>::iterator it1 = stdv.begin() + 5;
		XX::vector<int>::iterator it2 = xxv.begin() + 5;
		stdv.erase(it1);
		xxv.erase(it2);
		std::cout << "ɾ����:" << std::endl;
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
		std::cout << std::endl << "ɾ�����嵽8��:" << std::endl;
		std::vector<int>::iterator it11 = stdv.begin() + 8;
		XX::vector<int>::iterator it22 = xxv.begin() + 8;
		stdv.erase(it1, it11);
		xxv.erase(it2, it22);
		std::cout << "ɾ����:" << std::endl;
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
		std::cout << "����push_back:" << std::endl;
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


