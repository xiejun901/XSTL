#ifndef _STL_VECTOR_H_
#define _STL_VECTOR_H_
#include"stl_alloc.h"
#include"stl_construct.h"
#include"stl_uninitialized.h"

#include<initializer_list>//实现采用initializer_list来初始化

namespace XX{
	//template<typename T, typename Alloc = alloc>
	//class vector;

	/*template<typename T, typename Alloc = alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs){

	}
	template<typename T, typename Alloc = alloc>
	bool operator!=  (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs){

	}
	template<typename T, typename Alloc = alloc>
	bool operator<   (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs){

	}
	template<typename T, typename Alloc = alloc>
	bool operator<=  (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs){

	}
	template<typename T, typename Alloc = alloc>
	bool operator>   (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs){

	}
	template<typename T, typename Alloc = alloc>
	bool operator>=  (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs){

	}*/
	template<typename T, typename Alloc = alloc>
	class vector final{
		//友元，非成员函数
		/*friend bool operator== <T, Alloc> (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);
		friend bool operator!= <T, Alloc> (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);
		friend bool operator<  <T, Alloc> (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);
		friend bool operator<= <T, Alloc> (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);
		friend bool operator>  <T, Alloc> (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);
		friend bool operator>= <T, Alloc> (const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);*/
		//类型定义
	public:
		using value_type = T;
		using pointer = T*;
		using iterator = T*;
		using reference = T&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;

		using const_iterator = const T *;
		using const_reference = const T &;
	private:
		using data_allocator = simple_alloc<T, Alloc>;
		/*■■■■■■■■□□□□□□□□□
		  |               |                 | 
		start           finish         end_of_storage
		*/
		iterator start;
		iterator finish;
		iterator end_of_storage;
	public:
		//constructor
		vector() = default;
		explicit vector(size_type n, const T&value );
		explicit vector(size_type n);
		/*template<typename InputIterator>
		vector(InputIterator first, InputIterator last);*/
		vector(const vector &other);
		vector(vector &&other);
		vector(std::initializer_list<T> init);

		~vector();

		vector &operator = (const vector& rhs);
		vector &operator = (vector &&rhs);
		vector &operator = (std::initializer_list<T> ilist);

		void assign(size_type n, const T& value);
		//template<typename InputIterator>
		//void assign(InputIterator first, InputIterator last);
		void assign(std::initializer_list<T> ilist);

		reference         at(size_type pos);
		const_reference   at(size_type pos) const;

		reference         operator[](size_type pos);
		const_reference   operator[](size_type pos) const;

		reference         front();
		const_reference   front() const;

		reference		  back();
		const_reference   back() const;
		 
		T*                data();
		const T*          data() const;

		iterator          begin();
		const_iterator    begin() const;
		const_iterator    cbegin() const;

		iterator          end();
		const_iterator    end() const;
		const_iterator    cend() const;

		bool              empty() const;
		size_type         size() const;
		size_type         max_size() const;
		void              reserve(size_type new_cap);
		size_type         capacity() const;
		void              shrink_to_fit();
		
		void              clear();
		//iterator          insert(iterator pos, const T &value);//until c++11
		iterator          insert(const_iterator pos, const T &value);
		iterator          insert(const_iterator pos, T&&value);
		//void              insert(iterator pos, size_type n, const T &value);//until c++11
		iterator          insert(const_iterator pos, size_type n, const T &alue);
		//template<typename InputIterator>
		//void              insert(iterator pos, InputIterator first, InputIterator last);
		iterator          insert(const_iterator pos, std::initializer_list<T> ilist);

		iterator          erase(const_iterator pos);
		iterator          erase(const_iterator first, const_iterator last);

		void              push_back(const T& value);
		void              push_back(T&& value);
		void              pop_back();

		void              resize(size_type count);
		void              resize(size_type count, const value_type &value);
		void              swap(vector &other);

