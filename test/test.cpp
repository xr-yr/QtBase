#include "gtest/gtest.h"
#include "add.h"

TEST(addTest, Negative) {
    EXPECT_EQ(add(1, 2), 3);
    EXPECT_EQ(add(1, -2), -1);
    EXPECT_EQ(add(5, 6), 11);
}

// 创建测试类
class AddFunctionTest : public ::testing::Test {
protected:
    // 在此可以设置任何测试前后的操作
};

// 测试add函数
TEST_F(AddFunctionTest, Positive) {
    EXPECT_EQ(5, add(2, 3));
    EXPECT_EQ(100, add(50, 50));
}

// 测试边界条件
TEST_F(AddFunctionTest, Boundary) {
    EXPECT_EQ(0, add(0, 0));
    EXPECT_EQ(-1, add(-2, 1));
}

// 测试大数
TEST_F(AddFunctionTest, LargeNumbers) {
    EXPECT_EQ(2147483647, add(1073741823, 1073741824));
}
