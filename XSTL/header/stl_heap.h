#ifndef _STL_HEAP_H_
#define _STL_HEAP_H_
#include"stl_iterator.h"
namespace XX {
	//���������heap��һ�����

	//first,�ѵĵ�һ��������,holeIndex:������Ԫ�صĵ�������first�ľ���,topIndex:��������һ���������ľ��룬һ��Ϊ0��value:�����ֵ
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
	//��ȡ��distance_type��value_type
	template<typename RandomAccessIterator>
	inline void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
		_push_heap_aux(first, last, distance_type(first), value_type(first));
	}

}
#endif
