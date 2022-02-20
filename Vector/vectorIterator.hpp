
#ifndef FT_CONTAINERS_VECTORITERATOR_HPP
#define FT_CONTAINERS_VECTORITERATOR_HPP

#include "../Iterator/iterator.hpp"

// TEMPLATE VECTOR ITERATOR Class
template<typename It>
class vectorIterator {
protected:
	It current;
	typedef typename ft::iterator_traits<It> traits_type;
public:
	typedef It iterator_type;
	typedef typename traits_type::iterator_category iterator_category;
	typedef typename traits_type::value_type value_type;
	typedef typename traits_type::difference_type difference_type;
	typedef typename traits_type::reference reference;
	typedef typename traits_type::pointer pointer;

	vectorIterator() : current(It()) {}

	vectorIterator(const It &i) : current(i) {}

	template<typename Iter>
	vectorIterator(const vectorIterator<Iter> &src) : current(src.base()) {}

	reference operator*() const { return *current; }

	pointer operator->() const { return current; }

	vectorIterator &operator++() {
		++current;
		return *this;
	}

	vectorIterator operator++(int) { return vectorIterator(current++); }

	vectorIterator &operator--() {
		--current;
		return *this;
	}

	vectorIterator operator--(int) { return vectorIterator(current--); }

	reference operator[](difference_type n) const { return current[n]; }

	vectorIterator &operator+=(difference_type n) {
		current += n;
		return *this;
	}

	vectorIterator operator+(difference_type n) const {
		return vectorIterator(current + n);
	}

	vectorIterator &operator-=(difference_type n) {
		current -= n;
		return *this;
	}

	vectorIterator operator-(difference_type n) const {
		return vectorIterator(current - n);
	}

	const It &base() const { return current; }

}; // END ITERATOR VECTOR Class

template<typename ItL, typename ItR>
bool operator==(const vectorIterator<ItL> &lhs,
				const vectorIterator<ItR> &rhs) { return lhs.base() == rhs.base(); }

template<typename Itr>
bool operator==(const vectorIterator<Itr> &lhs,
				const vectorIterator<Itr> &rhs) { return lhs.base() == rhs.base(); }

template<typename ItL, typename ItR>
bool operator!=(const vectorIterator<ItL> &lhs,
				const vectorIterator<ItR> &rhs) { return lhs.base() != rhs.base(); }

template<typename Itr>
bool operator!=(const vectorIterator<Itr> &lhs,
				const vectorIterator<Itr> &rhs) { return lhs.base() != rhs.base(); }

template<typename ItL, typename ItR>
bool operator<(const vectorIterator<ItL> &lhs,
			   const vectorIterator<ItR> &rhs) { return lhs.base() < rhs.base(); }

template<typename It>
bool operator<(const vectorIterator<It> &lhs,
			   const vectorIterator<It> &rhs) { return lhs.base() < rhs.base(); }

template<typename ItL, typename ItR>
bool operator>(const vectorIterator<ItL> &lhs,
			   const vectorIterator<ItR> &rhs) { return lhs.base() > rhs.base(); }

template<typename It>
bool operator>(const vectorIterator<It> &lhs,
			   const vectorIterator<It> &rhs) { return lhs.base() > rhs.base(); }

template<typename ItL, typename ItR>
bool
operator<=(const vectorIterator<ItL> &lhs,
		   const vectorIterator<ItR> &rhs) { return lhs.base() <= rhs.base(); }

template<typename It>
bool
operator<=(const vectorIterator<It> &lhs,
		   const vectorIterator<It> &rhs) { return lhs.base() <= rhs.base(); }

template<typename ItL, typename ItR>
bool
operator>=(const vectorIterator<ItL> &lhs,
		   const vectorIterator<ItR> &rhs) { return lhs.base() >= rhs.base(); }

template<typename Itr>
bool
operator>=(const vectorIterator<Itr> &lhs,
		   const vectorIterator<Itr> &rhs) { return lhs.base() >= rhs.base(); }

template<typename ItL, typename ItR>
typename vectorIterator<ItL>::difference_type
operator-(const vectorIterator<ItL> &lhs,
		  const vectorIterator<ItR> &rhs) {
	return lhs.base() - rhs.base();
}

template<typename Itr>
typename vectorIterator<Itr>::difference_type
operator-(const vectorIterator<Itr> &lhs,
		  const vectorIterator<Itr> &rhs) {
	return lhs.base() - rhs.base();
}

template<typename Itr>
vectorIterator<Itr>
operator+(typename vectorIterator<Itr>::difference_type
		  n, const vectorIterator<Itr> &i) {
	return vectorIterator<Itr>(i.base() + n);
}

template<class T>
vectorIterator<T> operator+(typename vectorIterator<T>::difference_type i,
							vectorIterator<T> &tmp) {
	return tmp.base() + i;
}

template<class T>
vectorIterator<T> operator+(vectorIterator<T> &tmp,
							typename vectorIterator<T>::difference_type i) {
	return tmp.base() + i;
}

#endif //FT_CONTAINERS_VECTORITERATOR_HPP