		//私有的工具函数
		bool check(size_type pos) const { return pos <= size(); }
		//将[first,last）之间的元素拷贝到dest开始的位置，返回值为拷贝的最后一个元素的下一个位置
		//iterator copy(iterator first, iterator last, iterator dest);
		/*void copy_backward(iterator first, iterator last, iterator dest_last);*/
		//void fill(iterator first, iterator last, const T &value);
	};
	//构造函数
	template<typename T, typename Alloc>
	vector<T,Alloc>::vector(size_type n, const T &value ){
		start = data_allocator::allocate(n);
		finish = start + n;
		end_of_storage = start + n;
		uninitialized_fill(start, finish, value);
	}

	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(size_type n){
		start = data_allocator::allocate(n);
		finish = start;
		end_of_storage = start + n;
	}
	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(const vector &other){
		size_t n = other.size();
		start = data_allocator::allocate(n);
		finish = uninitialized_copy(other.begin(), other.end(), start);
		end_of_storage = start + n;
	}
	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(vector &&other){
		start = other.start;
		finish = other.finish;
		end_of_storage =other.end_of_storage;
		other.start = 0;
		other.finish = 0;
		other.end_of_storage = 0;
	}
	template<typename T, typename Alloc>
	vector<T, Alloc>::vector(std::initializer_list<T> init){
		size_t n = init.size();
		start = data_allocator::allocate(n);
		finish = uninitialized_copy(init.begin(), init.end(), start);
		end_of_storage = start + n;
	}
	//赋值运算符
	template<typename T, typename Alloc>
	vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &rhs){
		size_t n= rhs.size();
		start = data_allocator::allocate(n);
		finish = uninitialized_copy(rhs.begin(), rhs.end(), start);
		end_of_storage = start + n;
		return *this;
	}
	template<typename T, typename Alloc>
	vector<T, Alloc> &vector<T, Alloc>::operator=(vector &&rhs){
		start = rhs.start;
		finish = rhs.finish;
		end_of_storage =rhs.end_of_storage;
		rhs.start = 0;
		rhs.finish = 0;
		rhs.end_of_storage = 0;
		return *this;
	}
	template<typename T, typename Alloc>
	vector<T, Alloc> &vector<T, Alloc>::operator=(std::initializer_list<T> ilist){
		size_t n = ilist.size();
		start = data_allocator::allocate(n);
		finish = uninitialized_copy(ilist.begin(), ilist.end(), start);
		end_of_storage = start + n;
		return *this;
	}
	//assign相关
	template<typename T, typename Alloc>
	void vector<T, Alloc>::assign(size_type n, const T &value){
		size_type cap = capacity();
		if (n > cap){
			destroy(start, finish);
			data_allocator::deallocate(start, cap);
			start = data_allocator::allocate(n);
			size_type newcap = n; /*cap + (n > cap ? n : cap);*/
			start = data_allocator::allocate(newcap);
			finish = start;
			end_of_storage = finish + newcap;
		}
		finish = uninitialized_fill_n(start, n, value);
	}
	template<typename T, typename Alloc>
	void vector<T, Alloc>::assign(std::initializer_list<T> ilist){
		size_type n = ilist.size();
		size_type cap = capacity();
		if (n > cap){
			destroy(start, finish);
			data_allocator::deallocate(start, cap);
			start = data_allocator::allocate(n);
			size_type newcap = n; /*cap + (n > cap ? n : cap);*/
			start = data_allocator::allocate(newcap);
			finish = start;
			end_of_storage = finish + newcap;
		}
		finish = uninitialized_copy(ilist.begin(), ilist.end(), start);
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type pos){
		if (check(pos))
			return *(start + pos);
		else
			exit(1);//return *finish;//这儿应该抛出异常的
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(size_type pos) const{
		if (check(pos))
			return *(cbegin() + pos);
		else
			exit(1);//return *finish;//这儿应该抛出异常的
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](size_type pos){
		return *(begin() + pos);
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](const size_type pos) const{
		return *(cbegin() + pos);
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::front(){
		return *(start);
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const{
		return *(start);
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::back(){
		return *(finish-1);
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const{
		return *(finish-1);
	}
	template<typename T, typename Alloc>
	T* vector<T, Alloc>::data(){
		return start;
	}
	template<typename T, typename Alloc>
	const T* vector<T, Alloc>::data() const{
		return start;
	}
	
	//迭代器相关
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin()const {
		return start;
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cbegin()const {
		return start;
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() {
		return start;
	}

	template<typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end()const {
		return finish;
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::end(){
		return finish;
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cend()const {
		return start;
	}
	//容量相关
	template<typename T, typename Alloc>
	bool vector<T, Alloc>::empty() const{
		return start == finish;
	}
	template<typename T, typename Alloc>
	size_t vector<T, Alloc>::size() const{
		return finish - start;
	}
	template<typename T, typename Alloc>
	size_t vector<T, Alloc>::max_size() const{
		return size_type(-1)/sizeof(T);
	}
	template<typename T, typename Alloc>
	void vector<T, Alloc>::reserve(size_type new_cap){
		if (new_cap > capacity()){
			iterator new_start = data_allocator::allocate(new_cap);
			iterator new_finish = uninitialized_copy(start, finish, new_start);
			destroy(start, finish);
			data_allocator::deallocate(start, capacity());
			start = new_start;
			finish = new_finish;
			end_of_storage = start + new_cap;
		}
	}
	template<typename T, typename Alloc>
	size_t vector<T, Alloc>::capacity() const{
		return end_of_storage - start;
	}
	template<typename T, typename Alloc>
	void vector<T, Alloc>::shrink_to_fit(){
		iterator new_start = data_allocator::allocate(size());
		iterator new_finish = uninitialized_copy(start, finish, new_start);
		destroy(start, finish);
		data_allocator::deallocate(start, capacity());
		start = new_start;
		finish = new_finish;
		end_of_storage = finish;
	}
	//修改内容
	template<typename T, typename Alloc>
	void vector<T, Alloc>::clear(){
		while (finish != start)
			destroy(--finish);
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos, const T &value){
		iterator rt = const_cast<iterator>(pos);
		if (finish == end_of_storage)
		{
			size_t new_cap = capacity() == 0 ? 1 : 2 * capacity();
			iterator new_start = data_allocator::allocate(new_cap);
			iterator new_finish=uninitialized_copy(start, rt, new_start);
			construct(new_finish++, value);
			new_finish = uninitialized_copy(rt, finish, new_finish);
			destroy(start, finish);
			data_allocator::deallocate(start, capacity());
			start = new_start;
			finish = new_finish;
			end_of_storage = start + new_cap;
		}
		else{
			iterator fi = finish;
			if (fi == rt)
				construct(fi, value);
			else{
				construct(fi, *(fi - 1));
				--fi;
				while (fi != rt){
					*fi = *(fi - 1);
					--fi;
				}
				*rt = value;
			}
			++finish;
		}
		return rt;
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos, T &&value){
		iterator rt = const_cast<iterator>(pos);
		if (finish == end_of_storage)
		{
			size_t new_cap = capacity() == 0 ? 1 : 2 * capacity();
			iterator new_start = data_allocator::allocate(new_cap);
			iterator new_finish = uninitialized_copy(start, rt, new_start);
			construct(new_finish++, value);
			new_finish = uninitialized_copy(rt, finish, new_finish);
			destroy(start, finish);
			data_allocator::deallocate(start, capacity());
			start = new_start;
			finish = new_finish;
			end_of_storage = start + new_cap;
		}
		else{
			iterator fi = finish;
			if (fi == rt)
				construct(fi, value);
			else{
				construct(fi, *(fi - 1));
				--fi;
				while (fi != rt){
					*fi = *(fi - 1);
					--fi;
				}
				*rt = value;
			}
			++finish;
		}
		return rt;
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos, size_type n, const T &value){
		iterator position = const_cast<iterator>(pos);
		if (capacity() - size() < n){
			size_t new_cap = (capacity()>n ? capacity() : n) + capacity();
			iterator new_start = data_allocator::allocate(new_cap);
			iterator new_finish = uninitialized_copy(start, position, new_start);
			new_finish = uninitialized_fill_n(new_finish, n, value);
			new_finish = uninitialized_copy(position, finish, new_finish);
			destroy(start, finish);
			data_allocator::deallocate(start, capacity());
			start = new_start;
			finish = new_finish;
			end_of_storage = start + new_cap;
			position = start + n;
		}
		else{
			iterator oldfinish = finish;
			const size_type element_after = finish - position;
			if (element_after > n){
				finish=uninitialized_copy(finish - n, finish, finish);
				copy_backward(position, oldfinish-n, oldfinish);
				fill(position, position + n, value);
			}
			else{
				finish=uninitialized_copy(position, oldfinish, position + n);
				uninitialized_fill(oldfinish, position + n, value);
				fill(position, oldfinish, value);
			}
		}
		return position;
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos, std::initializer_list<T> ilist){
		iterator position = const_cast<iterator>(pos);
		size_t n = ilist.size();
		if (capacity() - size() < n){
			size_t new_cap = (capacity()>n ? capacity() : n) + capacity();
			iterator new_start = data_allocator::allocate(new_cap);
			iterator new_finish = uninitialized_copy(start, position, new_start);
			new_finish = uninitialized_copy(ilist.begin(), ilist.end(), new_finish);
			new_finish = uninitialized_copy(position, finish, new_finish);
			destroy(start, finish);
			data_allocator::deallocate(start, capacity());
			start = new_start;
			finish = new_finish;
			end_of_storage = start + new_cap;
			position = start + n;
		}
		else{
			iterator oldfinish = finish;
			const size_type element_after = finish - position;
			if (element_after > n){
				finish = uninitialized_copy(finish - n, finish, finish);
				copy_backward(position, oldfinish - n, oldfinish);
				copy(ilist.begin(), ilist.end(), position);
			}
			else{
				finish = uninitialized_copy(position, oldfinish, position + n);
				//uninitialized_fill(oldfinish, position + n, value);
				//fill(position, oldfinish, value);
				copy(ilist.begin(), ilist.begin() + element_after, position);
				uninitialized_copy(ilist.begin() + element_after, ilist.end(), oldfinish);
			}
		}
		return position;
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(const_iterator pos){
		iterator cpos = const_cast<iterator>(pos);
		copy(cpos + 1, finish, cpos);
		destroy(--finish);
		return cpos;
	}
	template<typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(const_iterator first, const_iterator last){
		iterator cfirst = const_cast<iterator>(first);
		iterator clast = const_cast<iterator>(last);
		copy(clast, finish, cfirst);
		while (clast!=cfirst){
			--clast;
			destroy(--finish);
		}
		return cfirst;
	}
	template<typename T, typename Alloc>
	void vector<T, Alloc>::push_back(const T& value){
		if (finish == end_of_storage){
			size_t new_cap = capacity() == 0 ? 1 : 2 * capacity();
			iterator new_start = data_allocator::allocate(new_cap);
			iterator new_finish = uninitialized_copy(start, finish, new_start);
			destroy(start, finish);
			data_allocator::deallocate(start, capacity());
			start = new_start;
			finish = new_finish;
			end_of_storage = start + new_cap;
		}
		construct(finish++, value);
	}
	template<typename T, typename Alloc>
	void vector<T, Alloc>::push_back(T&& value){
		if (finish == end_of_storage){
			size_t new_cap = capacity() == 0 ? 1 : 2 * capacity();
			iterator new_start = data_allocator::allocate(new_cap);
			iterator new_finish = uninitialized_copy(start, finish, new_start);
			destroy(start, finish);
			data_allocator::deallocate(start, capacity());
			start = new_start;
			finish = new_finish;
			end_of_storage = start + new_cap;
		}
		construct(finish++, value);
	}
	template<typename T, typename Alloc>
	void vector<T, Alloc>::pop_back(){
		destroy(--finish);
	}
	//析构函数
	template<typename T, typename Alloc>
	vector<T, Alloc>::~vector()
	{
		while (finish != start)
			destroy(--finish);
		data_allocator::deallocate(start, end_of_storage - start);
	}
	//template<typename T, typename Alloc>
	//typename vector<T, Alloc>::iterator vector<T, Alloc>::copy(iterator first, iterator last, iterator dest){
	//	while (first != last){
	//		*dest = *first;
	//		dest++;
	//		first++;
	//	}
	//	return dest;
	//}
	//template<typename T, typename Alloc>
	//void vector<T, Alloc>::copy_backward(iterator first, iterator last, iterator dest_last)
	//{
	//	while (last != first)
	//	{
	//		--last;
	//		--dest_last;
	//		*dest_last = *last;
	//	}
	//}
	//template<typename T, typename Alloc>
	//void vector<T, Alloc>::fill(iterator first, iterator last, const T &value)
	//{
	//	while (first != last){
	//		*first = value;
	//		++first;
	//	}
	//}
}
#endif