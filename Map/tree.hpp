
#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#include <iostream>
#include "../Iterator/treeIterator.hpp"
#include "../Iterator/reverseIterator.hpp"
#include "pair.hpp"
#include "RbTreeNode.hpp"

namespace ft {
	template<class Key, class Val, class KeyOfValue, class Compare,
			class Allocator = std::allocator<Val> >
	class Tree {
		typedef typename Allocator::template rebind<rb_tree_node<Val> >::other
				_node_allocator;
	protected:
		typedef RbTreeNodeBase *_base_ptr;
		typedef const RbTreeNodeBase *_const_base_ptr;
	public:
		typedef Key key_type;
		typedef Val value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef rb_tree_node<Val> *_link_type;
		typedef const rb_tree_node<Val> *_const_link_type;
		typedef Compare key_compare;
		typedef size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef Allocator allocator_type;
		typedef RbTreeIterator<value_type> iterator;
		typedef RbTreeConstIterator<value_type> const_iterator;
		typedef ft::reverseIterator<iterator> reverse_iterator;
		typedef ft::reverseIterator<const_iterator> const_reverse_iterator;
	private:
		RbTreeNodeBase _header;
		key_compare _comp;
		allocator_type _alloc;
		_node_allocator _node_alloc;
		size_t _node_count;
	public:
		Tree(const Compare &comp = key_compare(), const Allocator &alloc = allocator_type())
				: _comp(comp), _alloc(alloc) {
			_header.left = &_header;
			_header.right = &_header;
			_header.parent = nullptr;
			_header.color = RED;
			_node_count = 0;
		}

		Tree(const Tree &x, const Compare &comp = key_compare(), const Allocator &alloc = allocator_type())
				: _comp(comp), _alloc(alloc) {
			_header.left = &_header;
			_header.right = &_header;
			_header.parent = nullptr;
			_header.color = RED;
			_node_count = 0;
			if (x._header.parent)
				_M_root() = _M_copy(x);
		}

		~Tree() {
			clear();
		}

	protected:
		_base_ptr &_M_leftmost() { return this->_header.left; }

		_const_base_ptr _M_leftmost() const { return this->_header.left; }

		_base_ptr &_M_rightmost() { return this->_header.right; }

		_const_base_ptr _M_rightmost() const { return this->_header.right; }

		static const_reference _S_value(_const_link_type x) { return *x->valptr(); }

		static const_reference _S_value(_const_base_ptr x) {
			return *static_cast<_const_link_type>(x)->valptr();
		}

		static const Key &_S_key(_const_link_type x) { return KeyOfValue()(_S_value(x)); }

		static const Key &_S_key(_const_base_ptr x) { return KeyOfValue()(_S_value(x)); }

		static _link_type _S_left(_base_ptr x) { return static_cast<_link_type>(x->left); }

		static _const_link_type _S_left(_const_base_ptr x) {
			return static_cast<_const_link_type>(x->left);
		}

		static _link_type _S_right(_base_ptr x) {
			return static_cast<_link_type>(x->right);
		}

		static _const_link_type _S_right(_const_base_ptr x) {
			return static_cast<_const_link_type>(x->right);
		}

		static _base_ptr _S_minimum(_base_ptr x) {
			return RbTreeNodeBase::_S_minimum(x);
		}

		static _const_base_ptr _S_minimum(_const_base_ptr x) {
			return RbTreeNodeBase::_S_minimum(x);
		}

		static _base_ptr _S_maximum(_base_ptr x) {
			return RbTreeNodeBase::_S_maximum(x);
		}

		static _const_base_ptr _S_maximum(_const_base_ptr x) {
			return RbTreeNodeBase::_S_maximum(x);
		}

		_base_ptr &_M_root() { return this->_header.parent; }

		_const_base_ptr _M_root() const { return this->_header.parent; }

		_link_type _M_begin() { return (static_cast<_link_type>(_header.parent)); }

		_const_link_type _M_begin() const {
			return (static_cast<_const_link_type>(_header.parent));
		}

		_base_ptr _M_end() { return (&_header); }

		_const_base_ptr _M_end() const { return (&_header); }

		iterator _M_lower_bound(_link_type x, _base_ptr y,
								const Key &k) {
			while (x != 0)
				if (!_comp(_S_key(x), k))
					y = x, x = _S_left(x);
				else
					x = _S_right(x);
			return iterator(y);
		}

