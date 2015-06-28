#include"test_list.h"
#include"test_vector.h"
#include<list>
#include<vector>
#include<windows.h>
#include"type_traits.h"
#include"stl_deque.h"
#include"test_deque.h"
#include"test_stack.h"
#include"test_queue.h"
#include"stl_heap.h"
#include"stl_priority_queue.h"
#include"test_tree.h"
//using namespace std;
namespace XX {
	void test_heap() {
		vector<int> ivec{ 0,1,2,3,4,8,9,3,5 };
		make_heap(ivec.begin(), ivec.end());
		print_container(std::cout, ivec);
		ivec.push_back(7);
		push_heap(ivec.begin(), ivec.end());
		print_container(std::cout, ivec);
		pop_heap(ivec.begin(), ivec.end());
		std::cout << ivec.back() << std::endl;
		ivec.pop_back();
		print_container(std::cout, ivec);
		sort_heap(ivec.begin(), ivec.end());
		print_container(std::cout, ivec);

	}
}
int main() {
	while (1) {
		//test_list_protype();
		test_tree();
		test_deque();
		test_stack();
		test_queue();
		XX::test_heap();
		Sleep(100);
	}
	system("pause");
	return 0;
}