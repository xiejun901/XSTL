#ifndef _STL_UNIITIALIZED_H_
#define _STL_UNIITIALIZED_H_
#include"stl_construct.h"
namespace XX{
	template<typename InputIterator, typename ForwardIterator>
	ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator dest)
	{
		while (first != last)
		{
			construct(&*dest, *first);
			++first;
			++dest;
		}
		return dest;
	}

	template<typename ForwardIterator,typename T>
	void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &value)
	{
		while (first != last)
		{
			construct(first, value);
			first++;
		}
	}

	template<typename ForwardIterator,typename Size,typename T>
	ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T &value)
	{
		for (Size i = 0; i < n; ++first, ++i)
		{
			construct(first, value);
		}
		return first;
	}
	template<typename InputIterator, typename ForwardIterator>
	ForwardIterator copy(InputIterator first, InputIterator last, ForwardIterator dest){
		while (first != last){
			*dest = *first;
			dest++;
			first++;
		}
		return dest;
	}
	template<typename InputIterator, typename ForwardIterator>
	void copy_backward(InputIterator first, InputIterator last, ForwardIterator dest_last)
	{
		while (last != first)
		{
			--last;
			--dest_last;
			*dest_last = *last;
		}
	}
	template<typename ForwardIterator, typename T>
	void fill(ForwardIterator first, ForwardIterator last, const T &value){
		while (first != last){
			*first = value;
			++first;
		}
	}

}


#endif