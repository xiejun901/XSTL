#ifndef _STL_ITERATOR_H_
#define _STL_ITERATOR_H_
#include<cstddef>
#pragma once
namespace XX {
	//五种迭代器类型，在编译期时就可以萃取出迭代器类型，这样可以提高效率，比如如果是随机访问迭代器，那么在访问相隔n个位置的迭代器时就可以直接用加法，而不一个个挨着加上去，通过这物种类型，可以使得不同迭代器类型调用不同的重载函数
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag :public input_iterator_tag {};
	struct bidirectional_iterator_tag :public forward_iterator_tag {};
	struct random_acess_iterator_tag :public bidirectional_iterator_tag {};

	template<typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
	struct iterator {
		using iterator_category = Category;
		using value_type = T;
		using difference_type = Distance;
		using pointer = Pointer;
		using reference = Reference;
	};

	//traits
	//从迭代器类型中"榨"出相应型比如我们有个迭代器是class my_iterator:public iterator<size_t,int>，那么iterator_traits<my_iterator>::pointer 就是int *，iterator_traits<my_iterator>::value_type 就是int
	template<typename Iterator>
	struct iterator_traits {
		using iterator_category = typename Iterator::iterator_category;
		using value_type = typename Iterator::value_type;
		using difference_type = typename Iterator::difference_type;
		using pointer = typename Iterator::pointer;
		using reference = typename Iterator::reference;

	};

	//针对原生指针的偏特化版traits
	template<typename T>
	struct iterator_traits<T*> {
		using iterator_category = random_acess_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;

	};
	//针对原生 指向常量的指针 偏特化版
	template<typename T>
	struct iterator_traits<const T*> {
		using iterator_category = random_acess_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;

	};

	//获取某个迭代器的类型,返回一个物种迭代器类型中的一种的对象
	template<typename Iterator>
	inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator &) {
		using category = typename iterator_traits<Iterator>::iterator_category;
		return category();
	}
	//获取distance type,返回一个difference_type*的对象
	template<typename Iterator>
	inline typename iterator_traits<Iterator>::difference_type* distance_type(const Iterator &) {
		return static_cast<iterator_traits<Iterator>::difference_type*>(0);
	}
	//获取value type,返回一个value_type *的对象
	template<typename Iterator>
	inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator &) {
		return static_cast<iterator_traits<Iterator>::value_type*>(0);
	}
	//distance函数
	template<typename InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, input_iterator_tag) {
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last) {
			++first;
			++n;
		}
		return n;
	}
	template<typename RandomAccessIterator>
	inline typename iterator_traits<RandomAccessIterator>::difference_type __distance(RandomAccessIterator first, RandomAccessIterator last, random_acess_iterator_tag) {
		return last - first;
	}
	template<typename InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
		using category = typename iterator_traits<InputIterator>::iterator_category;
		return __distance(first, last, category());
	}
	//advance函数
	template<typename InputIterator, typename Distance>
	inline void __advance(InputIterator &i, Distance n, input_iterator_tag) {
		while (n--)
			++i;
	}
	template<typename BidirectionalIterator, typename Distance>
	inline void __advance(BidirectionalIterator &i, Distance n, bidirectional_iterator_tag) {
		if (n > 0)
			while (n--) ++i;
		else
			while (n++) --i;
	}
	template<typename RandomAcessIterator, typename Distance>
	inline void __advance(RandomAcessIterator &i, Distance n, random_acess_iterator_tag) {
		i += n;
	}
	template<typename InputIterator, typename Distance>
	inline void advance(InputIterator &i, Distance n) {
		__advance(i, n, iterator_category(i));
	}
}

#endif