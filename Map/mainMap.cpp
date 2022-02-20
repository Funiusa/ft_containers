#include <map>
#include <iostream>
#include "map.hpp"
#include <unistd.h>
#include <vector>
#include <ctime>
#include <stdio.h>
#include <string>

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

#define HOW 100000

template<typename T>
std::string to_string(const T &value) {
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template<class T>
void ft_assert(const T &lhs, const T &rhs) {
	if (lhs == rhs)
		std::cout << FGRN("[OK] ");
	else {
		std::cout << FRED("[KO] ");
		std::cout << lhs << " vs " << rhs << std::endl;
	}
}

double time_test_ft() {

	clock_t start, end;
	ft::map<int, int> map;
	start = clock();
	double progress = 0.0;
	std::cout << "FT Insertion...\n";
	for (size_t i = 0; i <= HOW; i++) {
		int barWidth = 70;
		std::cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		progress += (1.0 / (double) HOW);
		std::cout << "] " << int(progress * 100) << " %\r";
		std::cout.flush();
		map.insert(ft::make_pair(i, i));
	}
	std::cout
			<< "\x1b[2K"
			<< "\x1b[1A";
	progress = 0.0;
	std::cout << "FT Deletion...\n";
	for (size_t i = 0; i <= HOW; i++) {
		int barWidth = 70;
		std::cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		progress += (1.0 / (double) HOW);
		std::cout << "] " << int(progress * 100) << " %\r";
		std::cout.flush();
		map.erase(i);
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
	return (time);
}

double time_test_std() {
	clock_t start, end;
	start = clock();
	std::map<int, int> map;
	double progress = 0.0;
	std::cout << "STD Insertion...\n";
	for (size_t i = 0; i <= HOW; i++) {
		int barWidth = 70;
		std::cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		progress += (1.0 / (double) HOW);
		std::cout << "] " << int(progress * 100) << " %\r";
		std::cout.flush();
		map.insert(std::make_pair(i, i));
	}
	std::cout
			<< "\x1b[2K"
			<< "\x1b[1A";
	progress = 0.0;
	std::cout << "STD Deletion...\n";
	for (size_t i = 0; i <= HOW; i++) {
		int barWidth = 70;
		std::cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i) {
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		progress += (1.0 / (double) HOW);
		std::cout << "] " << int(progress * 100) << " %\r";
		std::cout.flush();
		map.erase(i);
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
	return (time);
}

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp {
	bool operator()(const char &lhs, const char &rhs) const { return lhs < rhs; }
};

void map_benchmark() {
	std::cout << "==============================================================================\n";
	std::cout << "|                                                                            |\n";
	std::cout << "|                                MAP TIMETEST                                |\n";
	std::cout << "|                                                                            |\n";
	std::cout << "==============================================================================\n";
	double diff = time_test_ft() / time_test_std();
	std::cout << "FT / STD = " << diff << std::endl;

}

void map_con_check() {
	std::cout << "|================================CONSTRUCTORS================================|" << std::endl;

	bool res = true;
	ft::map<char, int> first_ft;
	first_ft['a'] = 10;
	first_ft['b'] = 30;
	first_ft['c'] = 50;
	first_ft['d'] = 70;
	ft::map<char, int> second_ft(first_ft.begin(), first_ft.end());
	ft::map<char, int> third_ft(second_ft);
	ft::map<char, int, classcomp> fourth_ft;
	bool (*fn_pt)(char, char) = fncomp;
	std::map<char, int, bool (*)(char, char)> fifth(fn_pt);
	ft::map<char, int, bool (*)(char, char)> fifth_ft(fn_pt);
	std::map<int, int> map_std;
	for (size_t i = 1; i < 10; i++) {
		map_std.insert(std::make_pair(i, i));
	}
	std::map<int, int>::iterator it_std = map_std.begin();
	ft::map<int, int> map_ft;
	for (size_t i = 1; i < 10; i++) {
		map_ft.insert(ft::make_pair(i, i));
	}
	ft::map<int, int>::iterator it_ft = map_ft.begin();

	for (; it_ft != map_ft.end(); it_ft++, it_std++) {
		if (it_ft->first != it_std->first ||
			it_ft->second != it_std->second)
			res = false;
	}
	std::cout << (res ? FGRN("[OK] ") : FRED("[KO] ")) << std::endl;


}

void map_begin_check() {
	std::cout << "|===================================BEGIN====================================|" << std::endl;
	ft::map<int, int> map_ft1;
	for (size_t i = 1; i < 9; i++) {
		map_ft1.insert(ft::make_pair(i, i));
	}
	ft::map<char, char> map_ft2;
	for (size_t i = 49; i < 58; i++) {
		map_ft2.insert(ft::make_pair(i, i));
	}
	ft::map<int, char> map_ft3;
	for (size_t i = 49; i < 58; i++) {
		map_ft3.insert(ft::make_pair(i, 64 + i));
	}
	ft::map<double, std::string> map_ft4;
	for (size_t i = 49; i < 58; i++) {
		map_ft4.insert(ft::make_pair(i * 0.5f, "Hello"));
	}
	ft::map<short, bool> map_ft5;
	for (size_t i = 0; i < 9; i++) {
		map_ft5.insert(ft::make_pair(i, false));
	}
	ft::map<char, bool> map_ft6;
	for (size_t i = 49; i < 58; i++) {
		map_ft6.insert(ft::make_pair(i, true));
	}
	ft::map<float, float> map_ft7;
	for (size_t i = 49; i < 58; i++) {
		map_ft7.insert(ft::make_pair(i * 0.3f, i));
	}
	ft::map<std::string, std::string> map_ft8;
	for (size_t i = 49; i < 58; i++) {
		map_ft8.insert(ft::make_pair(to_string(i), to_string(i)));
	}

	std::map<int, int> map_std1;
	for (size_t i = 1; i < 9; i++) {
		map_std1.insert(std::make_pair(i, i));
	}
	std::map<char, char> map_std2;
	for (size_t i = 49; i < 58; i++) {
		map_std2.insert(std::make_pair(i, i));
	}
	std::map<int, char> map_std3;
	for (size_t i = 49; i < 58; i++) {
		map_std3.insert(std::make_pair(i, 64 + i));
	}
	std::map<double, std::string> map_std4;
	for (size_t i = 49; i < 58; i++) {
		map_std4.insert(std::make_pair(i * 0.5f, "Hello"));
	}
	std::map<short, bool> map_std5;
	for (size_t i = 0; i < 9; i++) {
		map_std5.insert(std::make_pair(i, false));
	}
	std::map<char, bool> map_std6;
	for (size_t i = 49; i < 58; i++) {
		map_std6.insert(std::make_pair(i, true));
	}
	std::map<float, float> map_std7;
	for (size_t i = 49; i < 58; i++) {
		map_std7.insert(std::make_pair(i * 0.3f, i));
	}
	std::map<std::string, std::string> map_std8;
	for (size_t i = 49; i < 58; i++) {
		map_std8.insert(std::make_pair(to_string(i), to_string(i)));
	}
	ft_assert((++map_ft1.begin())->first, (++map_std1.begin())->first);
	ft_assert((++map_ft2.begin())->first, (++map_std2.begin())->first);
	ft_assert((++map_ft3.begin())->first, (++map_std3.begin())->first);
	ft_assert((++map_ft4.begin())->first, (++map_std4.begin())->first);
	ft_assert((++map_ft5.begin())->first, (++map_std5.begin())->first);
	ft_assert((++map_ft6.begin())->first, (++map_std6.begin())->first);
	ft_assert((++map_ft7.begin())->first, (++map_std7.begin())->first);
	ft_assert((++map_ft8.begin())->first, (++map_std8.begin())->first);

	std::cout << "\n|===================================END======================================|" << std::endl;

	ft_assert((--map_ft1.end())->first, (--map_std1.end())->first);
	ft_assert((--map_ft2.end())->first, (--map_std2.end())->first);
	ft_assert((--map_ft3.end())->first, (--map_std3.end())->first);
	ft_assert((--map_ft4.end())->first, (--map_std4.end())->first);
	ft_assert((--map_ft5.end())->first, (--map_std5.end())->first);
	ft_assert((--map_ft6.end())->first, (--map_std6.end())->first);
	ft_assert((--map_ft7.end())->first, (--map_std7.end())->first);
	ft_assert((--map_ft8.end())->first, (--map_std8.end())->first);


	std::map<char, int> mymap;
	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;
	ft::map<char, int> mymap_ft;
	mymap_ft['b'] = 100;
	mymap_ft['a'] = 200;
	mymap_ft['c'] = 300;
	ft::map<char, int>::iterator it_ft = mymap_ft.begin();
	std::map<char, int>::iterator it = mymap.begin();
	for (; it != mymap.end(); ++it, ++it_ft) {
		if (it->first == it_ft->first && it->second == it_ft->second)
			std::cout << FGRN("[OK] ");
		else
			std::cout << FRED("[KO] ");
	}
	std::cout << "\n|===================================REND=====================================|" << std::endl;
	ft_assert((--map_ft1.rend())->first, (--map_std1.rend())->first);
	ft_assert((--map_ft2.rend())->first, (--map_std2.rend())->first);
	ft_assert((--map_ft3.rend())->first, (--map_std3.rend())->first);
	ft_assert((--map_ft4.rend())->first, (--map_std4.rend())->first);
	ft_assert((--map_ft5.rend())->first, (--map_std5.rend())->first);
	ft_assert((--map_ft6.rend())->first, (--map_std6.rend())->first);
	ft_assert((--map_ft7.rend())->first, (--map_std7.rend())->first);
	ft_assert((--map_ft8.rend())->first, (--map_std8.rend())->first);

	std::cout << "\n|===================================RBEGIN===================================|" << std::endl;

	ft_assert((++map_ft1.begin())->first, (++map_std1.begin())->first);
	ft_assert((++map_ft2.begin())->first, (++map_std2.begin())->first);
	ft_assert((++map_ft3.begin())->first, (++map_std3.begin())->first);
	ft_assert((++map_ft4.begin())->first, (++map_std4.begin())->first);
	ft_assert((++map_ft5.begin())->first, (++map_std5.begin())->first);
	ft_assert((++map_ft6.begin())->first, (++map_std6.begin())->first);
	ft_assert((++map_ft7.begin())->first, (++map_std7.begin())->first);
	ft_assert((++map_ft8.begin())->first, (++map_std8.begin())->first);

}

void map_empty_check() {
	std::cout << "\n|===================================EMPTY====================================|" << std::endl;

	std::map<int, int> map_std;
	for (size_t i = 0; i < 20; i++) {
		map_std.insert(std::make_pair(i, i));
	}
	std::map<int, int> map_std2;
	ft::map<int, int> map_ft;
	for (size_t i = 0; i < 20; i++) {
		map_ft.insert(ft::make_pair(i, i));
	}

	ft::map<int, int> map_ft2;
	ft_assert(map_std.empty(), map_ft.empty());
	ft_assert(map_std2.empty(), map_ft2.empty());

}

void map_size_check() {
	std::cout << "\n|===================================SIZE=====================================|" << std::endl;

	std::map<int, int> map_std;
	for (size_t i = 0; i < 20; i++) {
		map_std.insert(std::make_pair(i, i));
	}
	std::map<int, int> map_std2;
	ft::map<int, int> map_ft;
	for (size_t i = 0; i < 20; i++) {
		map_ft.insert(ft::make_pair(i, i));
	}

	ft::map<int, int> map_ft2;
	ft_assert(map_std.size(), map_ft.size());
	map_std.erase(1);
	map_ft.erase(1);
	map_std.erase(1000);
	map_ft.erase(1000);
	ft_assert(map_std.size(), map_ft.size());
	ft_assert(map_std2.size(), map_ft2.size());
}

void map_maxsize_check() {
	std::cout << "\n|=================================MAX_SIZE===================================|" << std::endl;

	std::map<int, int> map_std;
	ft::map<int, int> map_ft;
	std::map<double, double> map_std2;
	ft::map<double, double> map_ft2;
	ft_assert(map_std.max_size(), map_ft.max_size());
	ft_assert(map_std2.max_size(), map_ft2.max_size());
}

void map_skobo4ki_check() {
	std::cout << "\n|====================================[]======================================|" << std::endl;

	std::map<int, int> map_std;
	ft::map<int, int> map_ft;
	for (size_t i = 0; i < 20; i++) {
		map_std.insert(std::make_pair(i, i));
		map_ft.insert(ft::make_pair(i, i));
	}
	// std::cout << "STD " << map_std.size() << " FT " << map_ft.size() << std::endl << std::endl;
	ft_assert(map_std[40], map_ft[40]);
	// std::cout << "STD " << map_std.size() << " FT " << map_ft.size() << std::endl << std::endl;
	ft_assert(map_std[4], map_ft[4]);
	// std::cout << "STD " << map_std.size() << " FT " << map_ft.size() << std::endl << std::endl;


}

void map_insert_check() {
	std::cout << "\n|==================================INSERT====================================|" << std::endl;
	std::map<int, int> map_std;
	ft::map<int, int> map_ft;
	for (size_t i = 0; i <= 10; i++) {
		map_std.insert(std::make_pair(i, i));
		map_ft.insert(ft::make_pair(i, i));
	}
	ft::map<int, int>::iterator it_ft = map_ft.begin();
	std::map<int, int>::iterator it_std = map_std.begin();

	for (; it_ft != map_ft.end(); it_ft++, it_std++) {
		ft_assert(it_ft->first, it_std->first);
	}
	std::cout << "\n|==================================ERASE=====================================|" << std::endl;

	for (size_t i = 0; i <= 10; i++) {
		map_ft.erase(i);
	}
	for (size_t i = 0; i <= 10; i++) {
		map_std.erase(i);
	}
	it_ft = map_ft.begin();
	it_std = map_std.begin();
	if (it_std == map_std.end()) {
		if (it_ft == map_ft.begin())
			std::cout << FGRN("[OK] ");
		else
			std::cout << FRED("[KO] ");
	}
}

void map_swap_check() {
	std::cout << "\n|==================================SWAP======================================|" << std::endl;
	std::map<char, int> foo, bar;
	foo['x'] = 100;
	foo['y'] = 200;

	bar['a'] = 11;
	bar['b'] = 22;
	bar['c'] = 33;

	foo.swap(bar);
	ft::map<char, int> foo_ft, bar_ft;
	foo_ft['x'] = 100;
	foo_ft['y'] = 200;

	bar_ft['a'] = 11;
	bar_ft['b'] = 22;
	bar_ft['c'] = 33;

	foo_ft.swap(bar_ft);

	ft::map<char, int>::iterator it_ft = foo_ft.begin();
	std::map<char, int>::iterator it_std = foo.begin();
	for (; it_ft != foo_ft.end(); ++it_ft, ++it_std) {
		if (it_ft->first == it_std->first && it_ft->second == it_std->second)
			std::cout << FGRN("[OK] ");
		else
			std::cout << FRED("[KO] ");
	}
	it_ft = bar_ft.begin();
	it_std = bar.begin();
	for (; it_ft != bar_ft.end(); ++it_ft, ++it_std) {
		if (it_ft->first == it_std->first && it_ft->second == it_std->second)
			std::cout << FGRN("[OK] ");
		else
			std::cout << FRED("[KO] ");
	}
}

void map_clear_check() {
	std::cout << "\n|==================================CLEAR=====================================|" << std::endl;
	std::map<char, int> mymap;
	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	ft::map<char, int> mymap_ft;
	mymap_ft['x'] = 100;
	mymap_ft['y'] = 200;
	mymap_ft['z'] = 300;
	mymap.clear();
	mymap_ft.clear();
	ft::map<char, int>::iterator it_ft = mymap_ft.begin();
	std::map<char, int>::iterator it_std = mymap.begin();
	for (; it_ft != mymap_ft.end(); ++it_ft, ++it_std) {
		if (it_ft->first == it_std->first && it_ft->second == it_std->second)
			std::cout << FGRN("[OK] ");
		else
			std::cout << FRED("[KO] ");
	}
	if (it_std == mymap.end()) {
		if (it_ft == mymap_ft.begin())
			std::cout << FGRN("[OK] ");
		else
			std::cout << FRED("[KO] ");
	}
	mymap['a'] = 1101;
	mymap['b'] = 2202;
	mymap_ft['a'] = 1101;
	mymap_ft['b'] = 2202;
	it_ft = mymap_ft.begin();
	it_std = mymap.begin();
	for (; it_ft != mymap_ft.end(); ++it_ft, ++it_std) {
		if (it_ft->first == it_std->first && it_ft->second == it_std->second)
			std::cout << FGRN("[OK] ");
		else
			std::cout << FRED("[KO] ");
	}
}

void map_keycompare_check() {
	std::cout << "\n|=================================KEYCOMP====================================|" << std::endl;

	std::map<char, int> mymap;
	std::map<char, int>::key_compare mycomp = mymap.key_comp();
	mymap['a'] = 100;
	mymap['b'] = 200;
	mymap['c'] = 300;
	ft::map<char, int> mymap_ft;
	ft::map<char, int>::key_compare mycomp_ft = mymap_ft.key_comp();
	mymap_ft['a'] = 100;
	mymap_ft['b'] = 200;
	mymap_ft['c'] = 300;

	char highest = mymap.rbegin()->first;
	char highest_ft = mymap_ft.rbegin()->first;

	std::map<char, int>::iterator it = mymap.begin();
	ft::map<char, int>::iterator it_ft = mymap_ft.begin();
	do {
		ft_assert(mycomp((*it++).first, highest), mycomp_ft((*it_ft++).first, highest_ft));
	} while (it != mymap.end());
}

void map_valuecompare_check() {
	std::cout << "\n|==============================VALUE_COMPARE=================================|" << std::endl;

	std::map<char, int> mymap;
	mymap['x'] = 1001;
	mymap['y'] = 2002;
	mymap['z'] = 3003;
	ft::map<char, int> mymap_ft;
	mymap_ft['x'] = 1001;
	mymap_ft['y'] = 2002;
	mymap_ft['z'] = 3003;
	std::pair<char, int> highest = *mymap.rbegin();
	std::map<char, int>::iterator it = mymap.begin();
	ft::pair<char, int> highest_ft = *mymap_ft.rbegin();
	ft::map<char, int>::iterator it_ft = mymap_ft.begin();
	do {
		ft_assert(mymap.value_comp()(*it++, highest), mymap_ft.value_comp()(*it_ft++, highest_ft));
	} while (it != mymap.end());
}

void map_check_find() {
	std::cout << "\n|==================================FIND======================================|" << std::endl;
	std::map<char, int> mymap;
	std::map<char, int>::iterator it;
	mymap['a'] = 50;
	mymap['b'] = 100;
	mymap['c'] = 150;
	mymap['d'] = 200;
	ft::map<char, int> mymap_ft;
	ft::map<char, int>::iterator it_ft;
	mymap_ft['a'] = 50;
	mymap_ft['b'] = 100;
	mymap_ft['c'] = 150;
	mymap_ft['d'] = 200;
	mymap.erase(mymap.find('b'));
	mymap_ft.erase(mymap_ft.find('b'));
	if (mymap.find('a') != mymap.end() && mymap_ft.find('a') != mymap_ft.end())
		ft_assert(mymap.find('a')->second, mymap_ft.find('a')->second);
	else
		std::cout << FGRN("[OK] ");
	if (mymap.find('b') != mymap.end() && mymap_ft.find('b') != mymap_ft.end())
		ft_assert(mymap.find('b')->second, mymap_ft.find('b')->second);
	else
		std::cout << FGRN("[OK] ");
	if (mymap.find('c') != mymap.end() && mymap_ft.find('c') != mymap_ft.end())
		ft_assert(mymap.find('c')->second, mymap_ft.find('c')->second);
	else
		std::cout << FGRN("[OK] ");
	if (mymap.find('d') != mymap.end() && mymap_ft.find('d') != mymap_ft.end())
		ft_assert(mymap.find('d')->second, mymap_ft.find('d')->second);
	else
		std::cout << FGRN("[OK] ");
}

void map_count_check() {
	std::cout << "\n|=================================COUNT======================================|" << std::endl;

	std::map<char, int> mymap;
	char c;
	mymap['a'] = 101;
	mymap['c'] = 202;
	mymap['f'] = 303;
	ft::map<char, int> mymap_ft;
	mymap_ft['a'] = 101;
	mymap_ft['c'] = 202;
	mymap_ft['f'] = 303;
	for (c = 'a'; c < 'h'; c++) {
		ft_assert(mymap.count(c), mymap_ft.count(c));
	}
}

void map_lowerbound_check() {
	std::cout << "\n|=========================LOWER_BOUND/UPPER_BOUND============================|" << std::endl;

	std::map<char, int> mymap;
	std::map<char, int>::iterator itlow, itup;

	mymap['a'] = 20;
	mymap['b'] = 40;
	mymap['c'] = 60;
	mymap['d'] = 80;
	mymap['e'] = 100;
	mymap['f'] = 100;
	mymap['g'] = 100;
	mymap['y'] = 100;
	mymap['z'] = 100;
	ft::map<char, int> mymap_ft;
	ft::map<char, int>::iterator itlow_ft, itup_ft;

	mymap_ft['a'] = 20;
	mymap_ft['b'] = 40;
	mymap_ft['c'] = 60;
	mymap_ft['d'] = 80;
	mymap_ft['e'] = 100;
	mymap_ft['f'] = 100;
	mymap_ft['g'] = 100;
	mymap_ft['y'] = 100;
	mymap_ft['z'] = 100;
	itlow = mymap.lower_bound('b');
	itup = mymap.upper_bound('d');
	itlow_ft = mymap_ft.lower_bound('b');
	itup_ft = mymap_ft.upper_bound('d');
	mymap.erase(itlow, itup);
	mymap_ft.erase(itlow_ft, itup_ft);
	std::map<char, int>::iterator it = mymap.begin();
	ft::map<char, int>::iterator it_ft = mymap_ft.begin();
	for (; it != mymap.end(); ++it, ++it_ft) {
		if (it_ft->first == it->first && it_ft->second == it->second)
			std::cout << FGRN("[OK] ");
		else
			std::cout << FRED("[KO] ");
	}
}

void map_equalrange_check() {
	std::cout << "\n|===============================EQUAL_RANGE==================================|" << std::endl;
	std::map<char, int> mymap;
	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;
	ft::map<char, int> mymap_ft;
	mymap_ft['a'] = 10;
	mymap_ft['b'] = 20;
	mymap_ft['c'] = 30;
	std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> ret;
	ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> ret_ft;
	ret = mymap.equal_range('b');
	ret_ft = mymap_ft.equal_range('b');
	ft_assert(ret.first->first, ret_ft.first->first);
	ft_assert(ret.second->second, ret_ft.second->second);

}

void map_getallocator_check() {
	std::cout << "\n|==============================GET_ALLOCATOR=================================|" << std::endl;
	int psize;
	std::map<char, int> mymap;
	std::pair<const char, int> *p;
	p = mymap.get_allocator().allocate(5);
	psize = sizeof(std::map<char, int>::value_type) * 5;
	ft::map<char, int> mymap_ft;
	ft::pair<const char, int> *p_ft;
	p_ft = mymap_ft.get_allocator().allocate(5);
	int psize_ft = sizeof(ft::map<char, int>::value_type) * 5;
	ft_assert(psize, psize_ft);
	mymap_ft.get_allocator().deallocate(p_ft, 5);
	mymap.get_allocator().deallocate(p, 5);

}

void map_iterator_check() {
	std::cout << "\n|================================ITERATORS===================================|" << std::endl;
	ft::map<int, char> map_ft;
	std::map<int, char> map_std;

	for (size_t i = 21; i < 30; i++) {
		map_ft.insert(ft::make_pair(i, i));
		map_std.insert(std::make_pair(i, i));
	}
	ft::map<int, char>::iterator it_ft;
	ft::map<int, char>::const_iterator const_it_ft;
	ft::map<int, char>::reverse_iterator rev_it_ft;
	ft::map<int, char>::const_reverse_iterator const_rev_it_ft;

	std::map<int, char>::iterator it_std;
	std::map<int, char>::const_iterator const_it_std;
	std::map<int, char>::reverse_iterator rev_it_std;
	std::map<int, char>::const_reverse_iterator const_rev_it_std;

	it_ft = map_ft.begin();
	it_std = map_std.begin();
	for (; it_ft != map_ft.end(); it_ft++, it_std++) {
		ft_assert(it_ft->first, it_std->first);
		it_ft->second = 'a';
		it_std->second = 'a';
	}
	it_ft--;
	it_std--;
	std::cout << std::endl;
	for (; it_ft != map_ft.begin(); it_ft--, it_std--) {
		ft_assert(it_ft->first, it_std->first);
		it_ft->second = 'a';
		it_std->second = 'a';
	}
	ft_assert(it_ft->first, it_std->first);
	const_it_ft = map_ft.begin();
	const_it_std = map_std.begin();
	std::cout << std::endl;
	for (; const_it_ft != map_ft.end(); const_it_ft++, const_it_std++) {
		ft_assert(const_it_ft->first, const_it_std->first);
	}
	std::cout << std::endl;
	const_it_ft--;
	const_it_std--;
	for (; const_it_ft != map_ft.begin(); const_it_ft--, const_it_std--) {
		ft_assert(const_it_ft->first, const_it_std->first);
		// const_it_ft->second = 'a';
		// const_it_std->second = 'a';
	}
	ft_assert(it_ft->first, it_std->first);
	std::cout << std::endl;
	rev_it_ft = map_ft.rbegin();
	rev_it_std = map_std.rbegin();
	for (; rev_it_ft != map_ft.rend(); rev_it_ft++, rev_it_std++) {
		ft_assert(rev_it_ft->first, rev_it_std->first);
		rev_it_ft->second = 'a';
		rev_it_std->second = 'a';
	}
	std::cout << std::endl;
	rev_it_ft--;
	rev_it_std--;
	for (; rev_it_ft != map_ft.rbegin(); rev_it_ft--, rev_it_std--) {
		ft_assert(rev_it_ft->first, rev_it_std->first);
		rev_it_ft->second = 'a';
		rev_it_std->second = 'a';
	}
	ft_assert(it_ft->first, it_std->first);
	std::cout << std::endl;

	const_rev_it_ft = map_ft.rbegin();
	const_rev_it_std = map_std.rbegin();
	for (; const_rev_it_ft != map_ft.rend(); const_rev_it_ft++, const_rev_it_std++) {
		ft_assert(const_rev_it_ft->first, const_rev_it_std->first);
		// const_rev_it_ft->second = 'a';
		// const_rev_it_std->second = 'a';
	}
	std::cout << std::endl;
	const_rev_it_ft--;
	const_rev_it_std--;
	for (; const_rev_it_ft != map_ft.rbegin(); const_rev_it_ft--, const_rev_it_std--) {
		ft_assert(const_rev_it_ft->first, const_rev_it_std->first);
		// const_rev_it_ft->second = 'a';
		// const_rev_it_std->second = 'a';
	}
	ft_assert(it_ft->first, it_std->first);
	std::cout << std::endl;
	it_ft = map_ft.begin();
	it_std = map_std.begin();
	for (; it_ft != map_ft.end(); it_ft++, it_std++) {
		ft_assert(it_ft->first, it_std->first);
	}
	std::cout << std::endl;
	it_ft--;
	it_std--;
	for (; it_ft != map_ft.begin(); it_ft--, it_std--) {
		ft_assert(it_ft->first, it_std->first);
	}
	ft_assert(it_ft->first, it_std->first);
	std::cout << std::endl;
	rev_it_ft = map_ft.rbegin();
	rev_it_std = map_std.rbegin();
	ft_assert((--rev_it_std.base())->first, (--rev_it_ft.base())->first);
	rev_it_ft = map_ft.rend();
	rev_it_std = map_std.rend();
	ft_assert((rev_it_std.base())->first, (rev_it_ft.base())->first);
	std::cout << std::endl;


}

int main() {

	map_benchmark();
	map_con_check();
	map_begin_check();
	map_empty_check();
	map_size_check();
	map_maxsize_check();
	map_skobo4ki_check();
	map_insert_check();
	map_swap_check();
	map_clear_check();
	map_keycompare_check();
	map_valuecompare_check();
	map_check_find();
	map_count_check();
	map_lowerbound_check();
	map_equalrange_check();
	map_getallocator_check();
	map_iterator_check();
}
