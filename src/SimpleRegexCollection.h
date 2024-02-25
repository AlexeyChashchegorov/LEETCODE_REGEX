#pragma once

#include "types.h"

class SimpleRegexCollection final {
private:
	const View complex_regex_view;
public:
	SimpleRegexCollection() = delete;
	SimpleRegexCollection(const View& complex_regex_view_);

	class const_iterator final {
		private:
			const View& complex_regex_view;
			View simple_regex_view;
		public:
			const_iterator(const View& complex_regex_view_, const View& simple_regex_view);
			const View& operator*();
			const_iterator& operator++();
			bool operator!=(const const_iterator& it) const;
	};
	
	const_iterator begin();
	const_iterator end();
};
