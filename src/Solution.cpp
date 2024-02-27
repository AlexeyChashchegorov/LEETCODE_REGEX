#include "Solution.h"

#include "SimpleRegexCollection.h"
#include "PatternStringInitiator.h"
#include "Pattern.h"
#include "types.h"


Patterns Solution::initializedPatterns(const std::string& r, const std::string& s) {
	Patterns patterns;
	patterns.reserve(r.size());
	
	PatternStringInitiator pattern_string_initiator(View{s.data(), s.size()});
	for (const auto& simple_regex_view : SimpleRegexCollection(View{r.data(), r.size()}))
		patterns.emplace_back(Pattern{simple_regex_view, pattern_string_initiator.next(simple_regex_view)});
	return patterns;
}

bool Solution::isMatch(const std::string& r, const std::string& s) {
	patterns = std::move(initializedPatterns(r,s));
	return isMatch();
}

bool Solution::allPatternsMatched() {
	return std::find_if(patterns.begin(), patterns.end(), [](const auto& pattern) { return !pattern.match();}) == patterns.end();
}

Patterns::reverse_iterator Solution::unmatchedToMove() {
	auto it=std::next(patterns.rbegin(),1);
	for(; it!=patterns.rend(); it++) {
		auto prev_it = std::prev(it, 1);
		bool can_move_to_next = !it->match() && !it->string.empty() && (prev_it->regex.size() != 1 || prev_it->string.empty()); 
		if ( can_move_to_next )
			break;
	}
	return it;
}

Patterns::reverse_iterator Solution::matchedToMove() {
	auto it2 = patterns.rbegin();
	for(; it2!=std::prev(patterns.rend(),1); it2++) {
		auto prev_it = std::prev(it2,1);
		bool can_move_to_next = it2->match() && !it2->string.empty() && (prev_it->regex.size() != 1 || prev_it->string.empty()); 
		bool have_not_unmatched_at_back = 
			std::find_if(it2, patterns.rend(), 
				[](const auto& pattern){ return !pattern.match(); }) == patterns.rend();
		if ( can_move_to_next && have_not_unmatched_at_back )
			break;
	}
	if (it2 == std::prev(patterns.rend(),1)) {
		return patterns.rend();
	}
	return it2;
}

Patterns::reverse_iterator Solution::patternToMoveFrom() {
	auto it = unmatchedToMove();
	return (it != patterns.rend()) ? it : matchedToMove();
}

void Solution::makeSymbolMove(Patterns::reverse_iterator& pattern_to_move_from_it) {
	auto& from_string = pattern_to_move_from_it->string;
	auto& to_string = std::prev(pattern_to_move_from_it)->string;
	to_string = std::string_view(&from_string[0] + from_string.size() - 1, to_string.size() + 1);
	from_string.remove_suffix(1);
}

bool Solution::isMatch() {
	auto pattern_to_move_from_it = patterns.rbegin();
	while (!allPatternsMatched() && (pattern_to_move_from_it = patternToMoveFrom()) != patterns.rend()) {
		makeSymbolMove(pattern_to_move_from_it);
	}
	return allPatternsMatched();
}
