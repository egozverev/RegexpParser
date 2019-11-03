#include "tests.h"

TEST(general_tests, first){
    std::string str = "abbaa";
    std::string regexp = "acb..bab.c.*.ab.ba.+.+*a.";
    RegexpParser parser(str, regexp);
    EXPECT_EQ(parser.GetMaxSubstrLength(), 4);
}