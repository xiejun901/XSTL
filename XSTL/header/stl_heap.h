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
	//�����ѣ��������λ��0��Ԫ�أ���Ҫ��λ��0��Ԫ���½���ʹ�öѵ����ʱ��ֳ���
	template<typename RandomAccessIterator,typename Distance,typename T>
	void _adjust_heap(RandomAccessIterator first, Distance holIndex, Distance len, T value) {
		Distance leftChild = 2 * holIndex + 1;
		Distance rightChild = 2 * holIndex + 2;
		while (leftChild < len) {
			Distance maxIndex = holIndex;
			if (*(first + leftChild)>*(first + maxIndex))
				maxIndex = leftChild;
			if (*(first + rightChild) > *(first + maxIndex)&&rightChild<len)
				maxIndex = rightChild;
			if (maxIndex == holIndex)
				break;
			else {
				*(first + holIndex) = *(first + maxIndex);
				*(first + maxIndex) = value;
				holIndex = maxIndex;
				leftChild = 2 * holIndex + 1;
				rightChild = 2 * holIndex + 2;
			}
		}
		//*(first + holIndex) = value;
	}
	template<typename RandomAccessIterator>
	inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
		_pop_heap_aux(first, last, value_type(first));
	}

	template<typename RandomAccessIterator,typename T>
	inline void _pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*){
		_pop_heap(first, last - 1, last - 1, T(*(last - 1)), distance_type(first));
	}

	template<typename RandomAccessIterator, typename T, typename Distance>
	inline void _pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, T value, Distance *){
		*result = *first;
		*first = value;
		_adjust_heap(first, 0, Distance(last - first), value);
	}
	//heap����
	template<typename RandomAccessIterator>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last){
		while (last - first > 1)
			pop_heap(first, last--);
	}
	//����heap
	template<typename RandomAccessIterator>
	inline void make_heap(RandomAccessIterator first, RandomAccessIterator last) {
		_make_heap(first, last, value_type(first), distance_type(first));
	}
	template<typename RandomAccessIterator,typename T,typename Distance>
	void _make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance *) {
		if (last - first < 2)
			return;
		Distance len = last - first;
		Distance holeIndex = (len - 2) / 2;
		while (true) {
			_adjust_heap(first, holeIndex, len, T(*(first + holeIndex)));
			if (holeIndex == 0)
				return;
			holeIndex--;
		}
	}
}
#endif
