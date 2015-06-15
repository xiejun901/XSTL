#ifndef _STL_STACK_H_
#define _STL_STACK_H_
#include"stl_deque.h"
namespace XX {	
	template<typename T, typename Sequence = deque<T>>
	class stack {
	public:
		using value_type = typename Sequence::value_type;
		using size_type = typename Sequence::size_type;
		using reference = typename Sequence::reference;
		using const_reference = typename Sequence::const_reference;
	private:
		//µ×²ãÈÝÆ÷
		Sequence c;
	public:
		bool empty() { return c.empty(); }
		size_type size() { return c.size(); }
		reference top() { return c.back(); }
		const_reference top() const { return c.back(); }
		void push(const value_type &x) { c.push_back(x); }
		void pop() { c.pop_back(); }
	};
}
#endif
