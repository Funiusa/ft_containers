#include <iostream>
#include <unistd.h>
#include <vector>
#include "vector.hpp"
#include "vectorIterator.hpp"
#include <ctime>
#include <stdio.h>

#define HOW 3000
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
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

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

double    time_test_ft()
{

	clock_t start, end;
	std::vector<int> myvector (100,100);
	start = clock();
	double progress = 0.0;
	std::cout << "FT Insertion...\n";
	for (size_t i = 0; i <= HOW; i++)
	{
		int barWidth = 70;
		std::cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		progress += (1.0 / (double)HOW);
		std::cout << "] " << int(progress * 100) << " %\r";
		std::cout.flush();
		myvector.insert(myvector.begin() + 10, i, i);
	}
	std::cout
			<< "\x1b[2K"
			<< "\x1b[1A";
	progress = 0.0;
	std::cout << "FT Deletion...\n";
	for (size_t i = 0; i <= HOW; i++)
	{
		int barWidth = 70;
		std::cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		progress += (1.0 / (double)HOW);
		std::cout << "] " << int(progress * 100) << " %\r";
		std::cout.flush();
		myvector.erase(myvector.begin());
	}
	std::cout
			<< "\x1b[1A"
			<< "\x1b[2K"
			<< "FT Done"
			<< std::endl;
	end = clock();
	std::cout << std::endl;
	double time = ((double) end - start) / ((double) CLOCKS_PER_SEC);
	printf("FT: The above code block was executed in %.4f second(s)\n", time);
	return (time) ;
}

double    time_test_std()
{
	clock_t start, end;
	start = clock();
	std::vector<int> myvector (100,100);
	double progress = 0.0;
	std::cout << "STD Insertion...\n";
	for (size_t i = 0; i <= HOW; i++)
	{
		int barWidth = 70;
		std::cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		progress += (1.0 / (double)HOW);
		std::cout << "] " << int(progress * 100) << " %\r";
		std::cout.flush();
		myvector.insert(myvector.begin() + 10, i, i);
	}
	std::cout
			<< "\x1b[2K"
			<< "\x1b[1A";
	progress = 0.0;
	std::cout << "STD Deletion...\n";
	for (size_t i = 0; i <= HOW; i++)
	{
		int barWidth = 70;
		std::cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		progress += (1.0 / (double)HOW);
		std::cout << "] " << int(progress * 100) << " %\r";
		std::cout.flush();
		myvector.erase(myvector.begin());
	}
	std::cout
			<< "\x1b[1A"
			<< "\x1b[2K"
			<< "STD Done"
			<< std::endl;
	end = clock();
	std::cout << std::endl;
	double time = ((double) end - start) / ((double) CLOCKS_PER_SEC);
	printf("STD: The above code block was executed in %.4f second(s)\n", time);
	return (time) ;
}

void  vector_benchmark()
{
	std::cout << "==============================================================================\n";
	std::cout << "|                                                                            |\n";
	std::cout << "|                             VECTOR TIMETEST	                               |\n";
	std::cout << "|                                                                            |\n";
	std::cout << "==============================================================================\n";
	double diff = time_test_ft() / time_test_std();
	std::cout << "FT / STD = " << diff << std::endl;
}

void vector_constructor_check()
{
	std::cout << "|================================CONSTRUCTORS================================|" << std::endl;
	bool              res = true;
	int myints[] = {16,2,77,29};

	std::vector<int> first_std;
	std::vector<int> second_std (4,100);
	std::vector<int> third_std (second_std.begin(),second_std.end());
	std::vector<int> fourth_std (third_std);
	std::vector<int> fifth_std (myints, myints + sizeof(myints) / sizeof(int) );
	ft::vector<int> first_ft;
	ft::vector<int> second_ft (4,100);
	ft::vector<int> third_ft (second_ft.begin(),second_ft.end());
	ft::vector<int> fourth_ft (third_ft);
	ft::vector<int> fifth_ft (myints, myints + sizeof(myints) / sizeof(int) );

	ft::vector<int>::iterator it_ft = first_ft.begin();
	std::vector<int>::iterator it_std = first_std.begin();
	for ( ; it_std != first_std.end(); it_ft++, it_std++)
	{
		if ((*it_ft) != (*it_std))
			res = false;
	}
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
	it_ft = second_ft.begin();
	it_std = second_std.begin();
	for ( ; it_std != second_std.end(); it_ft++, it_std++)
	{
		if ((*it_ft) != (*it_std))
			res = false;
	}
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
	it_ft = third_ft.begin();
	it_std = third_std.begin();
	for ( ; it_std != third_std.end(); it_ft++, it_std++)
	{
		if ((*it_ft) != (*it_std))
			res = false;
	}
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
	it_ft = fourth_ft.begin();
	it_std = fourth_std.begin();
	for ( ; it_std != fourth_std.end(); it_ft++, it_std++)
	{
		if ((*it_ft) != (*it_std))
			res = false;
	}
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
	it_ft = fifth_ft.begin();
	it_std = fifth_std.begin();
	for ( ; it_std != fifth_std.end(); it_ft++, it_std++)
	{
		if ((*it_ft) != (*it_std))
			res = false;
	}
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
}