		const_iterator _M_lower_bound(_const_link_type x, _const_base_ptr y,
									  const Key &k) const {
			while (x != 0)
				if (!_comp(_S_key(x), k))
					y = x, x = _S_left(x);
				else
					x = _S_right(x);
			return const_iterator(y);
		}

		iterator _M_upper_bound(_link_type x, _base_ptr y,
								const Key &k) {
			while (x != 0)
				if (_comp(k, _S_key(x)))
					y = x, x = _S_left(x);
				else
					x = _S_right(x);
			return iterator(y);
		}

		const_iterator _M_upper_bound(_const_link_type x, _const_base_ptr y,
									  const Key &k) const {
			while (x != 0)
				if (_comp(k, _S_key(x)))
					y = x, x = _S_left(x);
				else
					x = _S_right(x);
			return const_iterator(y);
		}

		void _M_reset() {
			_header.parent = nullptr;
			_header.left = &_header;
			_header.right = &_header;
			_node_count = 0;
		}

		void _M_move_data(Tree &from) {
			_header.color = from._header.color;
			_header.parent = from._header.parent;
			_header.left = from._header.left;
			_header.right = from._header.right;
			_header.parent->parent = &_header;
			_node_count = from._node_count;
			from._M_reset();
		}

		void _M_drop_node(_link_type p) {
			_node_alloc.destroy(p);
			_node_alloc.deallocate(p, 1);
		}

		void _M_erase_aux(const_iterator position) {
			_link_type y = static_cast<_link_type>(eraseRebalance
					(const_cast<_base_ptr>(position._node),
					 this->_header));
			_M_drop_node(y);
			--_node_count;
		}

		void _M_erase(_link_type x) {
			while (x != 0) {
				_M_erase(_S_right(x));
				_link_type y = _S_left(x);
				_M_drop_node(x);
				x = y;
			}
		}

		void _M_erase_aux(const_iterator first, const_iterator last) {
			if (first == begin() && last == end())
				clear();
			else
				while (first != last)
					_M_erase_aux(first++);
		}

		_link_type _M_clone_node(_const_link_type x) {
			_link_type tmp = _node_alloc.allocate(1);
			_node_alloc.construct(tmp, *x);
			tmp->color = x->color;
			tmp->left = 0;
			tmp->right = 0;
			return tmp;
		}

		_link_type _M_copy(_const_link_type x, _base_ptr p) {
			_link_type top = _M_clone_node(x);
			top->parent = p;
			if (x->right)
				top->right = _M_copy(_S_right(x), top);
			p = top;
			x = _S_left(x);
			while (x != 0) {
				_link_type y = _M_clone_node(x);
				p->left = y;
				y->parent = p;
				if (x->right)
					y->right = _M_copy(_S_right(x), y);
				p = y;
				x = _S_left(x);
			}
			return top;
		}

		_link_type _M_copy(const Tree &x) {
			_link_type root = _M_copy(x._M_begin(), _M_end());
			_M_leftmost() = _S_minimum(root);
			_M_rightmost() = _S_maximum(root);
			_node_count = x._node_count;
			return root;
		}

