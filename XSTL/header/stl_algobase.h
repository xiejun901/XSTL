#ifndef _STL_ALGOBASE_H_
#define _STL_ALGOBASE_H_

namespace XX{

	template<typename T>
	void swap(T x, T y)
	{
		T temp = x;
		x = y;
		y = temp;
	}
}

#endif
