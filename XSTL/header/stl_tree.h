#ifndef _STL_TREE_H_
#define _STL_TREE_H_
#include<ctype.h>
#include"stl_iterator.h"
#include"stl_alloc.h"
#define private public
//红黑树结点

namespace XX {
	using _rb_tree_color_type = bool;
	const _rb_tree_color_type _rb_tree_color_red = false;
	const _rb_tree_color_type _rb_tree_color_black = true;
	struct _rb_tree_node_base {
		using _rb_tree_node_base_ptr = _rb_tree_node_base *;
		_rb_tree_node_base() :_parent(nullptr),
			_left(nullptr),
			_right(nullptr),
			_color(_rb_tree_color_red) {}
		//enum _rb_tree_color { _rb_tree_color_red, _rb_tree_color_black };
		_rb_tree_color_type _color;
		_rb_tree_node_base_ptr _parent;
		_rb_tree_node_base_ptr _left;
		_rb_tree_node_base_ptr _right;

		//找到某子树的最大结点
		static _rb_tree_node_base_ptr minimum(_rb_tree_node_base_ptr x) {
			while (x->_left != nullptr)
				x = x->_left;
			return x;
		}
		//找到某子树的最大结点
		static _rb_tree_node_base_ptr maximum(_rb_tree_node_base_ptr x) {
			while (x->_right)
				x = x->_right;
			return x;
		}
	};
	template<typename T>
	struct _rb_tree_node :_rb_tree_node_base {
		T _field;
		using _link_type = _rb_tree_node<T> *;
	};
	struct _rb_tree_base_iterator {
		using _rb_tree_node_ptr = _rb_tree_node_base::_rb_tree_node_base_ptr;
		using iterator_category = bidirectional_iterator_tag;
		using difference_type = ptrdiff_t;
		_rb_tree_node_ptr _node;

		void _increment() {
			if (_node->_right != nullptr)
				_node = _rb_tree_node_base::minimum(_node->_right);
			else {
				_rb_tree_node_ptr y= _node->_parent;
				while (y != nullptr&&_node == y->_right) {
					_node = y;
					y = _node->_parent;
				}
				_node = y;
			}
		}
		void _decrement() {
			if (_node->_left != nullptr)
				_node = _rb_tree_node_base::maximum(_node->_left);
			else {
				_rb_tree_node_ptr y = _node->_parent;
				while (y != nullptr&&_node == y->_left) {
					_node = y;
					y = _node->_parent;
				}
				_node = y;
			}
		}	
	};
	template<typename T,typename Ref,typename Ptr>
	struct _rb_tree_iterator:_rb_tree_base_iterator{
		using pointer = Ptr;
		using reference = Ref;
		using value_type = T;

		using iterator = _rb_tree_iterator<T, T&, T*>;
		using const_iterator = _rb_tree_iterator<T, const T&, const T*>;
		using self = _rb_tree_iterator<T, Ref, Ptr>;

		using _link_type = _rb_tree_node<T> *;

		reference operator*() const {
			return _link_type(_node)->_field;
		}
		pointer operator->() const {
			return &(operator *());
		}
		self &operator++() {
			_increment();
			return *this;
		}
		self operator++(int) {
			self temp = *this;
			this->_increment();
			return temp;
		}
		self &operator--() {
			_decrement();
			return *this;
		}
		self operator--(int) {
			self temp = *this;
			_decrement();
			return temp;
		}
	};
	template<typename Key,
		     typename Value,
		     typename KeyOfValue,//函数类型，通过此函数能获取key
		     typename Compare,//函数，比较大小
		     typename Alloc=alloc>
	class rb_tree {
	//类型定义
	private:
		using void_pointer = void *;
		using base_ptr = _rb_tree_node_base *;
		using rb_tree_node = _rb_tree_node<Value>;
		using rb_tree_node_allocator = simple_alloc<rb_tree_node,Alloc>;
		using color_type = _rb_tree_color_type;