void vector_begin_check()
{
	std::cout << "\n|=================================BEGIN|END==================================|" << std::endl;
	std::vector<int> myvector;
	ft::vector<int> myvector_ft;
	bool  res = true;
	for (int i=1; i<=5; i++)
	{
		myvector.push_back(i);
		myvector_ft.push_back(i);
	}
	ft::vector<int>::iterator it_ft = myvector_ft.begin();
	std::vector<int>::iterator it_std = myvector.begin() ;
	for ( ;it_std != myvector.end(); ++it_ft, ++it_std)
		if ((*it_ft) != (*it_std))
			res = false;
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
}

void vector_rbegin_check()
{
	std::cout << "\n|================================RBEGIN|REND=================================|" << std::endl;
	std::vector<int> myvector (5);
	ft::vector<int> myvector_ft (5);
	bool  res = true;
	int i=0;
	std::vector<int>::reverse_iterator rit = myvector.rbegin();
	ft::vector<int>::reverseIterator rit_ft = myvector_ft.rbegin();
	for (; rit!= myvector.rend(); ++rit, ++rit_ft, ++i)
	{
		*rit_ft = i;
		*rit = i;
	}
	ft::vector<int>::iterator it_ft = myvector_ft.begin();
	std::vector<int>::iterator it_std = myvector.begin() ;
	for ( ;it_std != myvector.end(); ++it_ft, ++it_std)
		if ((*it_ft) != (*it_std))
			res = false;
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));

}
void vector_size_check()
{
	std::cout << "\n|====================================SIZE====================================|" << std::endl;
	std::vector<int> myints;
	ft::vector<int> myints_ft;
	ft_assert(myints.size(), myints_ft.size());
	for (int i=0; i<10; i++)
	{
		myints.push_back(i);
		myints_ft.push_back(i);
	}
	ft_assert(myints.size(), myints_ft.size());
	myints.insert (myints.end(),10,100);
	myints_ft.insert (myints_ft.end(),10,100);
	ft_assert(myints.size(), myints_ft.size());
	myints.pop_back();
	myints_ft.pop_back();
	ft_assert(myints.size(), myints_ft.size());
}

