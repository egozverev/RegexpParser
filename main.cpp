#include <algorithm>
#include <cctype>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <unordered_set>

#include "tests.h"
#include "regexp_parser.h"


int main(int argc, char **argv) {
    /*std::string str = "abbaa";
    std::string regexp = "acb..bab.c.*.ab.ba.+.+*a.";
    RegexpParser parser(str, regexp);
    std::cout << parser.GetMaxSubstrLength();*/
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}