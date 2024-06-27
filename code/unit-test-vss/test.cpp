#include "pch.h"
#include <gtest/gtest.h>

class Calculator {
public:
    int Add(int a, int b) {
        return a + b;
    }

    int Subtract(int a, int b) {
        return a - b;
    }

    int Multiply(int a, int b) {
        return a * b;
    }

    int Divide(int a, int b) {
        if (b == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return a / b;
    }
};

TEST(CalculatorTests, Addition) {
    Calculator calc;
    EXPECT_EQ(calc.Add(2, 3), 5);
    EXPECT_EQ(calc.Add(-2, 3), 1);
    EXPECT_EQ(calc.Add(0, 0), 0);
}

TEST(CalculatorTests, Subtraction) {
    Calculator calc;
    EXPECT_EQ(calc.Subtract(5, 3), 2);
    EXPECT_EQ(calc.Subtract(2, 3), -1);
    EXPECT_EQ(calc.Subtract(0, 0), 0);
}

TEST(CalculatorTests, Multiplication) {
    Calculator calc;
    EXPECT_EQ(calc.Multiply(2, 3), 6);
    EXPECT_EQ(calc.Multiply(-2, 3), -6);
    EXPECT_EQ(calc.Multiply(0, 0), 0);
}

TEST(CalculatorTests, Division) {
    Calculator calc;
    EXPECT_EQ(calc.Divide(6, 3), 2);
    EXPECT_EQ(calc.Divide(5, 2), 2);
    EXPECT_THROW(calc.Divide(5, 0), std::invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}