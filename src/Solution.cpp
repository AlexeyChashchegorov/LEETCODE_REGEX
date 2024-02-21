#include "Solution.h"

#include <iostream>
#include <sstream>
#include <vector>

using View = std::string_view;
using Views = std::vector<View>;

struct Pattern {
	View regex;
	View string;
	
	bool match() const {
		if (regex == ".*")
			return true;
		if (regex.size() == 1 && string.size() == 1 && ( regex[0] == '.' || regex[0] == string[0] ))
			return true;
		if (regex.size() == 2)
			return std::count(string.begin(), string.end(), regex[0]) == string.size();
		return false;
	};

	std::string str() const {
		std::stringstream ss;
		ss << regex << "\t:'" << string << "'\t" << (match() ? "+" : "-");
		return ss.str();
	}
};

using Patterns = std::vector<Pattern>;

bool Solution::isMatch(const std::string& r, const std::string& s) {
	std::cout << r << ":" << s << std::endl;

	Patterns patterns;
	patterns.reserve(r.size());
	
	for (const auto& c : r) {
		if( c == '*' )
			patterns.back().regex = View(patterns.back().regex.begin(), 2);
		else
			patterns.emplace_back(Pattern{View(&c, 1),View()});

	}
	const char* start = s.data();
	for(auto& pattern : patterns) {
		if (start >= (s.data() + s.size())) {
			pattern.string = View(start, 0);
		} else {
			pattern.string = View(start, pattern.regex.size() == 1 ? 1 : s.data() + s.size() - start);
		}
		start = pattern.string.data() + pattern.string.size();
	}

	for (auto& pattern : patterns) {
		std::cout << pattern.str() << std::endl;
	}
	
	auto is_match = std::all_of(patterns.begin(), patterns.end(), [](const auto& pattern) { return pattern.match();} );
	// !empty && can_move &&  most_+_index 
	
	std::cout << is_match << std::endl;
	return false; // TODO make solution
}
