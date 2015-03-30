#include<memory>
#include<string>
#include<vector>
#include"Vector.h"
int main()
{
	std::vector<int> vec1;
	//std::allocator<int> alloc;
	//{
	//	XSTL::Vector<int> vec2;
	//	for (int i = 1; i < 10; i++)
	//		vec2.push_back(i);
	//	vec2.pop_back();
	//	vec2.push_back(22);
	//	vec2[2] = 134;
	//	vec2[3] = 445;
	//	vec2[6] = 678;
	//	for (XSTL::Vector<int>::iterator iter = vec2.begin(); iter != vec2.end(); ++iter)
	//		std::cout << *iter << std::endl;
	//}
	XSTL::Vector<std::string> a;
	//auto start = std::allocator<int>::allocate(20);
//	vec1.push_back(i*i);
//	auto const p = alloc.allocate(vec1.size);
	return 0;
}