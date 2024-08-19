#include "rootfinding.h"
#include <functional>
#include <gtest/gtest.h>
#include <numbers>

const auto constant_function = [](double x) { return 1.0; };
const auto linear_function = [](double x) { return x; };
const auto quadratic_func = [](double x) { return std::pow(x, 2.0) - 1.0; };

TEST(BisectionMethodTests, EndPointErrorMessageTest) {
  const auto result = bisect(constant_function, 1, 0, 1e-3, 1000);
  EXPECT_EQ(kLeftEndPointMustBeLessThanRightEndpoint, result.message);
}

TEST(BisectionMethodTests, InitialFunctionEvaluationErrorMessageTest) {
  const auto result = bisect(constant_function, 0, 1, 1e-3, 1000);
  EXPECT_EQ(kInitialFunctionEvaluationsMustDifferInSign, result.message);
}

TEST(BisectionMethodTests, ConvergenceErrorMessageTest) {
  const auto result = bisect(linear_function, -100, 1, 1e-3, 2);
  EXPECT_EQ(kConvergenceNotAchieved, result.message);
}

TEST(BisectionMethodTests, QuadraticFunctions) {
  EXPECT_EQ(1, bisect(quadratic_func, 0, 2, 1e-6, 1000).root);
  EXPECT_EQ(-1, bisect(quadratic_func, -2, 0, 1e-6, 1000).root);
}

TEST(BisectionMethodTests, CosineFunction) {
  const auto func = [](double x) { return std::cos(x); };
  const auto pi = std::numbers::pi_v<double>;
  const auto tol1 = 1e-3;
  const auto tol2 = 1e-4;
  const auto tol3 = 1e-5;
  EXPECT_NEAR(pi / 2.0, bisect(func, 0, pi, tol1, 1000).root, tol1);
  EXPECT_NEAR(pi / 2.0, bisect(func, 0, pi, tol2, 1000).root, tol2);
  EXPECT_NEAR(pi / 2.0, bisect(func, 0, pi, tol3, 1000).root, tol3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