void vector_maxsize_check()
{
	std::cout << "\n|==================================MAX_SIZE==================================|" << std::endl;
	std::vector<int> myvector;
	std::vector<char> myvector2;
	std::vector<long> myvector3;
	std::vector<short> myvector5;
	std::vector<double> myvector6;
	ft::vector<int>  myvector_ft;
	ft::vector<char> myvector2_ft;
	ft::vector<long> myvector3_ft;
	ft::vector<short>   myvector5_ft;
	ft::vector<double>  myvector6_ft;
	ft_assert(myvector.max_size(),  myvector_ft.max_size());
	ft_assert(myvector2.max_size(), myvector2_ft.max_size());
	ft_assert(myvector3.max_size(), myvector3_ft.max_size());
	ft_assert(myvector5.max_size(), myvector5_ft.max_size());
	ft_assert(myvector6.max_size(), myvector6_ft.max_size());

}
void vector_resize_check()
{
	std::cout << "\n|===================================RESIZE===================================|" << std::endl;
	std::vector<int> myvector;
	ft::vector<int> myvector_ft;
	for (int i=1;i<10;i++)
	{
		myvector.push_back(i);
		myvector_ft.push_back(i);
	}
	ft_assert(myvector.size(), myvector_ft.size());
	myvector.resize(5);
	myvector_ft.resize(5);
	ft_assert(myvector.size(), myvector_ft.size());
	myvector_ft.resize(8,100);
	myvector.resize(8,100);
	ft_assert(myvector.size(), myvector_ft.size());
	myvector_ft.resize(12);
	myvector.resize(12);
	ft_assert(myvector.size(), myvector_ft.size());
	myvector_ft.resize(5, 5);
	myvector.resize(5, 5);
	ft_assert(myvector.size(), myvector_ft.size());
	myvector.clear();
	myvector_ft.clear();
	ft_assert(myvector.size(), myvector_ft.size());
	myvector_ft.resize(5, 5);
	myvector.resize(5, 5);
	ft_assert(myvector.size(), myvector_ft.size());
}
void vector_capacity_check()
{
	std::cout << "\n|==================================CAPACITY==================================|" << std::endl;
	std::vector<int> vec_std;
	ft::vector<int> vec_ft;
	ft_assert(vec_std.capacity(), vec_ft.capacity());
	vec_std.resize(10);
	vec_ft.resize(10);
	ft_assert(vec_std.capacity(), vec_ft.capacity());
	vec_std.resize(2);
	vec_ft.resize(2);
	ft_assert(vec_std.capacity(), vec_ft.capacity());
}
void vector_empty_check()
{
	std::cout << "\n|===================================EMPTY====================================|" << std::endl;
	std::vector<int> vec_std;
	ft::vector<int> vec_ft;
	ft_assert(vec_std.empty(), vec_ft.empty());
	vec_std.insert(vec_std.begin(), 4);
	vec_ft.insert(vec_ft.begin(), 4);
	ft_assert(vec_std.empty(), vec_ft.empty());
}
void vector_reserve_check()
{
	std::cout << "\n|==================================RESERVE===================================|" << std::endl;
	std::vector<int> foo;
	ft::vector<int> bar;
	foo.reserve(10);
	bar.reserve(10);
	ft_assert(foo.capacity(), bar.capacity());
	foo.reserve(100);
	bar.reserve(100);
	ft_assert(foo.capacity(), bar.capacity());
	foo.reserve(5);
	bar.reserve(5);
	ft_assert(foo.capacity(), bar.capacity());
	for (int i = 0; i < 10; i++)
	{
		foo.push_back(i);
		bar.push_back(i);
	}
	foo.reserve(200);
	bar.reserve(200);
	ft_assert(foo.capacity(), bar.capacity());
	try
	{
		bar.reserve(bar.max_size() + 1);
		std::cout << FRED("[KO] ");

	}
	catch(const std::exception& e)
	{
		std::cout << FGRN("[OK] ");
	}

}
void vector_skobo4ki_check()
{
	std::cout << "\n|====================================[]======================================|" << std::endl;
	std::vector<int> vec_std(4, 100);
	vec_std[0] = 5;
	vec_std[1] = 6;
	vec_std[2] = 7;
	vec_std[3] = 8;
	ft::vector<int> vec_ft(4, 100);
	vec_ft[0] = 5;
	vec_ft[1] = 6;
	vec_ft[2] = 7;
	vec_ft[3] = 8;
	for (size_t i = 0; i < 4; i++)
	{
		ft_assert(vec_std[i], vec_ft[i]);
	}
}
void vector_at_check()
{
	std::cout << "\n|====================================AT======================================|" << std::endl;
	ft::vector<int> vec_ft(4,100);
	try
	{
		vec_ft.at(3);
		vec_ft.at(4);
		std::cout << FRED("[KO] ");
	}
	catch(const std::exception& e)
	{
		std::cout << FGRN("[OK] ");
	}
}
void vector_front_check()
{
	std::cout << "\n|================================FRONT|BACK==================================|" << std::endl;
	std::vector<int> myvector;
	myvector.push_back(78);
	myvector.push_back(16);
	ft::vector<int> myvector_ft;
	myvector_ft.push_back(78);
	myvector_ft.push_back(16);
	ft_assert(myvector.front(), myvector_ft.front());
	myvector_ft.front() -= 4;
	myvector.front() -= 4;
	ft_assert(myvector.front(), myvector_ft.front());
	ft_assert(myvector.back(), myvector_ft.back());
	myvector_ft.back() -= 4;
	myvector.back() -= 4;
	ft_assert(myvector.back() ,myvector_ft.back());
}

