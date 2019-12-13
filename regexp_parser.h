#pragma once
#include <algorithm>
#include <cctype>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <unordered_set>

class RegexpParser {
public:
    explicit RegexpParser(const std::string &str, const std::string& _regexp_rpn);
    std::string GetCommonRegexp() const;
    std::string GetMaxSubstring() const;
    int32_t GetMaxSubstrLength() const;

private:
    void BuildStacks(); // Transforming reverse polish notation regexp into common one.
    std::stack<std::string> regular_stack; // stack with strings taken from reverse poland notation
    std::stack<std::set<std::pair<uint32_t, uint32_t >>> substr_stack;
    /*stack with information about the substrings of the initial string
     * matching current regexps from reg stack. Pairs <a,b> ~ init_str[a,b)*/
    const std::string initial_string;
    const std::string regexp_rpn;
    const std::unordered_set<char> operands{'.', '*', '+'};
    bool is_incorrect = false;
};