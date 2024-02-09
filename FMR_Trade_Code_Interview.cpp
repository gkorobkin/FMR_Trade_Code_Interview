// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
1. You are give a c-style string. Write a function to determine if the characters are symmetric.  aba  abab  abccba

2. There are two string collections. eg. collection 1: {"str1", "str2", "str3", "str1", "str3", "str5", "str11", ...}, collection2 {"str1", "str2", "str4"}
   each string in collection2 is unique. Take each string in collection 2, print the number of occurrence of this string in collection1. If possible, print the
   number of occurrence in descending order.  Implement this in a function.
str1  2
str2  1
str4  0
*/

#include <iostream>
#include <cstdlib>
#include <cassert>

#include <vector>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <string_view>


using namespace std;

bool is_palindrome(const char* str);

using res_type = std::vector<std::tuple<std::string, size_t>>;

res_type get_occurrence(const std::set<std::string, less<>>& unq,
	const std::vector<std::string>& col);

int main()
{
	assert(is_palindrome("aba"));
	assert(!is_palindrome("abab"));
	assert(is_palindrome("abccba"));

	vector<string> c1{ "str1", "str2", "str3", "str1", "str3", "str5", "str11" };
	set<string, less<>> c2{ "str1", "str2", "str4" };

	auto res{ get_occurrence(c2, c1) };

	for (auto const& [s, c] : res) {
		cout << s << " " << c << endl;
	}

	return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
//	implementations

/// <summary>
/// Function to define symmetric strings, C-style
/// </summary>
/// <param name="str">The string</param>
/// <returns>Returns true if the string is a palindrome</returns>
bool is_palindrome(const char* str)
{
	assert(str && *str);

	for (auto e = str + strlen(str) - 1; str < e; ++str, --e) {
		if (*str != *e) return false;
	}

	return true;
}

/// <summary>
/// Function to calculate the occurrence of every string from from unique collection
/// in the input collection
/// </summary>
/// <param name="unq">Unique collection of sample strings</param>
/// <param name="col">Collection to count # of occurrences</param>
/// <returns>Collection of [str, cnt] tuples sorted by cnt descending</returns>
res_type get_occurrence(const std::set<std::string, less<>>& unq,
	const std::vector<std::string>& col)
{
	std::unordered_map<std::string, size_t> accur;

	for (auto& s : unq) {
		accur.emplace(s, std::count(col.begin(), col.end(), s));
	}

	res_type res;
	res.reserve(unq.size());

	std::transform(accur.begin(), accur.end(), std::back_inserter(res),
		[](auto& el) {
			return std::make_tuple(el.first, el.second);
		});
	std::sort(res.begin(), res.end(),
		[](auto& r1, auto& r2) { return get<1>(r1) > get<1>(r2); });

	return res;
}