void vector_assign_check()
{
	std::cout << "\n|==================================ASSIGN====================================|" << std::endl;
	bool  res = true;
	std::vector<int> first;
	std::vector<int> second;
	std::vector<int> third;
	first.assign (7,100);
	ft::vector<int> first_ft;
	ft::vector<int> second_ft;
	ft::vector<int> third_ft;
	first_ft.assign (7,100);
	std::vector<int>::iterator it_std;
	ft::vector<int>::iterator it_ft;
	it_std=first.begin()+1;
	it_ft=first_ft.begin()+1;
	second.assign (it_std,first.end()-1);
	second_ft.assign (it_ft,first_ft.end()-1);
	it_std=first.begin();
	it_ft=first_ft.begin();
	for ( ;it_std != first.end(); ++it_ft, ++it_std)
		if ((*it_ft) != (*it_std))
			res = false;
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
	it_std=second.begin();
	it_ft=second_ft.begin();
	for ( ;it_std != second.end(); ++it_ft, ++it_std)
		if ((*it_ft) != (*it_std))
			res = false;
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);
	third_ft.assign (myints,myints+3);
	it_std=third.begin();
	it_ft=third_ft.begin();
	for ( ;it_std != third.end(); ++it_ft, ++it_std)
		if ((*it_ft) != (*it_std))
			res = false;
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
}
void vector_pushback_check()
{
	std::cout << "\n|=============================PUSHBACK|POBACK================================|" << std::endl;
	std::vector<int> vec_std;
	ft::vector<int> vec_ft;
	vec_std.push_back(1477);
	vec_ft.push_back(1477);
	vec_std.push_back(1477);
	vec_ft.push_back(1477);
	if (vec_ft[0] == vec_std[0] && vec_ft.size() == vec_std.size())
		std::cout << FGRN("[OK] ");
	else
		std::cout << FRED("[KO] ");
	vec_std.push_back(477);
	vec_ft.push_back(477);
	if (vec_ft.back() == vec_std.back() && vec_ft.size() == vec_std.size())
		std::cout << FGRN("[OK] ");
	else
		std::cout << FRED("[KO] ");
	vec_std.pop_back();
	vec_ft.pop_back();
	if (vec_ft.back() == vec_std.back() && vec_ft.size() == vec_std.size())
		std::cout << FGRN("[OK] ");
	else
		std::cout << FRED("[KO] ");

}

void vector_swap_check()
{
	std::cout << "\n|===================================SWAP=====================================|" << std::endl;
	bool  res = true;
	std::vector<int> foo (3,100);
	std::vector<int> bar (5,200);
	foo.swap(bar);
	ft::vector<int> foo_ft (3,100);
	ft::vector<int> bar_ft (5,200);
	foo_ft.swap(bar_ft);

	std::vector<int>::iterator it_std = foo.begin();
	ft::vector<int>::iterator it_ft = foo_ft.begin();

	for ( ;it_std != foo.end(); ++it_ft, ++it_std)
		if ((*it_ft) != (*it_std))
			res = false;
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));

	it_std = bar.begin();
	it_ft = bar_ft.begin();
	for ( ;it_std != bar.end(); ++it_ft, ++it_std)
		if ((*it_ft) != (*it_std))
			res = false;
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
}
void vector_clear_check()
{
	std::cout << "\n|==================================CLEAR=====================================|" << std::endl;
	std::vector<int> vec_std(4,100);
	ft::vector<int> vec_ft(4,100);
	vec_std.clear();
	vec_ft.clear();
	if (vec_std.size() == vec_ft.size() && vec_std.capacity() == vec_ft.capacity())
		std::cout << FGRN("[OK] ");
	else
		std::cout << FRED("[KO] ");
}

