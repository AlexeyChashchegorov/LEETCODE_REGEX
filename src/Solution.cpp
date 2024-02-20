#include "Solution.h"

#include <vector>
#include <iostream>

bool Solution::isMatch(const std::string& r, const std::string& s) {
	std::vector<std::string_view> simple_regexes;
	simple_regexes.reserve(r.size());

	std::cout << r << ":" << s << std::endl;
	for (const auto& c : r) {
		if( c == '*' )
			simple_regexes.back() = std::string_view(simple_regexes.back().begin(), 2);
		else
			simple_regexes.emplace_back(std::string_view(&c, 1));
	}

	std::vector<std::string_view> matched_values;
	matched_values.reserve(simple_regexes.size());

	for(const auto& sv : simple_regexes) {
		const char* start = (matched_values.empty()) ? s.data() : matched_values.back().data() + matched_values.back().size();
		if (start >= (s.data() + s.size())) {
			matched_values.emplace_back(start, 0);
			continue;
		}
		matched_values.emplace_back(start, sv.size() == 1 ? 1 : s.data() + s.size() - start);
	}
	
	auto simple_match = [](const std::string_view& r, const std::string_view& s) {
		if (r == ".*" || (r.size() == 1 && s.size() == 1 && ( r[0] == '.' || r[0] == s[0] )))
			return true;
		if (r.size() == 2)
			return std::count(s.begin(), s.end(), r[0]) == s.size();
		return false;
	};
	std::vector<bool> matches(matched_values.size(), false);
	for (size_t i=0;i<matched_values.size();i++) {
		const auto& mv = matched_values[i];
		const auto& sr = simple_regexes[i];
		matches[i] = simple_match(sr, mv);
		std::cout << sr << "\t:'" << mv << "'\t" << (matches[i] ? "+" : "-") << std::endl;
	}	

	return false; // TODO make solution
}
