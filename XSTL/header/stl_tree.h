#ifndef _STL_TREE_H_
#define _STL_TREE_H_
#include<ctype.h>
#include"stl_iterator.h"
#include"stl_alloc.h"
#include"stl_construct.h"
#include"stl_algobase.h"
#define private public
//��������

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

		//�ҵ�ĳ�����������
		static _rb_tree_node_base_ptr minimum(_rb_tree_node_base_ptr x) {
			while (x->_left != nullptr)
				x = x->_left;
			return x;
		}
		//�ҵ�ĳ�����������
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
				while (_node == y->_right) {
					_node = y;
					y = _node->_parent;
				}
				if(_node->_right!=y)
					_node = y;
			}
		}
		void _decrement() {
			/*if (_node->_left != nullptr)
				_node = _rb_tree_node_base::maximum(_node->_left);
			else {
				_rb_tree_node_ptr y = _node->_parent;
				while (y != nullptr&&_node == y->_left) {
					_node = y;
					y = _node->_parent;
				}
				_node = y;
			}*/
			if (_node->_color == _rb_tree_color_red && _node->_parent->_parent == _node) //��ɫ��Ϊ�����ָ������header�ڵ㣬header����ǰһ���ڵ�Ϊ���ڵ�
				_node = _node->_right;
			else if (_node->_left != nullptr)
				_node = _rb_tree_node_base::maximum(_node);
			else{
				_rb_tree_node_ptr y = _node->_parent;
				while (_node == y->_left) {
					_node = y;
					y = y->_parent;
				}
				_node = y;
			}
		}	
	};
	inline bool operator==(const _rb_tree_base_iterator x, const _rb_tree_base_iterator y)
	{
		return x._node == y._node;
	}
	inline bool operator!=(const _rb_tree_base_iterator x, const _rb_tree_base_iterator y)
	{
		return x._node != y._node;
	}
	template<typename T,typename Ref,typename Ptr>
	struct _rb_tree_iterator:_rb_tree_base_iterator{
		using pointer = Ptr;
		using reference = Ref;
		using value_type = T;

		using iterator = _rb_tree_iterator<T, T&, T*>;
		using const_iterator = _rb_tree_iterator<T, const T&, const T*>;
		using self = _rb_tree_iterator<T, Ref, Ptr>;

		using _link_type = _rb_tree_node<T> *;

		_rb_tree_iterator(){}
		_rb_tree_iterator(_link_type x) { _node = x; }
		_rb_tree_iterator(const _rb_tree_iterator&it) { _node = it._node; }
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
		     typename KeyOfValue,//�������ͣ�ͨ���˺����ܻ�ȡkey
		     typename Compare,//�������Ƚϴ�С
		     typename Alloc=alloc>
	class rb_tree {
	//���Ͷ���
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
		rb_tree(const Compare comp = Compare()) :key_compare(comp),node_count(0)
		{
			init();
		}
		Compare key_comp() const { return key_comp; }
		iterator begin() const { return leftmost(); }
		iterator end() const { return header;/*rightmost();*/ }
		bool empty() const { return node_count == 0; }
		size_type size() const { return node_count; }
		size_type max_size() const { return size_type(-1); }

		iterator insert_equal(const value_type& v);
		void erase(iterator position);

        ~rb_tree();
	private:
		link_type get_node();
		void put_node(link_type p);
		link_type create_node(const value_type x);
		void destroy_node(link_type p);
        void _erase(link_type x);//erase without rebalancing
        void clear();

		//��Ҫ������ڵ��ָ��������_rb_tree_node_base *���͵ģ���Ҫǿ��ת��Ϊ_rb_tree_node *����  (T &)x�� *((T *)&x)��Ч����һ����ͬreinterpret_cast;
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

		static link_type minimum(link_type x) { return (link_type)_rb_tree_node_base::minimum(x); }
		static link_type maximum(link_type x) { return (link_type)_rb_tree_node_base::maximum(x); }
		static base_ptr minimum(base_ptr x) { return _rb_tree_node_base::minimum(x); }
		static base_ptr maximum(base_ptr x) { return _rb_tree_node_base::maximum(x); }
		void trans_plant(base_ptr u, base_ptr v);

		//��ʼ��һ������ֻ��һ���ս�㼴ֻ��header���
		void init();
		void rotation_right(base_ptr x);
		void rotation_left(base_ptr x);

		//����һ������
		iterator _insert(base_ptr _x, base_ptr _y, const value_type& v);
		void _rb_tree_rebalance(base_ptr z);
		base_ptr _delete(base_ptr z);
		void _rb_tree_delete_rebalance(base_ptr x);
		//˽�г�Ա
	private:
		size_type node_count;//��¼�ڵ�����
		link_type header;//һ����㣬�˽ڵ�����������С�Ľ�㣬�ҽڵ������Ķ��ӣ����ڵ㣬�μ��㷨�����е�nil�ڵ㣬�����nil�ڵ�����˸�����Ϣ��Ϊ�߽�
		Compare key_compare;//���ڱȽ�key��С�ĺ�������
		
	};
	
	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const value_type & v)
	{
		link_type x = root();
		link_type y = header;
		while (x != nullptr)
		{
			y = x;
			x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
		}
		return _insert(x,y,v);
	}

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator position)
	{
		_delete(position._node);
		--node_count;
	}

    template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
    inline rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::~rb_tree()
    {
        clear(); 
        put_node(header);
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
    inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_erase(link_type x)
    {
        while (x != nullptr)
        {
            _erase(right(x));
            link_type y = left(x);
            destroy_node(x);
            x = y;
        }
    }

    template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
    inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::clear()
    {
        if (node_count != 0)
        {
            _erase(root());
            leftmost() = header;
            root() = nullptr;
            rightmost() = header;
            node_count = 0;
        }
    }

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::trans_plant(base_ptr u, base_ptr v)
	{
		if (u->_parent == header)
			header->_parent = v;
		else if (u == u->_parent->_left)
			u->_parent->_left = v;
		else
			u->_parent->_right = v;
		if(v!=nullptr)
			v->_parent = u->_parent;
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

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_insert(base_ptr _x, base_ptr _y, const value_type & v)
	{
		link_type x = (link_type)_x;
		link_type y = (link_type)_y;
		link_type z;
		if (y == header || key_compare(KeyOfValue()(v), key(y)))
		{
			//�����������룬�Լ��ж��Ƿ�Ҫ�ô˽ڵ�Ϊ����㣬�Լ�ȷ���������ҽڵ�
			z = create_node(v);
			left(y) = z;
			if (y == header)
			{
				root() = z;
				rightmost() = z;
			}
			else if (y == leftmost())
				leftmost() = z;
		}
		else
		{
			z = create_node(v);
			right(y) = z;
			if (y == rightmost())
				rightmost() = z;
		}
		parent(z) = y;
		left(z) = nullptr;
		right(z) = nullptr;

		_rb_tree_rebalance(z);
		++node_count;
		return iterator(z);

	}

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	inline void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_rb_tree_rebalance(base_ptr z)
	{
		z->_color = _rb_tree_color_red;
		while (z != root() && z->_parent->_color == _rb_tree_color_red)
		{
			if (z->_parent == z->_parent->_parent->_left)
			{
				base_ptr y = z->_parent->_parent->_right;
				if (y&&y->_color == _rb_tree_color_red)
				{
					z->_parent->_color = _rb_tree_color_black;
					y->_color = _rb_tree_color_black;
					z->_parent->_parent->_color = _rb_tree_color_red;
					z = z->_parent->_parent;
				}
				else 
				{
					if (z == z->_parent->_right)
					{
						z = z->_parent;
						rotation_left(z);
					}
					z->_parent->_color = _rb_tree_color_black;
					z->_parent->_parent->_color = _rb_tree_color_red;
					rotation_right(z->_parent->_parent);
				}
			}
			else
			{
				base_ptr y = z->_parent->_parent->_left;
				if (y&&y->_color == _rb_tree_color_red)
				{
					z->_parent->_color = _rb_tree_color_black;
					y->_color = _rb_tree_color_black;
					z->_parent->_parent->_color = _rb_tree_color_red;
					z = z->_parent->_parent;
				}
				else
				{
					if (z = z->_parent->_left)
					{
						z = z->_parent;
						rotation_right(z);
					}
					z->_parent->_color = _rb_tree_color_black;
					z->_parent->_parent->_color = _rb_tree_color_red;
					rotation_left(z->_parent->_parent);
				}
			}
		}
		root()->_color = _rb_tree_color_black;
	}

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	inline typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>:: base_ptr rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_delete(base_ptr z)
	{
		base_ptr y = z;
		base_ptr x = nullptr;
		base_ptr x_parent = nullptr;
		//������Ϊ��
		if (y->_left == nullptr)
			x = y->_right;
		else
		{
			if (y->_right == nullptr)
				x = y->_left;
			else
			{
				y = minimum(y->_right);
				x = y->_right;
			}
		}
		if (y != z)
		{
			z->_left->_parent = y;
			y->_left = z->_left;
			if (y != z->_right)
			{
				x_parent = y->_parent;
				if (x)
					x->_parent = y->_parent;
				y->_parent->_left = x;
				y->_right = z->_right;
				z->_right->_parent = y;
			}
			else
				x_parent = y;
			if (header->_parent == z)
				header->_parent = y;
			else if (z->_parent->_left == z)
				z->_parent->_left = y;
			else
				z->_parent->_right = y;
			y->_parent = z->_parent;
			swap(y->_color, z->_color);
			y = z;
		}
		else //y==z
		{
			x_parent = y->_parent;
			if (x)
				x->_parent = y->_parent;
			if (header->_parent == z)
				header->_parent = x;
			else
			{
				if (z->_parent->_left == z)
					z->_parent->_left = x;
				else
					z->_parent->_right = x;
			}
			if (header->_left == z)
			{
				if (z->_right == nullptr)
					header->_left = z->_parent;
				else
					header->_left = minimum(x);
			}
			if (header->_right == z)
			{
				if (z->_left == nullptr)
					header->_right = z->_parent;
				else
					header->_right = maximum(x);
			}
		}
		if (y->_color != _rb_tree_color_red)
		{
			while (x != header->_parent && (x == nullptr || x->_color == _rb_tree_color_black))
			{
				if (x == x_parent->_left)
				{
					base_ptr w = x_parent->_right;
					if (w->_color == _rb_tree_color_red)
					{
						x_parent->_color = _rb_tree_color_red;
						w->_color = _rb_tree_color_black;
						rotation_left(x_parent);
						w = x_parent->_right;
					}
					if ((w->_right==nullptr || w->_right->_color == _rb_tree_color_black)&&
						(w->_left==nullptr || w->_left->_color == _rb_tree_color_black))
					{
						w->_color = _rb_tree_color_red;
						x = x_parent;
						x_parent = x_parent->_parent;
					}
					else
					{
						if (w->_right == nullptr || w->_right->_color == _rb_tree_color_black)
						{
							if(w->_left)
								w->_left->_color = _rb_tree_color_black;
							w->_color = _rb_tree_color_red;
							rotation_right(w);
							w = x_parent->_right;
						}
						if(w->_right)
							w->_right->_color = _rb_tree_color_black;
						w->_color = x_parent->_color;
						x_parent->_color = _rb_tree_color_black;
						rotation_left(x_parent);
						//x = header->_parent;
						break;
					}
				}
				else
				{
					base_ptr w = x_parent->_left;
					if (w->_color == _rb_tree_color_red)
					{
						x_parent->_color = _rb_tree_color_red;
						w->_color = _rb_tree_color_black;
						rotation_right(x_parent);
						w = x_parent->_left;
					}
					if ((w->_left == nullptr ||w->_left->_color == _rb_tree_color_black)&&
						(w->_right == nullptr || w->_right->_color == _rb_tree_color_black))
					{
						w->_color = _rb_tree_color_red;
						x = x_parent;
						x_parent = x_parent->_parent;
					}
					else
					{
						if (w->_left == nullptr || w->_left->_color == _rb_tree_color_black)
						{
							w->_color = _rb_tree_color_red;
							if(w->_right)
								w->_right->_color = _rb_tree_color_black;
							rotation_left(w);
							w = x_parent->_left;
						}
						if(w->_left)
							w->_left->_color = _rb_tree_color_black;
						w->_color = x_parent->_color;
						x_parent->_color = _rb_tree_color_black;
						rotation_right(x_parent);
						//x = header->_parent;
						break;
					}
				}
			}
			if(x)
				x->_color = _rb_tree_color_black;
		}
		return y;
		//if (y->_color != _rb_tree_color_red)
		//	_rb_tree_delete_rebalance(x);
		/*color_type yOriginalColor = y->_color;
		if (z->_left == nullptr)
		{
			x = z->_right;
			trans_plant(z, z->_right);
			if (z == header->_left)
			{
				if (z->_right == nullptr)
					header->_left = z->_parent;
				else
					header->_left = minimum(z->_right);
			}
			if (z == header->_right)
			{
				header->_right = z->_parent;
			}
		}
		else if (nullptr == z->_right)
		{
			x = z->_left;
			trans_plant(z, z->_left);
			if (z == header->_right)
			{
				header->_right = maximum(z->_left);
			}
		}
		else
		{
			y = minimum(z->_right);
			yOriginalColor = y->_color;
			x = y->_right;
			if (y->_parent == z)
				x->_parent = y;
			else
			{
				trans_plant(y, y->_right);
				y->_right = z->_right;
				y->_right->_parent = y;
			}
			trans_plant(z, y);
			y->_left = z->_left;
			y->_left->_parent = y;
			y->_color = z->_color;
		}
		if (yOriginalColor == _rb_tree_color_black)
			_rb_tree_delete_rebalance(x);*/
	}

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc>
	void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_rb_tree_delete_rebalance(base_ptr x)
	{
		while (x != header->_parent && x->_color == _rb_tree_color_black)
		{
			if (x == x->_parent->_left)
			{
				base_ptr w = x->_parent->_right;
				if (w->_color == _rb_tree_color_red)
				{
					x->_parent->_color = _rb_tree_color_red;
					w->_color = _rb_tree_color_black;
					rotation_left(x->_parent);
					w = x->_parent->_right;
				}
				if (w->_right->_color == _rb_tree_color_black&&w->_left->_color == _rb_tree_color_black)
				{
					w->_color = _rb_tree_color_red;
					x = x->_parent;
				}
				else
				{
					if (w->_right->_color == _rb_tree_color_black)
					{
						w->_color = _rb_tree_color_red;
						w->_left->_color = _rb_tree_color_black;
						rotation_right(w);
						w = w->_parent->_right;
					}
					w->_right->_color = _rb_tree_color_black;
					w->_color = x->_parent->_color;
					x->_parent->_color = _rb_tree_color_black;
					rotation_left(x->_parent);
					x = root();
				}
			}
			else
			{
				base_ptr w = x->_parent->_left;
				if (w->_color == _rb_tree_color_red)
				{
					x->_parent->_color = _rb_tree_color_red;
					w->_color = _rb_tree_color_black;
					rotation_right(x->_parent);
					w = x->_parent->_left;
				}
				if (w->_left->_color == _rb_tree_color_black&&w->_right->_color == _rb_tree_color_black)
				{
					w->_color = _rb_tree_color_red;
					x = x->_parent;
				}
				else
				{
					if (w->_left->_color == _rb_tree_color_black)
					{
						w->_color = _rb_tree_color_red;
						w->_right->_color = _rb_tree_color_black;
						rotation_left(w);
						w = w->_parent->_left;
					}
					w->_left->_color = _rb_tree_color_black;
					w->_color = x->_parent->_color;
					x->_parent->_color = _rb_tree_color_black;
					rotation_right(x->_parent);
					x = header->_parent;
				}
			}
		}
		x->_color = _rb_tree_color_black;
	}

	

}

#endif
