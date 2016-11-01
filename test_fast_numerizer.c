#if defined (__cplusplus)
extern "C" {
#endif

#include "fast_numerizer.h"
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
    double expect;
};

std::ostream& operator << (std::ostream &o, const TestCase &test_case) {
    o << "<TestCase(input=\"" << test_case.input << "\", expect=\"" << test_case.expect << "\")>";
    return o;
}

void operator >> (const YAML::Node& node, TestCase& test_case) {
    test_case.input = node[0].as<std::string>();
    test_case.expect = node[1].as<double>();
}

class FastNumerizer : public testing::TestWithParam<TestCase> {};

TEST_P(FastNumerizer, numerize) {
   EXPECT_EQ(GetParam().expect, numerize(GetParam().input.c_str()));
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