		RbTreeNodeBase
		*eraseRebalance(RbTreeNodeBase *const z,
						RbTreeNodeBase &header) throw() {
			RbTreeNodeBase *&root = header.parent;
			RbTreeNodeBase *&leftmost = header.left;
			RbTreeNodeBase *&rightmost = header.right;
			RbTreeNodeBase *y = z;
			RbTreeNodeBase *x = nullptr;
			RbTreeNodeBase *x_parent = nullptr;
			if (y->left == nullptr)
				x = y->right;
			else if (y->right == nullptr)
				x = y->left;
			else {
				y = y->right;
				while (y->left != nullptr)
					y = y->left;
				x = y->right;
			}
			if (y != z) {
				z->left->parent = y;
				y->left = z->left;
				if (y != z->right) {
					x_parent = y->parent;
					if (x) x->parent = y->parent;
					y->parent->left = x;
					y->right = z->right;
					z->right->parent = y;
				} else
					x_parent = y;
				if (root == z)
					root = y;
				else if (z->parent->left == z)
					z->parent->left = y;
				else
					z->parent->right = y;
				y->parent = z->parent;
				ft::swap(y->color, z->color);
				y = z;
			} else {
				x_parent = y->parent;
				if (x)
					x->parent = y->parent;
				if (root == z)
					root = x;
				else if (z->parent->left == z)
					z->parent->left = x;
				else
					z->parent->right = x;
				if (leftmost == z) {
					if (z->right == 0)
						leftmost = z->parent;
					else
						leftmost = RbTreeNodeBase::_S_minimum(x);
				}
				if (rightmost == z) {
					if (z->left == 0)
						rightmost = z->parent;
					else
						rightmost = RbTreeNodeBase::_S_maximum(x);
				}
			}
			if (y->color != RED) {
				while (x != root && (x == 0 || x->color == BLACK))
					if (x == x_parent->left) {
						RbTreeNodeBase *w = x_parent->right;
						if (w->color == RED) {
							w->color = BLACK;
							x_parent->color = RED;
							rotate_left(x_parent, root);
							w = x_parent->right;
						}
						if ((w->left == 0 ||
							 w->left->color == BLACK) &&
							(w->right == 0 ||
							 w->right->color == BLACK)) {
							w->color = RED;
							x = x_parent;
							x_parent = x_parent->parent;
						} else {
							if (w->right == nullptr
								|| w->right->color == BLACK) {
								w->left->color = BLACK;
								w->color = RED;
								rotateRight(w, root);
								w = x_parent->right;
							}
							w->color = x_parent->color;
							x_parent->color = BLACK;
							if (w->right)
								w->right->color = BLACK;
							rotate_left(x_parent, root);
							break;
						}
					} else {
						RbTreeNodeBase *w = x_parent->left;
						if (w->color == RED) {
							w->color = BLACK;
							x_parent->color = RED;
							rotateRight(x_parent, root);
							w = x_parent->left;
						}
						if ((w->right == nullptr ||
							 w->right->color == BLACK) &&
							(w->left == nullptr ||
							 w->left->color == BLACK)) {
							w->color = RED;
							x = x_parent;
							x_parent = x_parent->parent;
						} else {
							if (w->left == nullptr || w->left->color == BLACK) {
								w->right->color = BLACK;
								w->color = RED;
								rotate_left(w, root);
								w = x_parent->left;
							}
							w->color = x_parent->color;
							x_parent->color = BLACK;
							if (w->left)
								w->left->color = BLACK;
							rotateRight(x_parent, root);
							break;
						}
					}
				if (x) x->color = BLACK;
			}
			return y;
		}

		ft::pair<_base_ptr, _base_ptr>
		_M_get_insert_hint_unique_pos(const_iterator position,
									  const key_type &k) {
			iterator pos = position._M_const_cast();
			typedef pair<_base_ptr, _base_ptr> res;
			if (pos._node == _M_end()) {
				if (size() > 0
					&& _comp(_S_key(_M_rightmost()), k))
					return res(0, _M_rightmost());
				else
					return _M_get_insert_unique_pos(k);
			} else if (_comp(k, _S_key(pos._node))) {
				iterator before = pos;
				if (pos._node == _M_leftmost())
					return res(_M_leftmost(), _M_leftmost());
				else if (_comp(_S_key((--before)._node), k)) {
					if (_S_right(before._node) == 0)
						return res(0, before._node);
					else
						return res(pos._node, pos._node);
				} else
					return _M_get_insert_unique_pos(k);
			} else if (_comp(_S_key(pos._node), k)) {
				iterator after = pos;
				if (pos._node == _M_rightmost())
					return res(0, _M_rightmost());
				else if (_comp(k, _S_key((++after)._node))) {
					if (_S_right(pos._node) == 0)
						return res(0, pos._node);
					else
						return res(after._node, after._node);
				} else
					return _M_get_insert_unique_pos(k);
			} else
				return res(pos._node, 0);
		}

		ft::pair<_base_ptr, _base_ptr> _M_get_insert_unique_pos(const key_type &k) {
			typedef pair<_base_ptr, _base_ptr> _Res;
			_link_type x = _M_begin();
			_base_ptr y = _M_end();
			bool comp = true;
			while (x != 0) {
				y = x;
				comp = _comp(k, _S_key(x));
				x = comp ? _S_left(x) : _S_right(x);
			}
			iterator j = iterator(y);
			if (comp) {
				if (j == begin())
					return _Res(x, y);
				else
					--j;
			}
			if (_comp(_S_key(j._node), k))
				return _Res(x, y);
			return _Res(j._node, 0);
		}

