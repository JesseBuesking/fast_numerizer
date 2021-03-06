#if defined (__cplusplus)
extern "C" {
#endif
#include "fast_numerizer.h"
#include "num-fmt.h"
#if defined (__cplusplus)
}
#endif

#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using ::testing::InitGoogleTest;

struct TestCase {
    std::string input;
    std::string expect;
    int precision;
};

std::ostream& operator << (std::ostream &o, const TestCase &test_case) {
    o << "<TestCase(input=\"" << test_case.input << "\", expect=\"" << test_case.expect << "\")>";
    return o;
}

void operator >> (const YAML::Node& node, TestCase& test_case) {
    test_case.input = node[0].as<std::string>();
    test_case.expect = node[1].as<std::string>();
    test_case.precision = node[2].as<int>();
}

class FastNumerizer : public testing::TestWithParam<TestCase> {};

TEST_P(FastNumerizer, numerize) {
    ParserState state;
    initParserState(&state);

    const char* input = GetParam().input.c_str();
    const char* expect = GetParam().expect.c_str();

    initFastNumerizer();
    numerize(input, strlen(input), &state);
    freeFastNumerizer();

    ASSERT_TRUE(strcmp(expect, state.result) == 0) << "expected \"" << expect << "\" given \"" << input << "\", actual \"" << state.result << "\"\n";
}

std::vector<TestCase> ReadTestCasesFromDisk(std::string filename) {
    YAML::Node doc = YAML::LoadFile(filename);

    std::vector<TestCase> input;
    for (unsigned i=0; i < doc.size(); i++) {
        TestCase test_case;
        doc[i] >> test_case;
        input.push_back(test_case);
    }

    return input;
}

INSTANTIATE_TEST_CASE_P(
    Tests,
    FastNumerizer,
    testing::ValuesIn(ReadTestCasesFromDisk("test_basic.yaml")));

TEST(MorphStringTest, HandlesTrailingZeros) {
    sds s = sdsnew("12.000");
    morphNumericString(&s, 3);
    ASSERT_TRUE(strcmp("12", s) == 0) << "12 != " << s << "\n";
}