void vector_iterator_check()
{
	std::cout << "\n|================================ITERATORS===================================|" << std::endl;
	ft::vector<int> u(4, 500);
	u[1] = 400;
	u[2] = 300;
	u[3] = 200;
	std::vector<int> u1(4, 500);
	u1[1] = 400;
	u1[2] = 300;
	u1[3] = 200;
	ft::vector<int>::iterator it_ft = u.begin();
	ft::vector<int>::iterator it_fte = u.end();
	ft::vector<int>::constIterator it_constft = u.begin();
	ft::vector<int>::constIterator it_constfte = u.end();
	ft::vector<int>::constReverseIterator it_constreverseft = u.rbegin();
	ft::vector<int>::constReverseIterator it_constreversefte = u.rend();
	std::vector<int>::iterator it_std = u1.begin();
	std::vector<int>::iterator it_stde = u1.end();
	std::vector<int>::const_iterator it_conststd = u1.begin();
	std::vector<int>::const_iterator it_conststde = u1.end();
	std::vector<int>::const_reverse_iterator it_constreversestd = u1.rbegin();
	std::vector<int>::const_reverse_iterator it_constreversestde = u1.rend();
	ft_assert(*(it_std++), *(it_ft++));
	ft_assert(*(++it_std), *(++it_ft));
	ft_assert(*(--it_std), *(--it_ft));
	ft_assert(*(it_std--), *(it_ft--));
	ft_assert(*(2 + it_std),  *(2 + it_ft));
	ft_assert(*(it_std + 2), *(it_ft + 2));
	ft_assert((it_stde - it_std), (it_fte - it_ft));
	ft_assert((it_stde < it_std), (it_fte < it_ft));
	ft_assert((it_std < it_stde), (it_ft < it_fte));
	ft_assert((it_stde > it_std), (it_fte > it_ft));
	ft_assert((it_std > it_stde), (it_ft > it_fte));
	ft_assert((it_stde >= it_std), (it_fte >= it_ft));
	ft_assert((it_std >= it_stde), (it_ft >= it_fte));
	ft_assert((it_stde <= it_std), (it_fte <= it_ft));
	ft_assert((it_std <= it_stde), (it_ft <= it_fte));
	std::cout << std::endl;
	ft_assert(*(it_stde += 1), *(it_fte += 1));
	ft_assert(*(it_std += 1), *(it_ft += 1));
	ft_assert(*(it_std -= 1), *(it_ft -= 1));
	ft_assert(*(it_std -= 1), *(it_ft -= 1));
	ft_assert(*(it_conststd++), *(it_constft++));
	ft_assert(*(++it_conststd), *(++it_constft));
	ft_assert(*(--it_conststd), *(--it_constft));
	ft_assert(*(it_conststd--), *(it_constft--));
	ft_assert(*(2 + it_conststd),  *(2 + it_constft));
	ft_assert(*(it_conststd + 2), *(it_constft + 2));
	ft_assert((it_conststde - it_conststd), (it_constfte - it_constft));
	ft_assert((it_conststde < it_conststd), (it_constfte < it_constft));
	ft_assert((it_conststd < it_conststde), (it_constft < it_constfte));
	ft_assert((it_conststde > it_conststd), (it_constfte > it_constft));
	ft_assert((it_conststd > it_conststde), (it_constft > it_constfte));
	std::cout << std::endl;
	ft_assert((it_conststde >= it_conststd), (it_constfte >= it_constft));
	ft_assert((it_conststd >= it_conststde), (it_constft >= it_constfte));
	ft_assert((it_conststde <= it_conststd), (it_constfte <= it_constft));
	ft_assert((it_conststd <= it_conststde), (it_constft <= it_constfte));
	ft_assert(*(it_conststde += 1), *(it_constfte += 1));
	ft_assert(*(it_conststd += 1), *(it_constft += 1));
	ft_assert(*(it_conststd -= 1), *(it_constft -= 1));
	ft_assert(*(it_conststd -= 1), *(it_constft -= 1));
	ft_assert(*(it_constreversestd++), *(it_constreverseft++));
	ft_assert(*(++it_constreversestd), *(++it_constreverseft));
	ft_assert(*(--it_constreversestd), *(--it_constreverseft));
	ft_assert(*(it_constreversestd--), *(it_constreverseft--));
	ft_assert(*(2 + it_constreversestd), *(2 + it_constreverseft));
	ft_assert(*(it_constreversestd + 2), *(it_constreverseft + 2));
	ft_assert((it_constreversestde - it_constreversestd), (it_constreversefte - it_constreverseft));
	std::cout << std::endl;
	ft_assert((it_constreversestde - 3 < it_constreversestd + 1), (it_constreversefte - 3 < it_constreverseft + 1));
	ft_assert((it_constreversestd + 1< it_constreversestde - 3), (it_constreverseft +1 < it_constreversefte - 3));
	ft_assert((it_constreversestde - 3> it_constreversestd + 1), (it_constreversefte - 3 > it_constreverseft + 1));
	ft_assert((it_constreversestd +1> it_constreversestde-3), (it_constreverseft+1 > it_constreversefte-3));
	ft_assert((it_constreversestde-3 >= it_constreversestd +1), (it_constreversefte-3 >= it_constreverseft+1));
	ft_assert((it_constreversestd+1 >= it_constreversestde-3), (it_constreverseft+1 >= it_constreversefte-3));
	ft_assert((it_constreversestde-3 <= it_constreversestd+1), (it_constreversefte-3 <= it_constreverseft+1));
	ft_assert((it_constreversestd+1 <= it_constreversestde-3), (it_constreverseft+1 <= it_constreversefte-3));
	ft_assert(*(it_constreversestde += 1), *(it_constreversefte += 1));
	ft_assert(*(it_constreversestd += 1),  *(it_constreverseft += 1));
	ft_assert(*(it_constreversestd -= 1), *(it_constreverseft -= 1));
	ft_assert(*(it_constreversestde -= 1), *(it_constreversefte -= 1));
	ft::vector<int>::constIterator cit_1 = u.begin();
	ft::vector<int>::constIterator cit_2 = u.begin() + 2;
	std::vector<int>::const_iterator cit_std1 = u1.begin();
	std::vector<int>::const_iterator cit_std2 = u1.begin() + 2;
	ft_assert((cit_std2 - cit_std1), (cit_2 - cit_1));
	ft::vector<int>::iterator it_1 = u.begin();
	ft::vector<int>::iterator it_2 = u.begin() + 2;
	std::vector<int>::iterator it_std1 = u1.begin();
	std::vector<int>::iterator it_std2 = u1.begin() + 2;
	ft_assert((it_std2 - it_std1), (it_2 - it_1));
	ft::vector<int>::constReverseIterator rit_1 = u.rbegin();
	ft::vector<int>::constReverseIterator rit_2 = u.rbegin() + 2;
	std::vector<int>::const_reverse_iterator rit_std1 = u1.rbegin();
	std::vector<int>::const_reverse_iterator rit_std2 = u1.rbegin() + 2;
	ft_assert((rit_std2 - rit_std1), (rit_2 - rit_1));

}

