#include "Pattern.h"

#include <sstream>

bool Pattern::match() const {
	if (regex == ".*")
		return true;
	if (regex.size() == 1 && string.size() == 1 && ( regex[0] == '.' || regex[0] == string[0] ))
		return true;
	if (regex.size() == 2)
		return std::count(string.begin(), string.end(), regex[0]) == string.size();
	return false;
};

std::string Pattern::str() const {
	std::stringstream ss;
	ss << regex << "\t:'" << string << "'\t" << (match() ? "+" : "-");
	return ss.str();
}
