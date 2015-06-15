#include"test_list.h"
#include"test_vector.h"
#include<list>
#include<windows.h>
#include"type_traits.h"
#include"stl_deque.h"
#include"test_deque.h"
#include"test_stack.h"
#include"test_queue.h"
using namespace std;
int main() {
	while (1) {
		//test_list_protype();
		test_deque();
		test_stack();
		test_queue();
		Sleep(100);
	}
	system("pause");
	return 0;
}