	public:
		using ket_type = Key;
		using value_type = Value;
		using pointer = Value *;
		using const_pointer = const value_type *;
		using reference = value_type &;
		using const_reference = const value_type &;
		using link_type = rb_tree_node *;
		using size_type = size_t;
		using difference_type = ptrdiff_t;

		using iterator = _rb_tree_iterator<value_type, reference, pointer>;
		using const_iterator = _rb_tree_iterator<value_type, const_reference, const_pointer>;
		using const_reverse_iterator = reverse_iterator<const_iterator>;
		using reverse_iterator = reverse_iterator<iterator>;
	public:
		rb_tree(const Compare comp=Compare());
	private:
		link_type get_node();
		void put_node(link_type p);
		link_type create_node(const value_type x);
		void destroy_node(link_type p);

		//主要是这儿节点的指针类型是_rb_tree_node_base *类型的，需要强制转换为_rb_tree_node *类型  (T &)x和 *((T *)&x)的效果是一样的同reinterpret_cast;
		link_type &root() const { return (link_type&)(header->_parent); }
		link_type &leftmost() const { return (link_type&)(header->_left); }
		link_type &rightmost() const { return (link_type&)(header->_right); }

		static link_type& left(link_type x) { return (link_type&)(x->_left); }
		static link_type& right(link_type x) { return (link_type&)(x->_right); }
		static link_type& parent(link_type x) { return (link_type&)(x->_parent); }
		static reference value(link_type x) { return x->_field; }
		static const Key& key(link_type x) { return KeyOfValue()(value(x)); }
		static color_type& color(link_type x) { return (color_type&)(x->_color); }

		static link_type& left(base_ptr x) { return (link_type&)(x->_left); }
		static link_type& right(base_ptr x) { return (link_type&)(x->_right); }
		static link_type& parent(base_ptr x) { return (link_type&)(x->_parent); }
		static reference value(base_ptr x) { return ((link_type &)x)->_field; }
		static const Key& key(base_ptr x) { return KeyOfValue()(value(x)); }
		static color_type& color(base_ptr x) { return (color_type&)(x->_color); }

		//初始化一棵树，只有一个空结点即只有header结点
		void init();
		void rotation_right(base_ptr x);
		void rotation_left(base_ptr x);
		//私有成员
	private:
		size_type node_count;//记录节点数量
		link_type header;//一个结点，此节点的左儿子是最小的结点，右节点是最大的儿子，父节点，参见算法导论中的nil节点，这儿将nil节点添加了附加信息作为边界
		Compare key_compare;//用于比较key大小的函数对象
		
	};
	
	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::rb_tree(const Compare comp):key_compare(comp)
	{
		init();
	}

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	inline typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::link_type rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::get_node()
	{
		return rb_tree_node_allocator::allocate();
	}

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::put_node(link_type p)
	{
		rb_tree_node_allocator::deallocate(p);
	}

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	inline typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::link_type rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::create_node(const value_type x)
	{
		link_type temp = get_node();
		construct(&temp->_field, x);
		return temp;
	}

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::destroy_node(link_type p)
	{
		destroy(&p->_field);
		put_node(p);
	}

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::init()
	{
		header = get_node();
		color(header) = _rb_tree_color_red;

		root() = nullptr;
		leftmost() = header;
		rightmost() = header;
	}

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::rotation_right(base_ptr x)
	{
		base_ptr y = x->_left;
		x->_left = y->_right;
		if (y->_right != nullptr)
			y->_right->_parent = x;
		y->_parent = x->_parent;
		if (parent(x) == header)
			header->_parent = y;
		else if (x == x->_parent->_left)
			x->_parent->_left = y;
		else
			x->_parent->_right = y;
		y->_right = x;
		x->_parent = y;

	}

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::rotation_left(base_ptr x)
	{
		base_ptr y = x->_right;
		x->_right = y->_left;
		if (y->_left != nullptr)
			y->_left->_parent = x;
		y->_parent = x->_parent;
		if (parent(x) == header)
			header->_parent = y;
		else if (x == x->_parent->_left)
			x->_parent->_left = y;
		else
			x->_parent->_right = y;
		x->_parent = y;
		y->_left = x;
	}

}

#endif
