
#ifndef FT_CONTAINERS_TREEITERATOR_HPP
#define FT_CONTAINERS_TREEITERATOR_HPP

#include <iostream>
#include "../Iterator/iteratorTraits.hpp"
#include "../Map/RbTreeNode.hpp"


template<class ValueType>
class RbTreeIterator :
		public ft::iterator<ft::bidirectional_iterator_tag, ValueType> {
public:
	typedef ValueType value_type;
	typedef ft::bidirectional_iterator_tag iterator_category;
	typedef typename ft::iterator<iterator_category, value_type>::pointer pointer;
	typedef typename ft::iterator<iterator_category, value_type>::reference reference;
	typedef typename ft::iterator<iterator_category,
			value_type>::difference_type difference_type;

	typedef RbTreeIterator<value_type> _self;
	typedef typename ft::rb_tree_node<value_type>::_base_ptr _base_ptr;
	typedef typename ft::rb_tree_node<value_type> *_link_type;

	_base_ptr _node;

	RbTreeIterator() : _node() {}

	RbTreeIterator(const RbTreeIterator &src) : _node(src.base()) {}

	RbTreeIterator(_base_ptr x) : _node(x) {}

	template<typename _Iter>
	RbTreeIterator(const RbTreeIterator<_Iter> &src) : _node(src.base()) {}

	~RbTreeIterator() {};

	const _base_ptr base() const { return (_node); }

	reference operator*() const { return *static_cast<_link_type>(_node)->valptr(); }

	pointer operator->() const { return static_cast<_link_type> (_node)->valptr(); }

	bool operator==(const _self &x) const { return _node == x._node; }

	bool operator!=(const _self &x) const { return _node != x._node; }

	_self &operator++() {
		_node = rb_tree_increment(_node);
		return *this;
	}

	_self &operator--() {
		_node = rb_tree_decrement(_node);
		return *this;
	}

	_self operator++(int) {
		_self _tmp = *this;
		_node = rb_tree_increment(_node);
		return _tmp;
	}

	_self operator--(int) {
		_self _tmp = *this;
		_node = rb_tree_decrement(_node);
		return _tmp;
	}
};

template<typename ValueType>
class RbTreeConstIterator :
		public ft::iterator<ft::bidirectional_iterator_tag, ValueType> {
public:
	typedef ValueType value_type;
	typedef RbTreeIterator<ValueType> iterator;
	typedef ft::bidirectional_iterator_tag iterator_category;
	typedef const ValueType &reference;
	typedef const ValueType *pointer;
	typedef typename ft::iterator<iterator_category,
			value_type>::difference_type difference_type;

	typedef RbTreeConstIterator<ValueType> _self;
	typedef ft::RbTreeNodeBase::_const_base_ptr _base_ptr;
	typedef const ft::rb_tree_node<ValueType> *_link_type;

	_base_ptr _node;

	RbTreeConstIterator() : _node() {}

	RbTreeConstIterator(_base_ptr x) : _node(x) {}

	RbTreeConstIterator(const iterator &it) : _node(it._node) {}

	bool operator==(const _self &x) const { return _node == x._node; }

	bool operator!=(const _self &x) const { return _node != x._node; }

	iterator _M_const_cast() const {
		return iterator(const_cast<typename iterator::_base_ptr>(_node));
	}

	reference operator*() const {
		return *static_cast<_link_type>(_node)->valptr();
	}

	pointer operator->() const {
		return static_cast<_link_type>(_node)->valptr();
	}

	_self &operator++() {
		_node = rb_tree_increment(_node);
		return *this;
	}

	_self &operator--() {
		_node = rb_tree_decrement(_node);
		return *this;
	}

	_self operator++(int) {
		_self _tmp = *this;
		_node = rb_tree_increment(_node);
		return _tmp;
	}

	_self operator--(int) {
		_self _tmp = *this;
		_node = rb_tree_decrement(_node);
		return _tmp;
	}
};

template<class ValueType>
RbTreeIterator<ValueType> operator+(int a, RbTreeIterator<ValueType> b) {
	return (b.base() + a);
}

template<class ValueType>
RbTreeConstIterator<ValueType> operator+(int a, RbTreeConstIterator<ValueType> b) {
	return (b.base() + a);
}

template<typename Val>
bool operator==(const RbTreeIterator<Val> &x, const RbTreeConstIterator<Val> &y) {
	return x._node == y._node;
}

template<typename Val>
bool operator!=(const RbTreeIterator<Val> &x, const RbTreeConstIterator<Val> &y) {
	return x._node != y._node;
}

#endif //FT_CONTAINERS_TREEITERATOR_HPP
