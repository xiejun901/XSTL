#ifndef _STL_TREE_H_
#define _STL_TREE_H_
#include<ctype.h>
#include"stl_iterator.h"
//红黑树结点
namespace XX {
	struct _rb_tree_node_base {
		using _rb_tree_node_base_ptr = _rb_tree_node_base *;
		_rb_tree_node_base() :_parent(nullptr),
			_left(nullptr),
			_right(nullptr),
			_color(_rb_tree_color_red) {}
		enum _rb_tree_color { _rb_tree_color_red, _rb_tree_color_black };
		_rb_tree_color _color;
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
}

#endif
