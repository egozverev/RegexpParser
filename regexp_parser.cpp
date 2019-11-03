#include "regexp_parser.h"

RegexpParser::RegexpParser(const std::string &str, const std::string &_regexp_rpn) : initial_string(str),
                                                                                     regexp_rpn(_regexp_rpn) {
    BuildStacks();
    if (regular_stack.size() != 1) {
        is_incorrect = true;
    }
}

std::string RegexpParser::GetCommonRegexp() const {
    if (is_incorrect) {
        return "";
    }
    return regular_stack.top();
}

std::string RegexpParser::GetMaxSubstring() const {
    if (is_incorrect) {
        return "Incorrect input: regexp is wrong";
    }
    if (substr_stack.top().empty()) {
        return "";
    }
    /*for(auto p: substr_stack.top()){
        std::cout << initial_string.substr(p.first, p.second - p.first) << "\n";
    }*/
    /*
     * Get maximal substr of init str belonging to the Lang(regexp)
     */
    int32_t cur_length = -1;
    std::pair<uint32_t, uint32_t> cur_pair;
    for (auto substr: substr_stack.top()) {
        int32_t first = substr.first;
        int32_t second = substr.second;
        if (second - first > cur_length) {
            cur_length = second - first;
            cur_pair = std::make_pair(first, second);
        }
    }
    return initial_string.substr(cur_pair.first, cur_length);
}

int32_t RegexpParser::GetMaxSubstrLength() const {
    if (is_incorrect) {
        return std::numeric_limits<int32_t>::max();
    }
    return GetMaxSubstring().size();
}

void RegexpParser::BuildStacks() {
    /*
     * regexp_rpn - regular exp. in reverse polish notation.
     * contains only '*'. '+', '.' operands, numbers and letters
     */
    for (char elem: regexp_rpn) {
        if (isalnum(elem)) {
            regular_stack.push(std::string(1, elem));
            substr_stack.push(std::set<std::pair<uint32_t, uint32_t >>{});
            for (size_t i = 0; i < initial_string.size(); ++i) {
                if (initial_string[i] == elem) {
                    substr_stack.top().emplace(i, i + 1);
                }
            }
            /*for(auto p: substr_stack.top()){
                std::cout << initial_string.substr(p.first, p.second - p.first) << "\n";
            }*/
        } else {
            if (operands.find(elem) == operands.end()
                || ((elem == '+' || elem == '.') && regular_stack.size() < 2)
                || (elem == '*' && regular_stack.empty())) {
                /* If operand is incorrect or there are not enough arguments for it. */
                is_incorrect = true;
                return;
            }


            if (elem == '+') {
                std::string merging_string = regular_stack.top();
                regular_stack.pop();
                regular_stack.top() += '+' + merging_string;
                regular_stack.top().insert(0, "(");
                regular_stack.top().push_back(')');
                std::set<std::pair<uint32_t, uint32_t >> merging_set = std::move(substr_stack.top());
                substr_stack.pop();
                substr_stack.top().insert(merging_set.begin(), merging_set.end());
                /* just combined the elements of last two vectors*/
            } else if (elem == '.') {
                std::string merging_string = regular_stack.top();
                regular_stack.pop();
                regular_stack.top() += merging_string;
                std::set<std::pair<uint32_t, uint32_t >> snd_merging_set = std::move(substr_stack.top());
                substr_stack.pop();
                std::set<std::pair<uint32_t, uint32_t >> fst_merging_set = std::move(substr_stack.top());
                substr_stack.pop();
                substr_stack.push(std::set<std::pair<uint32_t, uint32_t >>());
                for (auto first_pair: fst_merging_set) {
                    for (auto second_pair: snd_merging_set) {
                        if (first_pair.second == second_pair.first) {
                            substr_stack.top().emplace(first_pair.first, second_pair.second);
                        }
                    }
                }
                /*for(auto p: substr_stack.top()){
                    std::cout << initial_string.substr(p.first, p.second - p.first) << "\n";
                }*/

            } else { /* elem == * */
                regular_stack.top().insert(0, "(");
                regular_stack.top() += ")*";
                for (size_t i = 0; i < initial_string.size(); ++i) {
                    substr_stack.top().emplace(i, i); /* empty substrings are fine too */
                }

                bool is_finished;
                do {
                    is_finished = true;
                    /*add substring untill it is possible |init_sub| < +inf => it'll be finished */
                    std::set<std::pair<uint32_t, uint32_t >> new_substrings;
                    for (auto first_pair: substr_stack.top()) {
                        for (auto second_pair: substr_stack.top()) {
                            if ((first_pair.second - first_pair.first == 0)
                                || (second_pair.second - second_pair.first == 0)) {
                                /*do not add unnecessary string!*/
                                continue;
                            }
                            if (first_pair.second == second_pair.first) {
                                //std::cout << first_pair.first << " " << first_pair.second << " " <<
                                //second_pair.first << " " << second_pair.second << "\n";
                                std::pair<uint32_t, uint32_t> candidate{first_pair.first, second_pair.second};
                                if (substr_stack.top().find(candidate) == substr_stack.top().end()) {
                                    new_substrings.emplace(first_pair.first, second_pair.second);
                                    is_finished = false;
                                }
                            }
                        }
                    }
                    substr_stack.top().insert(new_substrings.begin(), new_substrings.end());
                    /*for(auto p: new_substrings){
                        std::cout << initial_string.substr(p.first, p.second - p.first) << "\n";
                    }*/
                } while (!is_finished);
            }

        }

    }
}
