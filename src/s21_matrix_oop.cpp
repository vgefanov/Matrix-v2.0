#include "s21_matrix_oop.h"

void S21Matrix::matrix_initialization(int rows_, int cols_) {
    matrix_ = new double*[rows_];
    if (matrix_ != nullptr) {
        for (int i = 0; i < rows_; i++) {
            matrix_[i] = new double[cols_]();
        }
    }
}

void S21Matrix::matrix_remove() {
    if (matrix_ != nullptr) {
        for (int i = 0; i < rows_; i++) {
            if (matrix_[i] != nullptr) {
                delete[] matrix_[i];
            }
        }
        delete[] matrix_;
    }
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRowsCols(int rows, int cols) {
    if (rows < 1 || cols < 1) {
        throw std::invalid_argument("Error. Incorrect data");
    }
    if (rows != rows_ || cols != cols_) {
        S21Matrix tmp(rows, cols);
        for (int i = 0; i < tmp.rows_ && i < rows_; i++) {
            for (int j = 0; j < tmp.cols_ && j < cols_; j++) {
                tmp.matrix_[i][j] = matrix_[i][j];
            }
        }
        std::swap(*this, tmp);
    }
}

S21Matrix::S21Matrix() : rows_(3), cols_(3) { matrix_initialization(rows_, cols_); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows_ < 1 || cols_ < 1) {
        throw std::invalid_argument("Error. Incorrect data");
    }
    matrix_initialization(rows, cols);
}

S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    if (this != &other) {
        matrix_initialization(other.rows_, other.cols_);
        *this = other;
    }
}

S21Matrix::S21Matrix(S21Matrix&& other) : rows_(other.rows_), cols_(other.cols_) {
    if (this != &other) {
        std::swap(matrix_, other.matrix_);
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
    }
    other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
    if (matrix_) {
        matrix_remove();
    }
}

bool S21Matrix::eq_matrix(const S21Matrix& other) const {
    bool result = true;
    if (rows_ == other.rows_ && cols_ == other.cols_) {
        for (int i = 0; (i < rows_) && result; i++) {
            for (int j = 0; (j < cols_) && result; j++) {
                if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) result = false;
            }
        }
    } else {
        result = false;
    }
    return result;
}

void S21Matrix::sum_matrix(const S21Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Error. Incorrect data");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] += other.matrix_[i][j];
        }
    }
}

void S21Matrix::sub_matrix(const S21Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Error. Incorrect data");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

void S21Matrix::mul_number(const double num) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = matrix_[i][j] * num;
        }
    }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Error. Incorrect data");
    }
    S21Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            for (int k = 0; k < cols_; k++) {
                result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    *this = result;
}

S21Matrix S21Matrix::transpose() {
    S21Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result.matrix_[j][i] = matrix_[i][j];
        }
    }
    return result;
}

S21Matrix S21Matrix::matrix_minor(int rows, int cols) {
    S21Matrix result(rows_ - 1, cols_ - 1);
    int rows_reduced = 0;
    for (int i = 0; i < result.rows_; i++) {
        if (rows_reduced == rows) rows_reduced++;
        int cols_reduced = 0;
        for (int j = 0; j < result.cols_; j++) {
            if (cols_reduced == cols) cols_reduced++;
            result.matrix_[i][j] = matrix_[rows_reduced][cols_reduced];
            cols_reduced++;
        }
        rows_reduced++;
    }
    return result;
}

double S21Matrix::determinant() {
    if (cols_ != rows_) {
        throw std::invalid_argument("Error. Incorrect data");
    }
    double result = 0;
    if (rows_ == 1) {
        result = matrix_[0][0];
    } else {
        S21Matrix minor;
        for (int i = 0; i < cols_; i++) {
            minor = matrix_minor(0, i);
            result += pow(-1, i) * minor.determinant() * matrix_[0][i];
        }
    }
    return result;
}

S21Matrix S21Matrix::calc_complements() {
    if (rows_ != cols_) {
        throw std::invalid_argument("Error. Incorrect data");
    }
    S21Matrix result(rows_, cols_);
    S21Matrix minor;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            minor = matrix_minor(i, j);
            result.matrix_[i][j] = pow(-1, i + j) * minor.determinant();
        }
    }
    return result;
}

S21Matrix S21Matrix::inverse_matrix() {
    S21Matrix result;
    double det = determinant();
    if (fabs(det) < EPS) {
        throw std::range_error("Error. Incorrect data");
    }
    result = calc_complements().transpose();
    result.mul_number(1 / det);
    return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    S21Matrix res(*this);
    res.sum_matrix(other);
    return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix res(*this);
    res.sub_matrix(other);
    return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix result(*this);
    result.mul_matrix(other);
    return result;
}

S21Matrix S21Matrix::operator*(const double num) {
    S21Matrix result(*this);
    result.mul_number(num);
    return result;
}

S21Matrix operator*(const double num, const S21Matrix& other) {
    S21Matrix result(other);
    result.mul_number(num);
    return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const { return eq_matrix(other); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    if (this != &other) {
        matrix_remove();
        rows_ = other.rows_;
        cols_ = other.cols_;
        matrix_initialization(other.rows_, other.cols_);
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] = other.matrix_[i][j];
            }
        }
    }
    return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    sum_matrix(other);
    return *this;
}
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    sub_matrix(other);
    return *this;
}
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    mul_matrix(other);
    return *this;
}
S21Matrix& S21Matrix::operator*=(const double num) {
    mul_number(num);
    return *this;
}
double& S21Matrix::operator()(int rows, int cols) {
    if (rows >= rows_ || cols >= cols_) {
        throw std::invalid_argument("Error. Incorrect data");
    }
    return matrix_[rows][cols];
}

void S21Matrix::fill_matrix() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = i + j;
        }
    }
}

// void S21Matrix::print_matrix() {
//     for (int i = 0; i < rows_; i++) {
//         for (int j = 0; j < cols_; j++) {
//             std::cout << matrix_[i][j] << "\t";
//         }
//         std::cout << std::endl;
//     }
// }

// int main() { return 0; }
