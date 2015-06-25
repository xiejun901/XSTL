#ifndef _STL_TREE_H_
#define _STL_TREE_H_

//红黑树结点
namespace XX {
	template<typename T>
	struct _rb_tree_node {
		_rb_tree_color():_parent(nullptr),
						 _left(nullptr),
						 _right(nullptr),
						_color(0){}
		enum _rb_tree_color { _rb_tree_color_red, _rb_tree_color_black };
		_rb_tree_node _color;
		T _data;
		struct _rb_tree_node *_parent;
		struct _rb_tree_node *_left;
		struct _rb_tree_node *_right;

		//回去当前节点的
	};
}

#endif