	public:
		bool empty() const { return _node_count == 0; }

		size_type size() const { return _node_count; }

		size_type max_size() const { return _node_alloc.max_size(); }

		iterator lower_bound(const key_type &k) {
			return _M_lower_bound(_M_begin(), _M_end(), k);
		}

		const_iterator lower_bound(const key_type &k) const {
			return _M_lower_bound(_M_begin(), _M_end(), k);
		}

		iterator upper_bound(const key_type &k) {
			return _M_upper_bound(_M_begin(), _M_end(), k);
		}

		const_iterator upper_bound(const key_type &k) const {
			return _M_upper_bound(_M_begin(), _M_end(), k);
		}

		key_compare key_comp() const { return _comp; }

		const_iterator begin() const { return (const_iterator(_header.left)); }

		const_iterator end() const { return (const_iterator(&_header)); }

		iterator begin() { return (iterator(_header.left)); }

		iterator end() { return (iterator(&_header)); }

		reverse_iterator rbegin() { return (reverse_iterator(end())); }

		reverse_iterator rend() { return (reverse_iterator(begin())); }

		allocator_type get_allocator() { return _alloc; }

		allocator_type get_allocator() const { return _alloc; }

		Tree &operator=(const Tree &x) {
			clear();
			insert_unique(x.begin(), x.end());
		}

		void clear() {
			_M_erase(_M_begin());
			_M_reset();
		}

		ft::pair<iterator, bool> insert_unique(const Val &v) {
			typedef pair<iterator, bool> res;
			ft::pair<_base_ptr, _base_ptr>
					_res = _M_get_insert_unique_pos(KeyOfValue()(v));
			if (_res.second)
				return res(insert(_res.first, _res.second, v), true);
			return res(iterator(_res.first), false);
		}

		iterator insert_unique(const_iterator position, const Val &v) {
			pair<_base_ptr, _base_ptr>
					res = _M_get_insert_hint_unique_pos(position, KeyOfValue()(v));
			if (res.second)
				return insert(res.first, res.second, v);
			return iterator(res.first);
		}

		template<class II>
		void insert_unique(II first, II last) {
			for (; first != last; ++first)
				insert_unique(end(), *first);
		}

		iterator insert(_base_ptr x, _base_ptr p, const Val &v) {
			bool insert_left = (x != 0 || p == _M_end()
								|| _comp(KeyOfValue()(v), _S_key(p)));
			_link_type z = _node_alloc.allocate(1);
			_node_alloc.construct(z, v);
			insertRebalanceTree(insert_left, z, p, _header);
			++_node_count;
			return iterator(z);
		}

		void insertRebalanceTree(const bool insert_left,
								 RbTreeNodeBase *x,
								 RbTreeNodeBase *p,
								 RbTreeNodeBase &header) throw() {
			RbTreeNodeBase *&_root = header.parent;
			x->parent = p;
			x->left = nullptr;
			x->right = nullptr;
			x->color = RED;
			if (insert_left) {
				p->left = x;
				if (p == &header) {
					header.parent = x;
					header.right = x;
				} else if (p == header.left)
					header.left = x;
			} else {
				p->right = x;
				if (p == header.right)
					header.right = x;
			}
			while (x != _root
				   && x->parent->color == RED) {
				RbTreeNodeBase *const xpp = x->parent->parent;
				if (x->parent == xpp->left) {
					RbTreeNodeBase *const y = xpp->right;
					if (y && y->color == RED) {
						x->parent->color = BLACK;
						y->color = BLACK;
						xpp->color = RED;
						x = xpp;
					} else {
						if (x == x->parent->right) {
							x = x->parent;
							rotate_left(x, _root);
						}
						x->parent->color = BLACK;
						xpp->color = RED;
						rotateRight(xpp, _root);
					}
				} else {
					RbTreeNodeBase *const y = xpp->left;
					if (y && y->color == RED) {
						x->parent->color = BLACK;
						y->color = BLACK;
						xpp->color = RED;
						x = xpp;
					} else {
						if (x == x->parent->left) {
							x = x->parent;
							rotateRight(x, _root);
						}
						x->parent->color = BLACK;
						xpp->color = RED;
						rotate_left(xpp, _root);
					}
				}
			}
			_root->color = BLACK;
		}

