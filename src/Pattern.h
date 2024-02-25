#pragma once

#include "types.h"

struct Pattern {
	View regex;
	View string;
	
	bool match() const;

	std::string str() const;
};
