#include "SimpleRegexCollection.h"

SimpleRegexCollection::SimpleRegexCollection(const View& complex_regex_view_)
	: complex_regex_view(complex_regex_view_)
{}

SimpleRegexCollection::const_iterator SimpleRegexCollection::begin() {
	size_t size;
	if (complex_regex_view.size() == 0) size = 0;
	else if (complex_regex_view.size() == 1) size = 1;
	else if (complex_regex_view.size() > 1 && *(complex_regex_view.data() + 1) != '*') size = 1;
	else if (complex_regex_view.size() > 1 && *(complex_regex_view.data() + 1) == '*') size = 2;
	return SimpleRegexCollection::const_iterator(complex_regex_view, View{complex_regex_view.data(), size});
}

SimpleRegexCollection::const_iterator SimpleRegexCollection::end() {
	return SimpleRegexCollection::const_iterator(complex_regex_view, View{complex_regex_view.data() + complex_regex_view.size(), 0 });
}

SimpleRegexCollection::const_iterator::const_iterator(const View& complex_regex_view_, const View& simple_regex_view_) 
	: complex_regex_view(complex_regex_view_), simple_regex_view(simple_regex_view_) {
}

const View& SimpleRegexCollection::const_iterator::operator*() {
	return simple_regex_view;

}

bool SimpleRegexCollection::const_iterator::operator!=(const SimpleRegexCollection::const_iterator& other) const {
	return complex_regex_view != other.complex_regex_view || simple_regex_view != other.simple_regex_view;	
}

SimpleRegexCollection::const_iterator& SimpleRegexCollection::const_iterator::operator++() {
	const char* new_simple_regex_view_start = simple_regex_view.data() + simple_regex_view.size();
	size_t new_simple_regex_view_size;

	const auto complex_regex_view_end = complex_regex_view.data() + complex_regex_view.size();
	const size_t rest_complex_regex_view_size = complex_regex_view_end - new_simple_regex_view_start;

	if (new_simple_regex_view_start == complex_regex_view_end) new_simple_regex_view_size = 0;
	else if (rest_complex_regex_view_size  == 1) new_simple_regex_view_size = 1;
	else if (rest_complex_regex_view_size  > 1 && *(new_simple_regex_view_start + 1) != '*') new_simple_regex_view_size = 1;
	else if (rest_complex_regex_view_size  > 1 && *(new_simple_regex_view_start + 1) == '*') new_simple_regex_view_size = 2;
	
	simple_regex_view = View(new_simple_regex_view_start, new_simple_regex_view_size);
	return *this;
};

