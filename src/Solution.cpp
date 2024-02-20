#include "Solution.h"

#include <vector>
#include <iostream>

bool Solution::isMatch(const std::string& r, const std::string& s) {
	std::vector<std::string_view> simple_regexes;
	simple_regexes.reserve(r.size());

	for (const auto& c : r) {
		if( c == '*' )
			simple_regexes.back() = std::string_view(simple_regexes.back().begin(), 2);
		else
			simple_regexes.emplace_back(std::string_view(&c, 1));
	}
	
	for(const auto& sv : simple_regexes) {
		std::cout << sv << std::endl;
	}	

	return false; // TODO make solution
}