		void rotate_left(RbTreeNodeBase *const x, RbTreeNodeBase *&root) {
			RbTreeNodeBase *const y = x->right;
			x->right = y->left;
			if (y->left != nullptr)
				y->left->parent = x;
			y->parent = x->parent;
			if (x == root)
				root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void rotateRight(RbTreeNodeBase *const x,
						 RbTreeNodeBase *&root) {
			RbTreeNodeBase *const y = x->left;
			x->left = y->right;
			if (y->right != nullptr)
				y->right->parent = x;
			y->parent = x->parent;
			if (x == root)
				root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		ft::pair<iterator, iterator> equal_range(const Key &k) {
			_link_type x = _M_begin();
			_base_ptr y = _M_end();
			while (x != 0) {
				if (_comp(_S_key(x), k))
					x = _S_right(x);
				else if (_comp(k, _S_key(x)))
					y = x, x = _S_left(x);
				else {
					_link_type xu(x);
					_base_ptr yu(y);
					y = x, x = _S_left(x);
					xu = _S_right(xu);
					return ft::pair<iterator,
							iterator>(_M_lower_bound(x, y, k),
									  _M_upper_bound(xu, yu, k));
				}
			}
			return ft::pair<iterator, iterator>(iterator(y), iterator(y));
		}

		pair<const_iterator, const_iterator> equal_range(const Key &k) const {
			_const_link_type x = _M_begin();
			_const_base_ptr y = _M_end();
			while (x != 0) {
				if (_comp(_S_key(x), k))
					x = _S_right(x);
				else if (_comp(k, _S_key(x)))
					y = x, x = _S_left(x);
				else {
					_const_link_type xu(x);
					_const_base_ptr yu(y);
					y = x, x = _S_left(x);
					xu = _S_right(xu);
					return ft::pair<const_iterator,
							const_iterator>(_M_lower_bound(x, y, k),
											_M_upper_bound(xu, yu, k));
				}
			}
			return ft::pair<const_iterator, const_iterator>(const_iterator(y),
															const_iterator(y));
		}

		void swap(Tree &t) {
			if (_M_root() == 0) {
				if (t._M_root() != 0)
					this->_M_move_data(t);
			} else if (t._M_root() == 0)
				t._M_move_data(*this);
			else {
				ft::swap(_M_root(), t._M_root());
				ft::swap(_M_leftmost(), t._M_leftmost());
				ft::swap(_M_rightmost(), t._M_rightmost());
				_M_root()->parent = _M_end();
				t._M_root()->parent = t._M_end();
				ft::swap(this->_node_count, t._node_count);
			}
			ft::swap(this->_comp, t._comp);
		}

		size_type erase(const Key &x) {
			ft::pair<iterator, iterator> p = equal_range(x);
			const size_type old_size = size();
			_M_erase_aux(p.first, p.second);
			return old_size - size();
		}

		void erase(iterator first, iterator last) {
			_M_erase_aux(first, last);
		}

		void erase(iterator position) {
			_M_erase_aux(position);
		}

		void erase(const Key *first, const Key *last) {
			while (first != last)
				erase(*first++);
		}

		iterator find(const Key &k) {
			iterator j = _M_lower_bound(_M_begin(), _M_end(), k);
			return (j == end()
					|| _comp(k, _S_key(j._node))) ? end() : j;
		}

		const_iterator find(const Key &k) const {
			const_iterator j = _M_lower_bound(_M_begin(), _M_end(), k);
			return (j == end()
					|| _comp(k, _S_key(j._node))) ? end() : j;
		}

		size_type count(const Key &k) const {
			ft::pair<const_iterator, const_iterator> p = equal_range(k);
			const size_type n = ft::distance(p.first, p.second);
			return n;
		}

		bool operator==(const Tree &y) const {
			return size() == y.size()
				   && ft::equal(begin(), end(), y.begin());
		}

		bool operator<(const Tree &y) const {
			return ft::lexicographical_compare(begin(), end(),
											   y.begin(), y.end());
		}

		bool operator!=(const Tree &y) const { return !(*this == y); }

		bool operator>(const Tree &y) const { return y < *this; }

		bool operator<=(const Tree &y) const { return !(y < *this); }

		bool operator>=(const Tree &y) const { return !(*this < y); }
	}; // END CLASS TREE
}

#endif //FT_CONTAINERS_TREE_HPP
