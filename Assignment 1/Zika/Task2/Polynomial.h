#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <bits/stdc++.h>
#include <codecvt>
using namespace std;
#define endl '\n'
#define ll long long

class Polynomial {
private:
    vector<double> coeffs; // Store coefficients of the polynomial

public:
    // Constructors
    Polynomial() {}
    Polynomial(const vector<double>& coefficients) : coeffs(coefficients) {}
    Polynomial(const Polynomial& other) : coeffs(other.coeffs) {}

    // Destructor
    ~Polynomial() {}

    // Assignment operator
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            coeffs = other.coeffs;
        }
        return *this;
    }

    // Arithmetic operators
    Polynomial operator+(const Polynomial& other) const {
        vector<double> result(max(coeffs.size(), other.coeffs.size()), 0.0);
        for (size_t i = 0; i < result.size(); ++i) {
            if (i < coeffs.size()) result[i] += coeffs[i];
            if (i < other.coeffs.size()) result[i] += other.coeffs[i];
        }
        return Polynomial(result);
    }

    Polynomial operator-(const Polynomial& other) const {
        vector<double> result(max(coeffs.size(), other.coeffs.size()), 0.0);
        for (size_t i = 0; i < result.size(); ++i) {
            if (i < coeffs.size()) result[i] += coeffs[i];
            if (i < other.coeffs.size()) result[i] -= other.coeffs[i];
        }
        return Polynomial(result);
    }

    Polynomial operator*(const Polynomial& other) const {
        vector<double> result(coeffs.size() + other.coeffs.size() - 1, 0.0);
        for (size_t i = 0; i < coeffs.size(); ++i) {
            for (size_t j = 0; j < other.coeffs.size(); ++j) {
                result[i + j] += coeffs[i] * other.coeffs[j];
            }
        }
        return Polynomial(result);
    }

    // Equality operator
    bool operator==(const Polynomial& other) const {
        return coeffs == other.coeffs;
    }

    // Output operator
    friend ostream& operator<<(ostream& out, const Polynomial& poly) {
        for (int i = poly.coeffs.size() - 1; i >= 0; --i) {
            if (poly.coeffs[i] != 0) {
                if (i != poly.coeffs.size() - 1 && poly.coeffs[i] > 0) out << "+";
                out << poly.coeffs[i];
                if (i > 0) out << "x^" << i << " ";
            }
        }
        return out;
    }

    // Utility functions
    int degree() const {
        return coeffs.size() - 1;
    }

    double evaluate(double x) const {
        double result = 0.0;
        for (int i = coeffs.size() - 1; i >= 0; --i) {
            result = result * x + coeffs[i];
        }
        return result;
    }

    Polynomial compose(const Polynomial& q) const {
        Polynomial result;
        Polynomial powerOfQ({1});
        for (const auto& coeff : coeffs) {
            result = result + powerOfQ * Polynomial({coeff});
            powerOfQ = powerOfQ * q;
        }
        return result;
    }

    Polynomial derivative() const {
        vector<double> result;
        for (size_t i = 1; i < coeffs.size(); ++i) {
            result.push_back(coeffs[i] * i);
        }
        return Polynomial(result);
    }

    Polynomial integral() const {
        vector<double> result(coeffs.size() + 1, 0.0);
        for (size_t i = 0; i < coeffs.size(); ++i) {
            result[i + 1] = coeffs[i] / (i + 1);
        }
        return Polynomial(result);
    }

    double integral(double x1, double x2) const {
        Polynomial integralPoly = this->integral();
        return integralPoly.evaluate(x2) - integralPoly.evaluate(x1);
    }

   double getRoot(double guess = 1, double tolerance = 1e-6, int maxIter = 100) const {
        Polynomial deriv = this->derivative();
        double x = guess;
        for (int i = 0; i < maxIter; ++i) {
            double fx = this->evaluate(x);
            double fpx = deriv.evaluate(x);
            if (fabs(fpx) < tolerance) {
                throw runtime_error("Derivative too small");
            }
            double x1 = x - fx / fpx;
            if (fabs(x1 - x) < tolerance) {
                return x1;
            }
            x = x1;
        }
        throw runtime_error("No Real Root Found");
    }

    void setCoefficients(const vector<double>& coefficients) {
        coeffs = coefficients;
    }

    double getCoefficient(int degree) const {
        if (degree < 0 || degree >= coeffs.size()) throw out_of_range("Degree out of range");
        return coeffs[degree];
    }
};

#endif