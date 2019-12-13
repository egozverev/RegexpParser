#include "tests.h"

TEST(general_tests, first) {
    std::string str = "abbaa";
    std::string regexp = "acb..bab.c.*.ab.ba.+.+*a.";
    RegexpParser parser(str, regexp);
    EXPECT_EQ(parser.GetMaxSubstrLength(), 4);
}

TEST(general_tests, second) {
    std::string str = "babc";
    std::string regexp = "ab+c.aba.*.bac.+.*+*";
    RegexpParser parser(str, regexp);
    EXPECT_EQ(parser.GetMaxSubstrLength(), 2);
}

TEST(general_tests, third) {
    std::string str = "hoqeirjkabcbbbabaaabbabababcbbababddfdwwerdsfasaaababacasnnb";
    std::string regexp = "ab+*c.ab+*.";
    RegexpParser parser(str, regexp);
    EXPECT_EQ(parser.GetMaxSubstring(), "bbbabaaabbabababcbbabab");
}

TEST(general_tests, fotrh) {
    std::string str = "nonsence";
    std::string regexp = "ab+*c.ab+*.";
    RegexpParser parser(str, regexp);
    EXPECT_EQ(parser.GetCommonRegexp(), "((a+b))*c((a+b))*");
}

TEST(general_tests, fifth) {
    std::string str = "otioirweoirewoirewo";
    std::string regexp = "ab+*c.ab+*.";
    RegexpParser parser(str, regexp);
    std::cout << parser.GetMaxSubstring() << "\n";
    EXPECT_EQ(parser.GetMaxSubstring(), "");
}

TEST(error_tests, first) {
    std::string str = "abaidgaibac";
    std::string regexp = "+ab";
    RegexpParser parser(str, regexp);
    EXPECT_EQ(parser.GetCommonRegexp(), "");
}

TEST(error_tests, second) {
    std::string str = "aidafoasd";
    std::string regexp = "a.b";
    RegexpParser parser(str, regexp);
    EXPECT_EQ(parser.GetMaxSubstring(), "Incorrect input: regexp is wrong");
}

TEST(error_tests, third) {
    std::string str = "ab+*c.ab+*.abc";
    std::string regexp = "a.b";
    RegexpParser parser(str, regexp);
    EXPECT_EQ(parser.GetMaxSubstrLength(), std::numeric_limits<int32_t>::max());
}