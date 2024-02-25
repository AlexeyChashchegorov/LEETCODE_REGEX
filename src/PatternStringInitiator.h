#pragma once

#include "types.h"

class PatternStringInitiator final {
private:
	const View full_string_to_match_view;
	const char* string_to_match_start;
public:
	PatternStringInitiator() = delete;
	PatternStringInitiator(const View& full_string_to_match_view_);
	View next(const View& simple_regex_view);
};
