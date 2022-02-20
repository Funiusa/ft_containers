
#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include "../Iterator/iteratorTraits.hpp"
#include "../Iterator/reverseIterator.hpp"
#include <sstream>
#include <string>

namespace ft {

	template<bool, typename _Tp = void>
	struct enable_if {
	};
	template<typename _Tp>
	struct enable_if<true, _Tp> {
		typedef _Tp type;
	};

	template<typename _Tp, _Tp v>
	struct integral_constant {
		static const _Tp value = v;
		typedef _Tp value_type;
		typedef integral_constant<_Tp, v> type;

		operator value_type() { return value; }
	};

	typedef ft::integral_constant<bool, true> true_type;
	typedef ft::integral_constant<bool, false> false_type;

	template<typename, typename>
	struct are_same {
		enum {
			value = 0
		};
		typedef false_type type;
	};

	template<bool>
	struct truth_type {
		typedef false_type type;
	};

	template<>
	struct truth_type<true> {
		typedef true_type type;
	};

	template<typename>
	struct is_integral_helper : public false_type {
	};

	// INTEGER Functions equivalent Iter_cat for Int_iterator_tag
	template<typename _Tp>
	struct is_integer {
		enum {
			value = 0
		};
		typedef false_type type;
	};

	template<>
	struct is_integer<bool> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<char> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integral_helper<wchar_t> {
		const static bool value = true;
	};
	template<>
	struct is_integer<signed char> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<unsigned char> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<short> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<unsigned short> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<int> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<unsigned int> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<long> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<unsigned long> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<long long> {
		enum {
			value = 1
		};
		typedef true_type type;
	};
	template<>
	struct is_integer<unsigned long long> {
		enum {
			value = 1
		};
		typedef true_type type;
	};

	template<typename _Tp>
	struct remove_const {
		typedef _Tp type;
	};

	template<typename _Tp>
	struct remove_const<_Tp const> {
		typedef _Tp type;
	};

	template<typename _Tp>
	struct remove_volatile {
		typedef _Tp type;
	};

	template<typename _Tp>
	struct remove_volatile<_Tp volatile> {
		typedef _Tp type;
	};

	template<typename _Tp>
	struct remove_cv {
		typedef typename remove_const<typename remove_volatile<_Tp>::type>::type type;
	};

	template<typename>
	struct is_pointer_helper
			: public false_type {
	};

	template<typename _Tp>
	struct is_pointer_helper<_Tp *>
			: public true_type {
	};

	template<typename _Tp>
	struct is_pointer
			: public is_pointer_helper<typename remove_cv<_Tp>::type>::type {
	};

	template<typename _Tp>
	struct is_integral : public integral_constant<bool, (is_integral_helper<typename
	remove_cv<_Tp>::type>::value)> {
	};
	template<>
	struct is_integral<int> : ft::true_type {
	};

	// TEMPLATE FUNCTION Lexicographical Pr algorithm function
	// determines which number is the smallest in diapason [0, k)
	template<class InIt1, class InIt2>
	bool
	lexicographical_compare(InIt1 F1, InIt1 L1, InIt2 F2, InIt2 L2) {
		for (; F1 != L1 && F2 != L2; ++F1, ++F2) {
			if (F2 == L2 || *F2 < *F1)
				return false;
			else if (*F2 > *F1)
				return true;
		}
		return (F1 == L1 && F2 != L2);
	}

	// Algorithm function Equal
	template<bool boolT>
	struct _equal {
		template<typename InIt1, typename InIt2>
		static bool equal(InIt1 first1, InIt1 last1, InIt2 first2) {
			for (; first1 != last1; ++first1, ++first2)
				if (!(*first1 == *first2))
					return false;
			return true;
		}
	};

	template<typename ItIn1, typename ItIn2>
	bool equalAux(ItIn1 first1, ItIn1 last1, ItIn2 first2) {
		typedef typename ft::iterator_traits<ItIn1>::value_type valueType1;
		typedef typename ft::iterator_traits<ItIn2>::value_type valueType2;
		const bool type = ((ft::is_integer<valueType1>::value
							  || ft::is_pointer<valueType1>::value)
							 && ft::is_pointer<ItIn1>::value
							 && ft::is_pointer<ItIn2>::value
							 && ft::are_same<valueType1, valueType2>::value);
		return ft::_equal<type>::equal(first1, last1, first2);
	}

	template<typename InIt1, typename InIt2>
	bool
	equal(InIt1 first1, InIt1 last1, InIt2 first2) {
		return ft::equalAux(first1, last1, first2);
	}
	// TEMPLATE FUNCTION Swap
	template<class T>
	void swap(T &X, T &Y) {
		T tmp = X;
		X = Y, Y = tmp;
	}

}; // END NAMESPACE

#endif //FT_CONTAINERS_ITERATOR_HPP
