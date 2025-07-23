#include <iostream>
#include <stdexcept>
#include <iomanip>

class MatrixSizeMismatch : public std::runtime_error {
public:
    MatrixSizeMismatch(const std::string& msg) : std::runtime_error(msg) {}
};

class MatrixIndexOutOfBounds : public std::runtime_error {
public:
    MatrixIndexOutOfBounds(const std::string& msg) : std::runtime_error(msg) {}
};

class Matrix {
private:
    int** data;
    int rows, cols;

    void allocate(int r, int c) {
        rows = r;
        cols = c;
        data = new int*[rows];
        for (int i = 0; i < rows; ++i)
            data[i] = new int[cols]{};
    }

    void deallocate() {
        for (int i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;
    }

public:
    Matrix() : data(nullptr), rows(0), cols(0) {}

    Matrix(int r, int c) {
        if (r <= 0 || c <= 0) throw std::invalid_argument("Invalid matrix size");
        allocate(r, c);
    }
    Matrix(const Matrix& other) {
        allocate(other.rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = other.data[i][j];
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            deallocate();
            allocate(other.rows, other.cols);
            for (int i = 0; i < rows; ++i)
                for (int j = 0; j < cols; ++j)
                    data[i][j] = other.data[i][j];
        }
        return *this;
    }

    ~Matrix() {
        if (data) deallocate();
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw MatrixSizeMismatch("Addition: size mismatch");
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw MatrixSizeMismatch("Subtraction: size mismatch");
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] - other.data[i][j];
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows)
            throw MatrixSizeMismatch("Multiplication: incompatible sizes");
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < other.cols; ++j)
                for (int k = 0; k < cols; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
        return result;
    }

    int* operator[](int index) {
        if (index < 0 || index >= rows)
            throw MatrixIndexOutOfBounds("Row index out of bounds");
        return data[index];
    }

    const int* operator[](int index) const {
        if (index < 0 || index >= rows)
            throw MatrixIndexOutOfBounds("Row index out of bounds");
        return data[index];
    }

    friend std::istream& operator>>(std::istream& in, Matrix& m) {
        for (int i = 0; i < m.rows; ++i)
            for (int j = 0; j < m.cols; ++j)
                in >> m.data[i][j];
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Matrix& m) {
        for (int i = 0; i < m.rows; ++i) {
            for (int j = 0; j < m.cols; ++j)
                out << std::setw(4) << m.data[i][j];
            out << '\n';
        }
        return out;
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

void replaceNegativesWithSquares(Matrix& m) {
    for (int i = 0; i < m.getRows(); ++i)
        for (int j = 0; j < m.getCols(); ++j)
            if (m[i][j] < 0)
                m[i][j] *= m[i][j];
}

int main() {
    try {
        Matrix a(2, 3), b(2, 3), c(3, 2);
        std::cout << "Enter matrix A (2x3):\n";
        std::cin >> a;
        std::cout << "Enter matrix B (2x3):\n";
        std::cin >> b;
        std::cout << "Enter matrix C (3x2):\n";
        std::cin >> c;

        std::cout << "\nMatrix A:\n" << a;
        std::cout << "Matrix B:\n" << b;
        std::cout << "Matrix C:\n" << c;

        std::cout << "\nA + B:\n" << (a + b);
        std::cout << "A - B:\n" << (a - b);
        std::cout << "A * C:\n" << (a * c);

        std::cout << "\nModifying matrix A (replace negatives with squares)...\n";
        replaceNegativesWithSquares(a);
        std::cout << "Modified Matrix A:\n" << a;

        std::cout << "\nTrying A + C (should fail):\n";
        Matrix fail = a + c;

    } catch (const MatrixSizeMismatch& ex) {
        std::cerr << "Matrix size error: " << ex.what() << '\n';
    } catch (const MatrixIndexOutOfBounds& ex) {
        std::cerr << "Index error: " << ex.what() << '\n';
    } catch (const std::exception& ex) {
        std::cerr << "General error: " << ex.what() << '\n';
    }

    return 0;
}
