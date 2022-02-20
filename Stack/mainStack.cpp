#include <iostream>
#include <vector>
#include "../Vector/vector.hpp"
#include <stack>
#include "stack.hpp"

#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST

template<class T>
void      ft_assert(const T& lhs, const T& rhs)
{
	if(lhs == rhs)
		std::cout << FGRN("[OK] ");
	else
	{
		std::cout << FRED("[KO] ");
		std::cout << lhs << " vs " << rhs << std::endl;
	}

}
void stack_constructor_check()
{
	std::cout << "|================================CONSTRUCTORS================================|" << std::endl;

	bool    res = true;
	std::vector<int> myvector (2,200);
	std::stack<int> first;
	std::stack<int, std::vector<int> > third;
	std::stack<int, std::vector<int> > fourth (myvector);
	std::stack<int, std::vector<int> > fif (fourth);

	ft::vector<int> myvector_ft (2,200);
	ft::stack<int> first_ft;
	ft::stack<int,ft::vector<int> > third_ft;
	ft::stack<int,ft::vector<int> > fourth_ft (myvector_ft);
	ft::stack<int,ft::vector<int> > fif_ft (fourth_ft);

	for ( ; first.size(); first.pop(), first_ft.pop())
		if (first.top() != first_ft.top())
			res = false;
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
	for ( ; third.size(); third.pop(), third_ft.pop())
		if (third.top() != third_ft.top())
			res = false;
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
	for ( ; fourth.size(); fourth.pop(), fourth_ft.pop())
		if (fourth.top() != fourth_ft.top())
			res = false;
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
	for ( ; fif.size(); fif.pop(), fif_ft.pop())
		if (fif.top() != fif_ft.top())
			res = false;
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
}

void stack_empty_check()
{
	std::cout << "\n|===============================EMPTY|TOP|POP================================|" << std::endl;

	std::stack<int, std::deque<int> > mystack;
	ft::stack<int, std::deque<int> > mystack_ft;
	bool res = true;
	ft_assert(mystack.empty(), mystack_ft.empty());
	for (int i=1;i<=10;i++)
	{
		mystack.push(i);
		mystack_ft.push(i);
	}
	ft_assert(mystack.empty(), mystack_ft.empty());

	while (!mystack.empty())
	{
		if (mystack.top() != mystack_ft.top())
			res = false;
		mystack.pop();
		mystack_ft.pop();
	}
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));


}

void stack_push_check()
{
	std::cout << "\n|====================================PUSH====================================|" << std::endl;

	std::stack<int, ft::vector<int> > mystack;
	ft::stack<int, ft::vector<int> > mystack_ft;
	bool    res = true;
	for (int i=0; i<5; ++i) {
		mystack.push(i);
		mystack_ft.push(i);
		if (mystack.top() != mystack_ft.top())
			res = false;
	}
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
}
void    stack_operators_check()
{
	std::cout << "\n|=================================OPERATORS==================================|" << std::endl;

	std::stack<int> mystack;
	ft::stack<int> mystack_ft;
	for (int i=0; i<5; ++i)
	{
		mystack.push(i);
		mystack_ft.push(i);
	}
	std::stack<int> mystack_2;
	ft::stack<int> mystack_ft_2;

	for (int i=0; i<7; ++i)
	{
		mystack.push(i);
		mystack_ft.push(i);
	}

	ft_assert((mystack < mystack_2), (mystack_ft < mystack_ft_2));
	ft_assert((mystack <= mystack_2), (mystack_ft <= mystack_ft_2));
	ft_assert((mystack > mystack_2) , (mystack_ft > mystack_ft_2));
	ft_assert((mystack >= mystack_2), (mystack_ft >= mystack_ft_2));
	ft_assert((mystack != mystack_2), (mystack_ft != mystack_ft_2));
	ft_assert((mystack == mystack_2), (mystack_ft == mystack_ft_2));
	std::cout << std::endl;
}
int main()
{
	stack_constructor_check();
	stack_empty_check();
	stack_push_check();
	stack_operators_check();
}
