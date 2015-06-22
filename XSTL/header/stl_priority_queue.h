#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_
#include"stl_heap.h"
#include"stl_vector.h"
namespace XX {
	template<typename T,typename Sequence=vector<T>>
	class priority_queue {
	public:
		using value_type = typename Sequence::value_type;
		using size_type = typename Sequence::size_type;
		using reference = typename Sequence::reference;
		using const_reference = typename Sequence::const_reference;
	private:
		//µ×²ãÈÝÆ÷
		Sequence c;
	public:
		priority_queue():c(){}
		template<typename InputIterator>
		priority_queue(InputIterator first, InputIterator last) : c(first, last) {
			make_heap(c.begin(), c.end());
		}
		bool empty() { return c.empty(); }
		size_type size() { return c.size(); }
		const_reference top() const{ return c.front(); }
		void push(const value_type&x) {
			c.push_back(x);
			push_heap(c.begin(), c.end());
		}
		void pop() {
			pop_heap(c.begin(), c.end());
			c.pop_back();
		}
	};
}

#endif
