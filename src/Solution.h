#include <string>

#include "Pattern.h"

class Solution final {
private:
    static Patterns initializedPatterns(const std::string& s, const std::string& P);
    bool isMatch();
    bool allPatternsMatched();

    Patterns patterns;
public:
    bool isMatch(const std::string& s, const std::string& p);
};
