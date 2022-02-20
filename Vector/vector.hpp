#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <iostream>
#include "vectorIterator.hpp"
#include "../Iterator/iterator.hpp"

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class vector {
	private:
		T *_array;
		size_t _size;
		size_t _capacity;
		Allocator _alloc;
	public:
		typedef vector<T, Allocator> Myt;
		typedef T value_type;
		typedef Allocator allocatorType;
		typedef size_t size_type;
		typedef std::ptrdiff_t differenceType;
		typedef typename allocatorType::reference reference;
		typedef typename allocatorType::const_reference const_reference;
		typedef typename allocatorType::pointer pointer;
		typedef typename allocatorType::const_pointer constPointer;
		typedef vectorIterator<pointer> iterator;
		typedef vectorIterator<constPointer> constIterator;
		typedef ft::reverseIterator<iterator> reverseIterator;
		typedef ft::reverseIterator<constIterator> constReverseIterator;

	public:
		vector(const allocatorType &alloc = allocatorType()) :
				_array(),
				_size(0),
				_capacity(0),
				_alloc(alloc) {}

		vector(size_type n, const value_type &val = value_type(), const allocatorType &alloc = allocatorType()) {
			_alloc = alloc;
			_size = n;
			_capacity = _size;
			_array = _alloc.allocate(n);
			for (size_t i = 0; i < _size; i++) {
				_alloc.construct(_array + i, val);
			}
		}

		vector(const vector &x) { *this = x; }

		template<class InputIterator>
		vector(InputIterator first,
			   typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
			   const allocatorType &alloc = allocatorType()) : _alloc(alloc) {
			differenceType len = ft::distance(first, last);
			_array = _alloc.allocate(len);
			_size = len;
			_capacity = len;

			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(_array + i, *(first + i));
			}
		}

		~vector() {
			for (size_t i = 0; i < _size; i++)
				_alloc.destroy(_array + i);
			_alloc.deallocate(_array, _capacity);
		}


		vector &operator=(const vector &x);

		const_reference operator[](size_t index) const { return (_array[index]); }

		reference operator[](size_t index) { return (_array[index]); }

		iterator begin() { return (iterator(_array)); }

		iterator end() { return (iterator(_array + _size)); }

		constIterator begin() const { return (constIterator(_array)); }

		constIterator end() const { return (constIterator(_array + _size)); }

		reverseIterator rbegin() { return (reverseIterator(this->end())); }

		reverseIterator rend() { return (reverseIterator(this->begin())); }

		constReverseIterator rbegin() const { return (constReverseIterator(end())); }

		constReverseIterator rend() const { return (constReverseIterator(begin())); }

		size_t size() const { return (this->_size); }

		size_t capacity() { return (this->_capacity); }

		size_type max_size() { return (_alloc.max_size()); }

		allocatorType get_allocator() { return (Allocator()); }

		bool empty() const { return (!_size); }

		iterator insert(iterator pos, const T &value);

		void insert(iterator pos, size_type count, const T &value);

		template<class InputIt>
		void insert(iterator pos, InputIt first,
					typename enable_if<!is_integral<InputIt>::value,
							InputIt>::type last);

		void swap(vector &src);

		void push_back(const T &value);

		void pop_back();

		void clear();

		void reserve(size_type new_cap);

		void resize(size_type count, T value = value_type());

		void assign(size_type count, const T &value);

		template<class InputIt>
		void assign(InputIt first,
					typename enable_if<!is_integral<InputIt>::value,
							InputIt>::type last);

		iterator erase(iterator pos);

		iterator erase(iterator first, iterator last);

		reference at(size_t index);

		const_reference at(size_t index) const;

		reference front() { return _array[0]; }

		const_reference front() const { return _array[0]; }

		reference back() { return _array[_size - 1]; }

		const_reference back() const { return _array[_size - 1]; }

	private:
		void reAlloc(size_t newCapacity);

		class OutOfBoundsException : public std::exception {
			virtual const char *what() const throw() { return ("Out of bounds"); }
		};

		class MaxSizeException : public std::exception {
			virtual const char *what() const throw() { return ("Maximum size exceeded"); }
		};

	};


	template<class T, class Allocator>
	ft::vector<T, Allocator> &ft::vector<T, Allocator>::operator=(const vector &x) {
		if (this != &x) {
			this->_alloc = x._alloc;
			this->_size = x._size;
			this->_capacity = x._capacity;
			this->_array = this->_alloc.allocate(_capacity);
			for (size_t i = 0; i < x._size; i++) {
				_alloc.construct(this->_array + i, *(x._array + i));
			}
		}
		return *this;
	}

	template<class T, class Allocator>
	typename ft::vector<T, Allocator>::reference ft::vector<T, Allocator>::at(size_t index) {
		if (index >= _size)
			throw OutOfBoundsException();
		return (_array[index]);
	}

	template<class T, class Allocator>
	typename ft::vector<T, Allocator>::const_reference ft::vector<T, Allocator>::at(size_t index) const {
		if (index >= _size)
			throw OutOfBoundsException();
		return (_array[index]);
	}

	template<class T, class Allocator>
	typename ft::vector<T, Allocator>::iterator ft::vector<T,
			Allocator>::erase(iterator pos) {
		size_type i = ft::distance(begin(), pos);
		_alloc.destroy(&(*pos));
		for (; i < _size - 1; i++)
			_array[i] = _array[i + 1];
		_size--;
		return (pos);
	}

	template<class T, class Allocator>
	typename ft::vector<T, Allocator>::iterator ft::vector<T,
			Allocator>::erase(iterator first, iterator last) {
		size_type start = ft::distance(begin(), first);
		size_type count = ft::distance(first, last);
		for (; first != last; first++)
			_alloc.destroy(&(*first));
		for (; start < _size - count; start++)
			_array[start] = _array[start + count];
		_size -= count;
		return (first);
	}

	template<class T, class Allocator>
	void ft::vector<T, Allocator>::resize(size_type n, value_type val) {
		if (n == this->_size)
			return;
		else if (n > this->_size) {
			while (n > _size) {
				if (n > _capacity)
					reAlloc(n);
				_alloc.construct(this->_array + (_size++), val);
			}
		} else if (n < this->_size) {
			for (size_t i = _size; i > n; i--)
				_alloc.destroy(_array + i);
			_size = n;
		}
	}

	template<class T, class Allocator>
	void ft::vector<T, Allocator>::reserve(size_type new_cap) {
		if (new_cap > max_size())
			throw MaxSizeException();
		else if (new_cap <= _capacity)
			return;
		else
			reAlloc(new_cap);
	}

	template<class T, class Allocator>
	void ft::vector<T, Allocator>::reAlloc(size_t newCapacity) {

		T *newBlock = _alloc.allocate(newCapacity);

		if (newCapacity < _size)
			_size = newCapacity;
		for (size_t i = 0; i < _size; i++)
			newBlock[i] = _array[i];

		_alloc.deallocate(_array, _capacity);
		_array = newBlock;
		_capacity = newCapacity;
	}

	template<class T, class Allocator>
	void ft::vector<T, Allocator>::push_back(const T &value) {
		if (_size >= _capacity)
			reAlloc(_capacity ? _capacity * 2 : 2);
		_alloc.construct(_array + _size++, value);
	}

	template<class T, class Allocator>
	void ft::vector<T, Allocator>::pop_back() {
		_alloc.destroy(_array + _size);
		_size--;
	}

	template<class T, class Allocator>
	void ft::vector<T, Allocator>::clear() {
		for (size_t i = 0; i < _size; i++)
			_alloc.destroy(_array + i);
		_size = 0;
	}

	template<class T, class Allocator>
	void ft::vector<T, Allocator>::assign(size_type count, const T &value) {
		clear();
		insert(begin(), count, value);
	}

	template<class T, class Allocator>
	template<class InputIt>
	void ft::vector<T, Allocator>::assign(InputIt first,
										  typename enable_if<!is_integral<InputIt>::value, InputIt>::type last) {
		clear();
		insert(begin(), first, last);
	}

	template<class T, class Allocator>
	typename ft::vector<T, Allocator>::iterator ft::vector<T, Allocator>::insert(iterator pos, const T &value) {
		size_type n = ft::distance(this->begin(), pos);
		if (_size + 1 > _capacity) {
			T *newBlock;
			newBlock = _alloc.allocate(_capacity ? _capacity * 2 : 2);
			size_type i;
			for (i = 0; i < n; i++)
				_alloc.construct(newBlock + i, *(_array + i));
			_alloc.construct(newBlock + i++, value);
			_size++;
			for (; i < _size; i++) {
				_alloc.construct(newBlock + i, *(_array + i - 1));
				_alloc.destroy(_array + i);
			}
			_alloc.deallocate(_array, _capacity);
			this->_array = newBlock;
			_capacity *= 2;
		} else {
			size_type i;
			for (i = _size; i > n; i--)
				_array[i] = _array[i - 1];
			_size++;
			_alloc.construct(_array + i, value);
		}
		return (iterator(_array + n));

	}

	template<class T, class Allocator>
	void ft::vector<T, Allocator>::insert(iterator pos, size_type count, const T &value) {
		size_type n = ft::distance(this->begin(), pos);
		if (_size + count > _capacity) {
			T *newBlock;
			size_type newCapacity = _capacity ? _capacity * 2 : 2;
			while (_size + count > newCapacity)
				newCapacity *= 2;
			newBlock = _alloc.allocate(newCapacity);
			size_type i;
			for (i = 0; i < n; i++)
				_alloc.construct(newBlock + i, *(_array + i));
			for (int tmp = count; tmp > 0; tmp--, _size++, i++)
				_alloc.construct(newBlock + i, value);
			for (; i < _size; i++) {
				_alloc.construct(newBlock + i, *(_array + i - count));
				_alloc.destroy(_array + i);
			}
			_alloc.deallocate(_array, _capacity);
			this->_array = newBlock;
			_capacity = newCapacity;

		} else {
			size_type i;
			size_type stop = count > n ? count : n;
			for (i = _size + count; i > stop; i--)
				_array[i] = _array[i - count];
			_size += count;
			for (; count > 0; count--, i++)
				_alloc.construct(_array + i, value);

		}
	}

	template<class T, class Allocator>
	template<class InputIt>
	void ft::vector<T, Allocator>::insert(iterator pos, InputIt first,
										  typename enable_if<!is_integral<InputIt>::value, InputIt>::type last) {
		size_type n = ft::distance(this->begin(), pos);
		size_type count = ft::distance(first, last);

		if (_size + count > _capacity) {
			T *newBlock;
			size_type newCapacity = _capacity ? _capacity * 2 : 2;

			while (_size + count > newCapacity)
				newCapacity *= 2;
			newBlock = _alloc.allocate(newCapacity);
			size_type i;
			for (i = 0; i < n; i++)
				_alloc.construct(newBlock + i, *(_array + i));
			for (int tmp = count; tmp > 0; tmp--, _size++, i++, first++)
				_alloc.construct(newBlock + i, *first);
			for (; i < _size; i++) {
				_alloc.construct(newBlock + i, *(_array + i - count));
				_alloc.destroy(_array + i);
			}
			_alloc.deallocate(_array, _capacity);
			this->_array = newBlock;
			_capacity = newCapacity;
		} else {
			size_type i;
			size_type stop = count > n ? count : n;
			for (i = _size + count; i > stop; i--)
				_array[i] = _array[i - count];
			_size += count;

			for (; count > 0; count--, i++, first++)
				_alloc.construct(_array + i, *first);
		}
	}

	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (typename ft::vector<T>::size_type i = 0; i < lhs.size(); i++) {
			if (lhs[i] != rhs[i])
				return (false);
		}
		return true;
	}

	template<class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return !(lhs == rhs);
	}

	template<class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return !(rhs < lhs);
	}

	template<class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return rhs < lhs;
	}

	template<class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return !(lhs < rhs);
	}

	template<class T, class Allocator>
	void ft::vector<T, Allocator>::swap(vector &src) {
		ft::swap(_array, src._array);
		ft::swap(_size, src._size);
		ft::swap(_capacity, src._capacity);
	}

} // END NAMESPACE FT

#endif //FT_CONTAINERS_VECTOR_HPP
