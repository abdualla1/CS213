#include "Polynomial.h"

// Constructors
Polynomial::Polynomial() {}

Polynomial::Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {}

Polynomial::Polynomial(const Polynomial& other) : coeffs(other.coeffs) {}

// Destructor
Polynomial::~Polynomial() {}

// Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coeffs = other.coeffs;
    }
    return *this;
}

// Arithmetic operators
Polynomial Polynomial::operator+(const Polynomial& other) const {
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0.0);
    for (size_t i = 0; i < result.size(); ++i) {
        if (i < coeffs.size()) result[i] += coeffs[i];
        if (i < other.coeffs.size()) result[i] += other.coeffs[i];
    }
    return Polynomial(result);
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    vector<double> result(max(coeffs.size(), other.coeffs.size()), 0.0);
    for (size_t i = 0; i < result.size(); ++i) {
        if (i < coeffs.size()) result[i] += coeffs[i];
        if (i < other.coeffs.size()) result[i] -= other.coeffs[i];
    }
    return Polynomial(result);
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0.0);
    for (size_t i = 0; i < coeffs.size(); ++i) {
        for (size_t j = 0; j < other.coeffs.size(); ++j) {
            result[i + j] += coeffs[i] * other.coeffs[j];
        }
    }
    return Polynomial(result);
}

// Equality operator
bool Polynomial::operator==(const Polynomial& other) const {
    return coeffs == other.coeffs;
}

// Output operator
ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = poly.coeffs.size() - 1; i >= 0; --i) {
        if (poly.coeffs[i] != 0) {
            if (i != poly.coeffs.size() - 1 && poly.coeffs[i] > 0) out << "+";
            out << poly.coeffs[i];
            if (i > 0) out << "x";
            if (i > 1) out << "^" << i;
            out << " ";
        }
    }
    return out;
}

// Utility functions
int Polynomial::degree() const {
    return coeffs.size() - 1;
}

double Polynomial::evaluate(double x) const {
    double result = 0.0;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}

Polynomial Polynomial::compose(const Polynomial& q) const {
    Polynomial result;
    for (int i = coeffs.size() - 1; i >= 0; --i) {
        result = result * q + Polynomial({coeffs[i]});
    }
    return result;
}

Polynomial Polynomial::derivative() const {
    vector<double> result;
    for (int i = 1; i < coeffs.size(); ++i) {
        result.push_back(coeffs[i] * i);
    }
    return Polynomial(result);
}

Polynomial Polynomial::integral() const {
    vector<double> result = {0.0};
    for (int i = 0; i < coeffs.size(); ++i) {
        result.push_back(coeffs[i] / (i + 1));
    }
    return Polynomial(result);
}

double Polynomial::integral(double x1, double x2) const {
    Polynomial integralPoly = integral();
    return integralPoly.evaluate(x2) - integralPoly.evaluate(x1);
}

double Polynomial::getRoot(double guess, double tolerance, int maxIter) {
    Polynomial deriv = derivative();
    for (int i = 0; i < maxIter; ++i) {
        double value = evaluate(guess);
        if (abs(value) < tolerance) return guess;
        double derivValue = deriv.evaluate(guess);
        if (derivValue == 0) break;
        guess -= value / derivValue;
    }
    return guess;
}

void Polynomial::setCoefficients(const vector<double>& coefficients) {
    coeffs = coefficients;
}

double Polynomial::getCoefficient(int degree) const {
    if (degree < 0 || degree >= coeffs.size()) return 0.0;
    return coeffs[degree];
}

int main() {
    Polynomial p1({1, -2, 3}); // Represents 1 - 2x + 3x^2
    Polynomial p2({-1, 4}); // Represents -1 + 4x

    Polynomial sum = p1 + p2;
    Polynomial difference = p1 - p2;
    Polynomial product = p1 * p2;

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p1 + p2: " << sum << endl;
    cout << "p1 - p2: " << difference << endl;
    cout << "p1 * p2: " << product << endl;

    double x = 2.5;
    cout << "p1 evaluated at x = " << x << ": " << p1.evaluate(x) << endl;
    cout << "p2 evaluated at x = " << x << ": " << p2.evaluate(x) << endl;

    return 0;
}