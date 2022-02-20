#ifndef FT_CONTAINERS_PAIR_HPP
#define FT_CONTAINERS_PAIR_HPP

namespace ft {
	// TEMPLATE CLASS PARE
	// Used to represent a pair of objects as a single object
	// or if you need to place a pair of values in a container
	template<class T, class U>
	struct pair {
		typedef T first_type;
		typedef U second_type;
		first_type first;
		second_type second;

		pair() : first(), second() {}

		pair(const T &a, const U &b) : first(a), second(b) {}

		template<class U1, class U2>
		pair(const pair<U1, U2> &x): first(x.first), second(x.second) {}

		pair &operator=(const pair &pr) {
			this->first = pr.first;
			this->second = pr.second;
			return *this;
		}

		template<class V, class W>
		pair &operator=(const pair<V, W> &pr) {
			first = pr.first;
			second = pr.second;
			return *this;
		}

		bool operator==(const pair<T, U> &y) const {
			return this->first == y.first && this->second == y.second;
		}

		bool operator<(const pair<T, U> &y) const {
			return this->first < y.first
				   || !(y.first < this->first && this->second < y.second);
		}

		bool operator!=(const pair<T, U> &y) const { return !(this == y); }

		bool operator>(const pair<T, U> &y) const { return y < this; }

		bool operator<=(const pair<T, U> &y) const { return !(y < this); }

		bool operator>=(const pair<T, U> &y) const { return !(this < y); }

	}; // END PAIR TEMPLATE

	// TEMPLATE FUNCTION make_pair
	template<class T1, class T2>
	ft::pair<T1, T2> make_pair(T1 x, T2 y) {
		return pair<T1, T2>(x, y);
	}

	template<class arg, class result>
	struct unary_function {
		typedef arg argument_type;
		typedef result result_type;
	};

	template<typename Arg1, typename Arg2, typename Result>
	struct binary_function {
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	template<class Pair>
	struct Select1st : public unary_function<Pair,
			typename Pair::first_type> {
		typename Pair::first_type &operator()(Pair &x) const { return x.first; }

		const typename Pair::first_type &operator()(const Pair &x) const { return x.first; }
	};

	template<class Pair>
	struct Select2nd : public unary_function<Pair,
			typename Pair::second_type> {
		typename Pair::second_type &operator()(Pair &x) const { return x.second; }

		const typename Pair::second_type &operator()(const Pair &x) const { return x.second; }
	};


} // END NAMESPACE

#endif //FT_CONTAINERS_PAIR_HPP
