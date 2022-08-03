#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

#define EPS 1e-7

class S21Matrix {
 private:
    int rows_, cols_;
    double** matrix_;
    void matrix_initialization(int rows_, int cols_);
    void matrix_remove();
    S21Matrix matrix_minor(int rows, int cols);

 public:
    int GetRows() const;
    int GetCols() const;
    void SetRowsCols(int rows, int cols);
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();
    bool eq_matrix(const S21Matrix& other) const;
    void sum_matrix(const S21Matrix& other);
    void sub_matrix(const S21Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const S21Matrix& other);
    S21Matrix transpose();
    S21Matrix calc_complements();
    double determinant();
    S21Matrix inverse_matrix();
    S21Matrix operator+(const S21Matrix& other);
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix operator*(const double num);
    S21Matrix operator*(const S21Matrix& other);
    friend S21Matrix operator*(const double num, const S21Matrix& other);
    bool operator==(const S21Matrix& other) const;
    S21Matrix& operator=(const S21Matrix& other);
    S21Matrix& operator+=(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix& operator*=(const S21Matrix& other);
    S21Matrix& operator*=(const double num);
    double& operator()(int rows, int cols);
    void fill_matrix();
    // void print_matrix();
};

#endif  // SRC_S21_MATRIX_OOP_H_
