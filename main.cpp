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
    explicit RegexpParser(std::string &str, std::string& _regexp_rpn) : initial_string(str), regexp_rpn(_regexp_rpn) {
    }

//private:
    void BuildStacks() {
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
                    std::set<std::pair<uint32_t, uint32_t >> merging_set = std::move(substr_stack.top());
                    substr_stack.pop();
                    std::copy(merging_set.begin(), merging_set.end(),
                              std::back_inserter(substr_stack.top()));
                    /* just combined the elements of last two vectors*/
                }
                else if (elem == '.'){
                    std::string merging_string = regular_stack.top();
                    regular_stack.pop();
                    std::vector<std::pair<uint32_t, uint32_t>> result_vector;
                    regular_stack.top() += merging_string;
                    std::set<std::pair<uint32_t, uint32_t >> merging_set = std::move(substr_stack.top());
                    substr_stack.pop();
                    for(auto first_pair: substr_stack.top()){
                        for(auto second_pair: merging_set){
                            if(first_pair.second == second_pair.first){
                                result_vector.emplace_back(first_pair.first, second_pair.second);
                            }
                        }
                    }
                }
                else{ /* elem == * */
                    regular_stack.top() += elem;
                    for(size_t i = 0; i < initial_string.size(); ++i){
                        substr_stack.top().emplace(i,i); /* empty substrings are fine too */
                    }
                    bool is_finished;
                    do{
                        is_finished = true;
                        /*add substring untill it is possible |init_sub| < +inf => it'll be finished */
                        for(auto first_pair: substr_stack.top()){
                            for(auto second_pair: substr_stack.top()){
                                if(first_pair.second - first_pair.first == 0
                                    || second_pair.second - second_pair.first == 0){
                                    /*do not add unnecessary string!*/
                                    continue;
                                }
                                if (first_pair.second = second_pair.first){
                                    substr_stack.top().emplace(first_pair.first, second_pair.second);
                                    is_finished = false;
                                }
                            }
                        }
                    } while(!is_finished);
                }

            }

        }
    }

    /*
     * Transforming reverse polish notation regexp into common one.
     */
    std::stack<std::string> regular_stack;
    /* stack with strings taken from reverse poland notation*/
    std::stack<std::set<std::pair<uint32_t, uint32_t >>> substr_stack;
    /*stack with information about the substrings of the initial string
     * matching current regexps from reg stack. Pairs <a,b> ~ init_str[a,b)*/
    std::string initial_string;
    std::string regexp_rpn;
    const std::unordered_set<char> operands{'.', '*', '+'};
    bool is_incorrect = false;
};


int main() {
    std::string str = "abbcacababaac";
    std::string regexp = "ab+c.aba.∗.bac.+.+∗";
    RegexpParser parser(str, regexp);
    parser.BuildStacks();
    std::cout << parser.regular_stack.top();


}