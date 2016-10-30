#if defined (__cplusplus)
extern "C" {
#endif

#include "fast_numerizer.h"

#if defined (__cplusplus)
}
#endif

#include "gtest/gtest.h"

using ::testing::InitGoogleTest;

TEST(numerizer, simple_tests_work) {
    EXPECT_EQ(100.0, numerize("one hundred"));
}
