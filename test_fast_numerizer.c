#include "test_fast_numerizer.h"

using ::testing::InitGoogleTest;

TEST(numerizer, simple) {
    EXPECT_EQ(1, 1);
}

TEST(numerizer, doingsomething) {
    EXPECT_EQ(100.0, numerize("one hundred"));
}

int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
