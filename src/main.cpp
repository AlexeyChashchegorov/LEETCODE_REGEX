#include "Solution.h"

#include <iostream>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage:./solution <regex_pattern> <string>";
		return 1;
	}
	auto regex_pattern = argv[1];
	auto string = argv[2];
	std::cout << "Starting: regex_pattern=" << regex_pattern << ", string=" << string << std::endl;
	std::cout << (Solution().isMatch(regex_pattern, string) ? "matched" : "not matched") << std::endl;
	return 0;
}
