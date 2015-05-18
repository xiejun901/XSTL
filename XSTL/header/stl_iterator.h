#ifndef _STL_ITERATOR_H_
#define _STL_ITERATOR_H_
#include<cstddef>
#pragma once
namespace XX {
	//���ֵ��������ͣ��ڱ�����ʱ�Ϳ�����ȡ�����������ͣ������������Ч�ʣ����������������ʵ���������ô�ڷ������n��λ�õĵ�����ʱ�Ϳ���ֱ���üӷ�������һ�������ż���ȥ��ͨ�����������ͣ�����ʹ�ò�ͬ���������͵��ò�ͬ�����غ���
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
	//�ӵ�����������"ե"����Ӧ�ͱ��������и���������class my_iterator:public iterator<size_t,int>����ôiterator_traits<my_iterator>::pointer ����int *��iterator_traits<my_iterator>::value_type ����int
	template<typename Iterator>
	struct iterator_traits {
		using iterator_category = typename Iterator::iterator_category;
		using value_type = typename Iterator::value_type;
		using difference_type = typename Iterator::difference_type;
		using pointer = typename Iterator::pointer;
		using reference = typename Iterator::reference;

	};

	//���ԭ��ָ���ƫ�ػ���traits
	template<typename T>
	struct iterator_traits<T*> {
		using iterator_category = random_acess_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;

	};
	//���ԭ�� ָ������ָ�� ƫ�ػ���
	template<typename T>
	struct iterator_traits<const T*> {
		using iterator_category = random_acess_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;

	};

	//��ȡĳ��������������,����һ�����ֵ����������е�һ�ֵĶ���
	template<typename Iterator>
	inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator &) {
		using category = typename iterator_traits<Iterator>::iterator_category;
		return category();
	}
	//��ȡdistance type,����һ��difference_type*�Ķ���
	template<typename Iterator>
	inline typename iterator_traits<Iterator>::difference_type* distance_type(const Iterator &) {
		return static_cast<iterator_traits<Iterator>::difference_type*>(0);
	}
	//��ȡvalue type,����һ��value_type *�Ķ���
	template<typename Iterator>
	inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator &) {
		return static_cast<iterator_traits<Iterator>::value_type*>(0);
	}
	//distance����
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
	//advance����
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