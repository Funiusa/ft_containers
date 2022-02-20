#ifndef FT_CONTAINERS_REVERSEITERATOR_HPP
#define FT_CONTAINERS_REVERSEITERATOR_HPP

#include "iterator.hpp"

namespace ft {

	template<typename Iterator>
	class reverseIterator
			: public iterator<typename iterator_traits<Iterator>::iterator_category,
					typename iterator_traits<Iterator>::value_type,
					typename iterator_traits<Iterator>::difference_type,
					typename iterator_traits<Iterator>::pointer,
					typename iterator_traits<Iterator>::reference> {
	protected:
		Iterator current;
		typedef iterator_traits <Iterator> traits_type;
	public:
		typedef Iterator iterator_type;
		typedef typename traits_type::difference_type difference_type;
		typedef typename traits_type::pointer pointer;
		typedef typename traits_type::reference reference;

		reverseIterator() : current() {}

		reverseIterator(iterator_type x) : current(x) {}

		reverseIterator(const reverseIterator &x) : current(x.current) {}

		template<typename It>
		reverseIterator(const reverseIterator<It> &x) : current(x.base()) {}

		iterator_type
		base() const { return current; }

		reference
		operator*() const {
			Iterator tmp = current;
			return *--tmp;
		}

		pointer
		operator->() const { return &(operator*()); }

		reverseIterator &
		operator++() {
			--current;
			return *this;
		}

		reverseIterator
		operator++(int) {
			reverseIterator tmp = *this;
			--current;
			return tmp;
		}

		reverseIterator &
		operator--() {
			++current;
			return *this;
		}

		reverseIterator
		operator--(int) {
			reverseIterator tmp = *this;
			++current;
			return tmp;
		}

		reverseIterator
		operator+(difference_type n) const { return reverseIterator(current - n); }

		reverseIterator &
		operator+=(difference_type n) {
			current -= n;
			return *this;
		}

		reverseIterator
		operator-(difference_type n) const { return reverseIterator(current + n); }

		reverseIterator &
		operator-=(difference_type n) {
			current += n;
			return *this;
		}

		reference
		operator[](difference_type n) const { return *(*this + n); }

	}; // END CLASS

	template<typename It>
	bool
	operator==(const reverseIterator<It> &x,
			   const reverseIterator<It> &y) { return x.base() == y.base(); }

	template<typename It>
	bool
	operator!=(const reverseIterator<It> &x,
			   const reverseIterator<It> &y) { return !(x == y); }

	template<typename It>
	bool
	operator<(const reverseIterator<It> &x,
			  const reverseIterator<It> &y) { return y.base() < x.base(); }

	template<typename It>
	bool
	operator>(const reverseIterator<It> &x,
			  const reverseIterator<It> &y) { return y < x; }

	template<typename It>
	bool
	operator<=(const reverseIterator<It> &x,
			   const reverseIterator<It> &y) { return !(y < x); }

	template<typename It>
	bool
	operator>=(const reverseIterator<It> &x,
			   const reverseIterator<It> &y) { return !(x < y); }

	template<class It1, class It2>
	typename reverseIterator<It1>::difference_type
	operator-(const reverseIterator<It1> &x, const reverseIterator<It2> &y) {
		return y.base() - x.base();
	}

	template<class It>
	reverseIterator<It> operator+(typename reverseIterator<It>::difference_type n,
								  const reverseIterator<It> &x) {
		return reverseIterator<It>(x.base() - n);
	}

} // END FT NAMESPACE

#endif //FT_CONTAINERS_REVERSEITERATOR_HPP
