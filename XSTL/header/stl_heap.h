#ifndef _STL_HEAP_H_
#define _STL_HEAP_H_
#include"stl_iterator.h"
namespace XX {
	//包含了针对heap的一组操作

	//first,堆的第一个迭代器,holeIndex:插入新元素的迭代器与first的距离,topIndex:根结点与第一个迭代器的距离，一般为0，value:插入的值
	template<typename RandomAccessIterator,typename Distance,typename T>
	void _push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value) {
		Distance parent = (holeIndex - 1) / 2;
		while (holeIndex > topIndex&&*(first+parent) < value) {
			*(first + holeIndex) = *(first + parent);
			holeIndex = parent;
			parent= (holeIndex - 1) / 2;
		}
		*(first + holeIndex) = value;
	}

	template<typename RandomAccessIterator, typename Distance, typename T>
	inline void _push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance *, T * ) {
		_push_heap(first, Distance(last - first - 1), Distance(0), T(*(last - 1)));
	}
	//萃取出distance_type和value_type
	template<typename RandomAccessIterator>
	inline void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
		_push_heap_aux(first, last, distance_type(first), value_type(first));
	}

}
#endif
