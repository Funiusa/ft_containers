#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include <iostream>
#include "../Vector/vector.hpp"

namespace ft {
	template<class Tp, class Conteiner = ft::vector<Tp> >
	class stack {
	protected:
		Conteiner _conteiner;
	public:
		typedef Conteiner container_type;
		typedef typename Conteiner::value_type value_type;
		typedef typename Conteiner::reference reference;
		typedef typename Conteiner::const_reference const_reference;
		typedef typename Conteiner::size_type size_type;
		// Main functions
		stack(const Conteiner _c = Conteiner()) : _conteiner(_c) {}

		~stack() {}

		bool empty() const { return _conteiner.empty(); }

		size_type size() const { return _conteiner.size(); }

		reference top() { return _conteiner.back(); }

		const_reference top() const { return _conteiner.back(); }

		void push(const value_type &x) { _conteiner.push_back(x); }

		void pop() { _conteiner.pop_back(); }

		friend bool operator==(const stack<Tp, Conteiner> &lhs, const stack<Tp, Conteiner> &rhs) {
			return lhs._conteiner == rhs._conteiner;
		}

		friend bool operator<(const stack<Tp, Conteiner> &lhs, const stack<Tp, Conteiner> &rhs) {
			return lhs._conteiner < rhs._conteiner;
		}
	};

	template<typename T, typename C>
	bool operator<(const stack<T, C> &lhs, const stack<T, C> &rhs) {
		return lhs._conteiner < rhs._conteiner;
	}

	template<typename T, typename C>
	bool operator!=(const stack<T, C> &lhs, const stack<T, C> &rhs) {
		return !(lhs == rhs);
	}

	template<typename T, typename C>
	bool operator>(const stack<T, C> &lhs, const stack<T, C> &rhs) {
		return (rhs < lhs);
	}

	template<typename T, typename C>
	bool operator<=(const stack<T, C> &lhs, const stack<T, C> &rhs) {
		return !(rhs < lhs);
	}

	template<typename T, typename C>
	bool operator>=(const stack<T, C> &lhs, const stack<T, C> &rhs) {
		return !(lhs < rhs);
	}

	template<typename T, typename C>
	bool operator==(const stack<T, C> &lhs, const stack<T, C> &rhs) {
		return lhs._conteiner == rhs._conteiner;
	}
} // END NAMESPACE FT

#endif //FT_CONTAINERS_STACK_HPP
