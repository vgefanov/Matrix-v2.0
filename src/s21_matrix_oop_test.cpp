≥≥#include "s21_matrix_oop.h"

#include <gtest/gtest.h>

TEST(Matrix, get_set) {
    S21Matrix m1;
    m1.SetRowsCols(4, 4);
    ASSERT_EQ(m1.GetRows(), 4);
    ASSERT_EQ(m1.GetCols(), 4);
}

TEST(Matrix, eq_matrix) {
    S21Matrix m1;
    S21Matrix m2(3, 3);
    S21Matrix m3(4, 5);
    bool result_1 = m1.eq_matrix(m2);
    ASSERT_EQ(result_1, true);
    bool result_2 = m1.eq_matrix(m3);
    ASSERT_EQ(result_2, false);
}

void fill_matrix_1(S21Matrix* m) {
    (*m)(0, 0) = 0;
    (*m)(0, 1) = 2;
    (*m)(0, 2) = 4;
    (*m)(1, 0) = 2;
    (*m)(1, 1) = 4;
    (*m)(1, 2) = 6;
    (*m)(2, 0) = 4;
    (*m)(2, 1) = 6;
    (*m)(2, 2) = 8;
}

TEST(Matrix, sum_matrix) {
    S21Matrix m1;
    S21Matrix m2(3, 3);
    S21Matrix m3;
    m1.fill_matrix();
    m2.fill_matrix();
    fill_matrix_1(&m3);
    m1.sum_matrix(m2);
    ASSERT_TRUE(m1.eq_matrix(m3));
}

TEST(Matrix, sub_matrix) {
    S21Matrix m1;
    S21Matrix m2(3, 3);
    S21Matrix m3;
    m1.fill_matrix();
    m2.fill_matrix();
    fill_matrix_1(&m3);
    m3.sub_matrix(m2);
    ASSERT_TRUE(m3.eq_matrix(m1));
}

TEST(Matrix, mul_number) {
    S21Matrix m1;
    S21Matrix m2;
    m1.fill_matrix();
    fill_matrix_1(&m2);
    m1.mul_number(2);
    ASSERT_TRUE(m1.eq_matrix(m2));
}

TEST(Matrix, mul_matrix) {
    S21Matrix m1;
    S21Matrix m2(3, 3);
    S21Matrix m3;
    m1.fill_matrix();
    m2.fill_matrix();
    m1.mul_matrix(m2);
    m3(0, 0) = 5, m3(0, 1) = 8, m3(0, 2) = 11;
    m3(1, 0) = 8, m3(1, 1) = 14, m3(1, 2) = 20;
    m3(2, 0) = 11, m3(2, 1) = 20, m3(2, 2) = 29;
    ASSERT_TRUE(m1.eq_matrix(m3));
}

TEST(Matrix, transpose) {
    S21Matrix m1;
    S21Matrix m2;
    m1.fill_matrix();
    m2.fill_matrix();
    m1.transpose();
    ASSERT_TRUE(m1.eq_matrix(m2));
}

TEST(Matrix, determinant) {
    S21Matrix m1;
    m1.fill_matrix();
    int result = m1.determinant();
    ASSERT_EQ(result, 0);
}

TEST(Matrix, calc_complements) {
    S21Matrix m1;
    S21Matrix m2;
    m1.fill_matrix();
    m1 = m1.calc_complements();
    m2(0, 0) = -1, m2(0, 1) = 2, m2(0, 2) = -1;
    m2(1, 0) = 2, m2(1, 1) = -4, m2(1, 2) = 2;
    m2(2, 0) = -1, m2(2, 1) = 2, m2(2, 2) = -1;
    ASSERT_TRUE(m1.eq_matrix(m2));
}
TEST(Matrix, inverse_matrix) {
    S21Matrix m1;
    m1(0, 0) = 2, m1(0, 1) = 5, m1(0, 2) = 7;
    m1(1, 0) = 6, m1(1, 1) = 3, m1(1, 2) = 4;
    m1(2, 0) = 5, m1(2, 1) = -2, m1(2, 2) = -3;
    m1 = m1.inverse_matrix();
    S21Matrix m2;
    m2(0, 0) = 1, m2(0, 1) = -1, m2(0, 2) = 1;
    m2(1, 0) = -38, m2(1, 1) = 41, m2(1, 2) = -34;
    m2(2, 0) = 27, m2(2, 1) = -29, m2(2, 2) = 24;
    ASSERT_TRUE(m1.eq_matrix(m2));
}

TEST(Matrix, overload) {
    S21Matrix m1, m2, m3;
    m1 = m1 + m2;
    ASSERT_TRUE(m1 == m3);
    m1 += m2;
    ASSERT_TRUE(m1 == m3);
    m1 = m1 - m2;
    ASSERT_TRUE(m1 == m3);
    m1 -= m2;
    ASSERT_TRUE(m1 == m3);
    m1 = m1 * m2;
    ASSERT_TRUE(m1 == m3);
    m1 *= m2;
    ASSERT_TRUE(m1 == m3);
    m1 = m1 * 2;
    ASSERT_TRUE(m1 == m3);
    m1 = 2 * m1;
    ASSERT_TRUE(m1 == m3);
    m1 *= 2;
    ASSERT_TRUE(m1 == m3);
}

// TEST(Matrix, exceptions) {
//     S21Matrix m1(3, 3), m2(2, 4), m3(1, 5);
//     EXPECT_ANY_THROW(S21Matrix m1(-4, -4));
//     EXPECT_ANY_THROW(m1.SetRowsCols(-2, -2));
//     EXPECT_THROW(m1(30, 30) = 4, std::invalid_argument);
//     EXPECT_ANY_THROW(m1.sum_matrix(m2));
//     EXPECT_ANY_THROW(m1.sub_matrix(m2));
//     EXPECT_ANY_THROW(m1.mul_matrix(m2));
//     EXPECT_ANY_THROW(m2.determinant());
//     EXPECT_ANY_THROW(m2.calc_complements());
//     EXPECT_ANY_THROW(m1.inverse_matrix());
// }

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
