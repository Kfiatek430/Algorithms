#include <iostream>
#include <cstdlib>
using namespace std;

class Matrix {
protected:
    int rows;
    int cols;
    int **data = nullptr;
    char *name;

public:
    Matrix();
    Matrix(int rows, int cols, char *name = "Unnamed");
    Matrix(const Matrix &src);
    ~Matrix();

    void setValue(int row, int col, int value);
    int getValue(int row, int col) const;
    int getRows() const;
    int getCols() const;
    void fillWithRandomValues(int maxValue = 9);
    void print(const char *newName = "") const;
    Matrix transpose() const;
    static int determinant(Matrix matrix);

    friend Matrix operator+(const Matrix &m1, const Matrix &m2);
    friend Matrix operator*(const Matrix &m1, int scalar);
    friend Matrix operator*(const Matrix &m1, const Matrix &m2);

    Matrix &operator=(const Matrix &other);
    friend istream &operator>>(istream &input, Matrix &matrix);
    friend ostream &operator<<(ostream &output, const Matrix &matrix);

private:
    void allocateMemory();
    void releaseMemory();
    void copyFrom(const Matrix &src);
};

Matrix::Matrix() {}

Matrix::Matrix(int rows, int cols, char *name) {
    this->rows = rows;
    this->cols = cols;
    this->name = name;
    allocateMemory();
}

Matrix::Matrix(const Matrix &src) {
    copyFrom(src);
}

Matrix::~Matrix() {
    releaseMemory();
}

void Matrix::allocateMemory() {
    data = new int *[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[cols];
    }
}

void Matrix::releaseMemory() {
    if (data) {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}

void Matrix::copyFrom(const Matrix &src) {
    rows = src.rows;
    cols = src.cols;
    name = src.name;
    allocateMemory();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = src.data[i][j];
        }
    }
}

void Matrix::setValue(int row, int col, int value) {
    data[row][col] = value;
}

int Matrix::getValue(int row, int col) const {
    return data[row][col];
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getCols() const {
    return cols;
}

void Matrix::fillWithRandomValues(int maxValue) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            setValue(i, j, 1 + (rand() % maxValue));
        }
    }
}

void Matrix::print(const char *newName) const {
    cout << "\nMatrix " << (newName[0] ? newName : name) << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << data[i][j] << (j < cols - 1 ? ' ' : '\n');
        }
    }
    cout << "==========================================" << endl;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows, "Transpose");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

int Matrix::determinant(Matrix matrix) {
    if (matrix.getRows() == 1) return matrix.getValue(0, 0);

    int result = 0;
    int size = matrix.getRows();
    Matrix subMatrix(size - 1, size - 1, "SubMatrix");

    for (int col = 0; col < size; col++) {
        if (matrix.getValue(0, col) != 0) {
            int subRow = 0;
            for (int i = 1; i < size; i++) {
                int subCol = 0;
                for (int j = 0; j < size; j++) {
                    if (j != col) {
                        subMatrix.setValue(subRow, subCol++, matrix.getValue(i, j));
                    }
                }
                subRow++;
            }
            result += ((col % 2 == 0 ? 1 : -1) * matrix.getValue(0, col) * determinant(subMatrix));
        }
    }
    return result;
}

Matrix operator+(const Matrix &m1, const Matrix &m2) {
    if (m1.rows != m2.rows || m1.cols != m2.cols) {
        cerr << "Matrix dimensions must match for addition." << endl;
        exit(EXIT_FAILURE);
    }

    Matrix result(m1.rows, m1.cols, "Addition");
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            result.data[i][j] = m1.data[i][j] + m2.data[i][j];
        }
    }
    return result;
}

Matrix operator*(const Matrix &m1, int scalar) {
    Matrix result(m1.rows, m1.cols, "Scalar Multiplication");
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            result.data[i][j] = m1.data[i][j] * scalar;
        }
    }
    return result;
}

Matrix operator*(const Matrix &m1, const Matrix &m2) {
    if (m1.rows != m2.rows || m1.cols != m2.cols) {
        cerr << "Matrix dimensions must match for multiplication." << endl;
        exit(EXIT_FAILURE);
    }

    Matrix result(m1.rows, m1.cols, "Element-wise Multiplication");
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            result.data[i][j] = m1.data[i][j] * m2.data[i][j];
        }
    }
    return result;
}

Matrix &Matrix::operator=(const Matrix &other) {
    if (this != &other) {
        releaseMemory();
        copyFrom(other);
    }
    return *this;
}

istream &operator>>(istream &input, Matrix &matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            input >> matrix.data[i][j];
        }
    }
    return input;
}

ostream &operator<<(ostream &output, const Matrix &matrix) {
    output << "\nMatrix " << matrix.name << endl;
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            output << matrix.data[i][j] << (j < matrix.cols - 1 ? ' ' : '\n');
        }
    }
    output << "==========================================" << endl;
    return output;
}

int main() {
    cout << "Testing the Matrix class and its methods.\n";

    cout << "\nCreating and filling a 3x3 matrix with random values (1-9):\n";
    Matrix matrixA(3, 3, "Matrix A");
    matrixA.fillWithRandomValues();
    matrixA.print();

    cout << "\nTranspose of Matrix A:\n";
    Matrix transposedMatrix = matrixA.transpose();
    transposedMatrix.print("Transpose of Matrix A");

    cout << "\nCalculating the determinant of Matrix A:\n";
    int determinantA = Matrix::determinant(matrixA);
    cout << "Determinant of Matrix A: " << determinantA << endl;

    cout << "\nCreating two 2x3 matrices (Matrix B and Matrix C) and filling them with random values:\n";
    Matrix matrixB(2, 3, "Matrix B");
    Matrix matrixC(2, 3, "Matrix C");
    matrixB.fillWithRandomValues();
    matrixC.fillWithRandomValues();
    matrixB.print();
    matrixC.print();

    cout << "\nAdding Matrix B and Matrix C:\n";
    Matrix additionResult = matrixB + matrixC;
    additionResult.print("Addition Result");

    cout << "\nMultiplying Matrix B by scalar 5:\n";
    Matrix scalarMultiplicationResult = matrixB * 5;
    scalarMultiplicationResult.print("Scalar Multiplication Result");

    cout << "\nElement-wise multiplication of Matrix B and Matrix C:\n";
    Matrix elementWiseMultiplicationResult = matrixB * matrixC;
    elementWiseMultiplicationResult.print("Element-wise Multiplication Result");

    cout << "\nCreating a copy of Matrix A and modifying the copy:\n";
    Matrix matrixACopy = matrixA;
    matrixACopy.setValue(0, 0, 999);
    matrixA.print("Matrix A (Original)");
    matrixACopy.print("Matrix A Copy (Modified)");

    cout << "\nTesting input and output operators. Enter a 2x2 matrix (row by row):\n";
    Matrix inputMatrix(2, 2, "Input Matrix");
    cin >> inputMatrix;
    cout << "You entered:\n" << inputMatrix;

    cout << "\nTesting determinant of a 1x1 matrix:\n";
    Matrix oneByOneMatrix(1, 1, "1x1 Matrix");
    oneByOneMatrix.setValue(0, 0, 7);
    oneByOneMatrix.print();
    cout << "Determinant: " << Matrix::determinant(oneByOneMatrix) << endl;

    cout << "\nEnd of Matrix class tests." << endl;
    return 0;
}