void vector_getallocator_check()
{
	std::cout << "\n|==============================GETALLOCATOR==================================|" << std::endl;
	std::vector<int> myvector;
	ft::vector<int> myvector_ft;
	bool res = true;
	int *p;
	int *pft;
	unsigned int i;
	p = myvector.get_allocator().allocate(5);
	pft = myvector_ft.get_allocator().allocate(5);
	for (i=0; i<5; i++) myvector_ft.get_allocator().construct(&p[i],i);
	for (i=0; i<5; i++) myvector.get_allocator().construct(&pft[i],i);
	std::vector<int>::iterator it_std = myvector.begin();
	ft::vector<int>::iterator it_ft = myvector_ft.begin();

	for ( ;it_std != myvector.end(); ++it_ft, ++it_std)
		if ((*it_ft) != (*it_std))
			res = false;
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] "));
	for (i=0; i<5; i++) myvector_ft.get_allocator().destroy(&p[i]);
	for (i=0; i<5; i++) myvector.get_allocator().destroy(&pft[i]);
	myvector_ft.get_allocator().deallocate(p,5);
	myvector.get_allocator().deallocate(pft,5);
}

void vector_operators_check()
{
	std::cout << "\n|==============================|<><=>=!===|==================================|" << std::endl;
	std::vector<int> foo (3,100);
	std::vector<int> bar (2,200);
	ft::vector<int> foo_ft (3,100);
	ft::vector<int> bar_ft (2,200);
	ft_assert((foo==bar), (foo_ft==bar_ft));
	ft_assert((foo!=bar), (foo_ft!=bar_ft));
	ft_assert((foo< bar), (foo_ft< bar_ft));
	ft_assert((foo> bar), (foo_ft> bar_ft));
	ft_assert((foo<=bar), (foo_ft<=bar_ft));
	ft_assert((foo>=bar), (foo_ft>=bar_ft));
	std::cout << std::endl;
}

int main()
{
	vector_benchmark();
	vector_constructor_check();
	vector_begin_check();
	vector_rbegin_check();
	vector_size_check();
	vector_maxsize_check();
	vector_resize_check();
	vector_capacity_check();
	vector_empty_check();
	vector_reserve_check();
	vector_skobo4ki_check();
	vector_at_check();
	vector_front_check();
	vector_assign_check();
	vector_pushback_check();
	vector_swap_check();
	vector_clear_check();
	vector_iterator_check();
	vector_getallocator_check();
	vector_operators_check();
}
