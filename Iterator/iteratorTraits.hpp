#ifndef FT_CONTAINERS_ITERATORTRAITS_HPP
#define FT_CONTAINERS_ITERATORTRAITS_HPP

#include <iostream>

namespace ft {

	// TEMPLATE ITERATOR TAG
	struct input_iterator_tag {
	};

	struct output_iterator_tag {
	};

	struct forward_iterator_tag : public input_iterator_tag {
	};

	struct bidirectional_iterator_tag : public forward_iterator_tag {
	};

	struct random_access_iterator_tag : public bidirectional_iterator_tag {
	};

	// ITERATOR BASE
	template<class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T *, class Reference = T &>
	struct iterator {
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	// ITERATOR TRAITS
	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type; // ptrdiff_t
		typedef difference_type distance_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
	};

	template<typename Tr>
	struct iterator_traits<Tr *> {
		typedef ft::random_access_iterator_tag iterator_category;
		typedef Tr value_type;
		typedef std::ptrdiff_t difference_type;
		typedef Tr *pointer;
		typedef Tr &reference;
	};

	template<typename Tr>
	struct iterator_traits<const Tr *> {
		typedef ft::random_access_iterator_tag iterator_category;
		typedef Tr value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const Tr *pointer;
		typedef const Tr &reference;
	};

	// TEMPLATE FUNCTION distance
	// Standard mechanism for determining the difference
	// between two iterators in a range
	template<class It>
	typename ft::iterator_traits<It>::difference_type
	_distance(It first, It last, ft::input_iterator_tag) {
		typename ft::iterator_traits<It>::difference_type result = 0;
		while (first != last) {
			++first;
			++result;
		}
		return result;
	}

	template<class It>
	typename ft::iterator_traits<It>::difference_type
	_distance(It first, It last, ft::random_access_iterator_tag) {
		return last - first;
	}

	template<class It>
	typename ft::iterator_traits<It>::difference_type
	distance(It first, It last) {
		return ft::_distance(first, last,
							 typename ft::iterator_traits<It>::iterator_category());
	}
} // END FT NAMESPACE

#endif //FT_CONTAINERS_ITERATORTRAITS_HPP
