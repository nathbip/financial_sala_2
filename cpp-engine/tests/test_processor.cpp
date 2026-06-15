#include <gtest/gtest.h>
#include "TransactionProcessor.h"

class ProcessorTest : public ::testing::Test {
protected:
    TransactionProcessor p;
};

TEST_F(ProcessorTest, StartsEmpty) {
    auto r = p.GetReport();
    EXPECT_EQ(r.count, 0);
    EXPECT_DOUBLE_EQ(r.total, 0.0);
}

TEST_F(ProcessorTest, ProcessesSingleValidLine) {
    p.ProcessLine("1,150.50");
    auto r = p.GetReport();
    EXPECT_EQ(r.count, 1);
    EXPECT_DOUBLE_EQ(r.total, 150.50);
}

// ==========================================
// TODO_WORKSHOP: IMPLEMENT THE FOLLOWING TESTS
// ==========================================

TEST_F(ProcessorTest, ComputesMinCorrectly) {
    // Description: Process lines with amounts 500.0, 100.0, 300.0.
    // Assert that 'min' is exactly 100.0.
    p.ProcessLine("1,500.0");
    p.ProcessLine("2,100.0");
    p.ProcessLine("3,300.0");
    auto r = p.GetReport();
    EXPECT_EQ(r.count, 3);
    EXPECT_DOUBLE_EQ(r.min, 100.0);
}

TEST_F(ProcessorTest, RejectsNegativeAmountsAndZero) {
    // Description: Process lines with amounts -50.0 and 0.0.
    // Assert that 'count' remains 0 and 'invalid_lines' becomes 2.
    p.ProcessLine("1,-50.0");
    p.ProcessLine("2,0.0");
    auto r = p.GetReport();
    EXPECT_EQ(r.count, 0);
    EXPECT_EQ(r.invalid_lines, 2);
}

TEST_F(ProcessorTest, HandlesMalformedStrings) {
    // Description: Process lines like "1,ABC" or "JUST_A_STRING".
    // Assert that 'invalid_lines' increments correctly without crashing.
    p.ProcessLine("1,ABC");
    p.ProcessLine("2,JUST_A_STRING");
    auto r = p.GetReport();
    EXPECT_EQ(r.invalid_lines, 2);
}

TEST_F(ProcessorTest, FloatingPointPrecisionMath) {
    // Description: Process "1,10.01", "2,10.02", "3,10.03".
    // Use EXPECT_DOUBLE_EQ or EXPECT_NEAR to check that 'total' is 30.06.
    // This teaches why floating point math testing is tricky.
    p.ProcessLine("1,10.01");
    p.ProcessLine("2,10.02");
    p.ProcessLine("3,10.03");
    auto r = p.GetReport();
    EXPECT_DOUBLE_EQ(r.total, 30.06);
}