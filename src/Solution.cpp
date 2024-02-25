#include "Solution.h"

#include <iostream>
#include <sstream>

#include "SimpleRegexCollection.h"
#include "Pattern.h"
#include "types.h"


bool Solution::isMatch(const std::string& r, const std::string& s) {
	std::cout << r << ":" << s << std::endl;

	Patterns patterns;
	patterns.reserve(r.size());
	
	for (const auto& simple_regex_view : SimpleRegexCollection(View{r.data(), r.size()})) {
		patterns.emplace_back(Pattern{simple_regex_view, View()});
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

	for (auto& pattern : patterns) std::cout << pattern.str() << std::endl;
		
	while (std::find_if(patterns.begin(), patterns.end(), [](const auto& pattern) { return !pattern.match();}) != patterns.end()) {
		// !empty && can_move &&  most_+_index 

		auto it=std::next(patterns.rbegin(),1);
		for(; it!=patterns.rend(); it++) {
			auto prev_it = std::prev(it, 1);
			//std::cout << "?(" << it->str() << ") (" << prev_it->str() << ")" << std::endl;
			bool can_move_to_next = !it->match() && !it->string.empty() && (prev_it->regex.size() != 1 || prev_it->string.empty()); 
			bool have_not_unmatched_at_back = 
				std::find_if(std::next(it), patterns.rend(),
					[](const auto& pattern){ return !pattern.match(); }) == patterns.rend();
			if ( can_move_to_next /*&& have_not_unmatched_at_back*/ ) {
				std::cout <<"P1:" << it->str() << "(" << std::distance(it, patterns.rend()) <<")" <<std::endl;
				break;
			}
		}
		if (it == patterns.rend()) {
			// first time not a problem
			auto it2 = patterns.begin();
			for(; it2!=std::prev(patterns.end(),1); it2++) {
				auto next_it = std::next(it2,1);
				bool can_move_to_next = it2->match() && !it2->string.empty() && (next_it->regex.size() != 1 || next_it->string.empty()); 
				bool have_not_unmatched_at_back = 
					std::find_if(patterns.begin(), it2, 
						[](const auto& pattern){ return !pattern.match(); }) == it2;
				if ( can_move_to_next && !have_not_unmatched_at_back ) {
					std::cout <<"P2:" << it2->str() << "(" << std::distance(patterns.begin(), it2) <<")" <<std::endl;
					break;
				}
			}
			if (it2 == std::prev(patterns.end(),1)) {
				std::cout << "not match" << std::endl;
				break;
			}
			it = std::make_reverse_iterator(std::next(it2));
		}
		std::cout <<"Px:" << it->str() << "(" << std::distance(it, patterns.rend()) <<")" <<std::endl;
		auto& from_string = it->string;
		auto& to_string = std::prev(it)->string;
		std::cout <<"--" << std::endl;
		//std::cout << "M-->:" <<  from_string << std::endl;
		//std::cout << "M<--:" <<  to_string << std::endl;
		to_string = std::string_view(&from_string[0] + from_string.size() - 1, to_string.size() + 1);
		from_string.remove_suffix(1);
		
		for (auto& pattern : patterns) std::cout << pattern.str() << std::endl;
	}
	
	return false; // TODO make solution
}
