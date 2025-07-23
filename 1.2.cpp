#include <iostream>
#include <numeric> // для gcd щоб знайти спільний дільник (get common denominator)
using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;

    void reduce() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

public:
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        }
        reduce();
    }

    friend istream& operator>>(istream& in, Fraction& f) {
        char slash;
        in >> f.numerator >> slash >> f.denominator;
        if (f.denominator == 0) {
            throw invalid_argument("Denominator cannot be zero.");
        }
        f.reduce();
        return in;
    }

    friend ostream& operator<<(ostream& out, const Fraction& f) {
        int whole = f.numerator / f.denominator;
        int remainder = abs(f.numerator % f.denominator);

        if (f.numerator == 0) {
            out << "0";
        } else if (remainder == 0) {
            out << whole;
        } else if (abs(f.numerator) < f.denominator) {
            out << f.numerator << "/" << f.denominator;
        } else {
            out << whole << " " << remainder << "/" << f.denominator;
        }

        return out;
    }

    Fraction operator+(const Fraction& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator-(const Fraction& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw invalid_argument("Division by zero fraction.");
        }
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }

    bool operator<(const Fraction& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    bool operator<=(const Fraction& other) const {
        return *this < other || *this == other;
    }

    bool operator>(const Fraction& other) const {
        return !(*this <= other);
    }

    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }

    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }
};

int main() {
    try {
        Fraction a, b;

        cout << "Enter first fraction (format: numerator/denominator): ";
        cin >> a;
        cout << "Enter second fraction (format: numerator/denominator): ";
        cin >> b;

        cout << "\nReduced fractions:" << endl;
        cout << "A = " << a << endl;
        cout << "B = " << b << endl;

        cout << "\nArithmetic operations:" << endl;
        cout << "A + B = " << (a + b) << endl;
        cout << "A - B = " << (a - b) << endl;
        cout << "A * B = " << (a * b) << endl;
        cout << "A / B = " << (a / b) << endl;

        cout << "\nComparison results:" << endl;
        cout << "A <  B: " << (a < b) << endl;
        cout << "A <= B: " << (a <= b) << endl;
        cout << "A >  B: " << (a > b) << endl;
        cout << "A >= B: " << (a >= b) << endl;
        cout << "A == B: " << (a == b) << endl;
        cout << "A != B: " << (a != b) << endl;

    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}

