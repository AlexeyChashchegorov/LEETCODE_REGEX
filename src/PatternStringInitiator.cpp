#include "PatternStringInitiator.h"
PatternStringInitiator::PatternStringInitiator(const View& full_string_to_match_view_) 
	: full_string_to_match_view(full_string_to_match_view_), string_to_match_start(full_string_to_match_view.data())
{}


View PatternStringInitiator::next(const View& simple_regex_view) {
	const auto full_string_to_match_end = full_string_to_match_view.data() + full_string_to_match_view.size();
	size_t string_to_match_size;
	if (string_to_match_start >= full_string_to_match_end) {
		string_to_match_size = 0;
	} else {
		string_to_match_size = simple_regex_view.size() == 1 ? 1 : full_string_to_match_end - string_to_match_start;
	}
	View ret(string_to_match_start, string_to_match_size);
	string_to_match_start += string_to_match_size;
	return ret;
};

bool PatternStringInitiator::initializedCompletely() const {
	return string_to_match_start == full_string_to_match_view.data() + full_string_to_match_view.size();
}
