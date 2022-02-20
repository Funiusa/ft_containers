
#ifndef FT_CONTAINERS_RBTREENODE_HPP
#define FT_CONTAINERS_RBTREENODE_HPP

#define RED   false
#define BLACK true
#define nullptr NULL

#include <iostream>
#include "../Iterator/iteratorTraits.hpp"

// RB TREE NODE BASE
namespace ft {
	struct RbTreeNodeBase {
		typedef RbTreeNodeBase *_base_ptr;
		typedef const RbTreeNodeBase *_const_base_ptr;
		bool color;
		_base_ptr parent;
		_base_ptr left;
		_base_ptr right;

		static _base_ptr _S_minimum(_base_ptr x) {
			while (x->left != nullptr) x = x->left;
			return x;
		}

		static _const_base_ptr _S_minimum(_const_base_ptr x) {
			while (x->left != nullptr) x = x->left;
			return x;
		}

		static _base_ptr _S_maximum(_base_ptr x) {
			while (x->right != nullptr) x = x->right;
			return x;
		}

		static _const_base_ptr _S_maximum(_const_base_ptr x) {
			while (x->right != nullptr) x = x->right;
			return x;
		}
	};

	static RbTreeNodeBase *local_Rb_tree_decrement(RbTreeNodeBase *x) throw() {
		if (x->color == RED
			&& x->parent->parent == x)
			x = x->right;
		else if (x->left != nullptr) {
			RbTreeNodeBase *y = x->left;
			while (y->right != nullptr)
				y = y->right;
			x = y;
		} else {
			RbTreeNodeBase *y = x->parent;
			while (x == y->left) {
				x = y;
				y = y->parent;
			}
			x = y;
		}
		return x;
	}

	RbTreeNodeBase *rb_tree_decrement(RbTreeNodeBase *x) throw() {
		return local_Rb_tree_decrement(x);
	}

	const RbTreeNodeBase *rb_tree_decrement(const RbTreeNodeBase *x) throw() {
		return local_Rb_tree_decrement(const_cast<RbTreeNodeBase *>(x));
	}

	static RbTreeNodeBase *local_Rb_tree_increment(RbTreeNodeBase *x) throw() {
		if (x->right != nullptr) {
			x = x->right;
			while (x->left != nullptr)
				x = x->left;
		} else {
			RbTreeNodeBase *y = x->parent;
			while (x == y->right) {
				x = y;
				y = y->parent;
			}
			if (x->right != y)
				x = y;
		}
		return x;
	}

	RbTreeNodeBase *rb_tree_increment(RbTreeNodeBase *x) throw() {
		return local_Rb_tree_increment(x);
	}

	const RbTreeNodeBase *rb_tree_increment(const RbTreeNodeBase *x) throw() {
		return local_Rb_tree_increment(const_cast<RbTreeNodeBase *>(x));
	}

	// TREE NODE BASE
	template<typename Val>
	struct rb_tree_node : public RbTreeNodeBase {
		typedef rb_tree_node<Val> *_link_type;
		Val value_field;

		rb_tree_node(const Val &v) : RbTreeNodeBase(), value_field(v) {}

		Val *valptr() { return &value_field; }

		const Val *valptr() const { return &value_field; }
	};

}


#endif //FT_CONTAINERS_RBTREENODE_HPP
