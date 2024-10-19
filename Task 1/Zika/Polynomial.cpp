#include <bits/stdc++.h>
#include <codecvt>
#include "Polynomial.h"
using namespace std;
#define endl '\n'
#define ll long long

class PolynomialInterface {
public:
void runAllOperations() {
        int degree1, degree2;
        cin >> degree1;
        vector<double> coefficients1(degree1 + 1);
        for (int i = 0; i <= degree1; ++i) {
            cin >> coefficients1[i];
        }
        degree2 = degree1;
        // cin >> degree2;
        vector<double> coefficients2(degree2 + 1);
        for (int i = 0; i <= degree2; i++)
        {
            cin >> coefficients2[i];
        }
        
        Polynomial p1(coefficients1);
        Polynomial p2(coefficients2);
        cout << endl;
        cout << "Polynomial p1: " << p1 << endl;
        cout << "Polynomial p2: " << p2 << endl;

        // Addition
        Polynomial sum = p1 + p2;
        cout << "p1 + p2: " << sum << endl;

        // Subtraction
        Polynomial diff = p1 - p2;
        cout << "p1 - p2: " << diff << endl;

        // Multiplication
        Polynomial prod = p1 * p2;
        cout << "p1 * p2: " << prod << endl;

        // Equality
        bool isEqual = (p1 == p2);
        cout << "p1 == p2: " << (isEqual ? "true" : "false") << endl;

        // Degree
        cout << "Degree of p1: " << p1.degree() << endl;
        cout << "Degree of p2: " << p2.degree() << endl;

        // Evaluation
        double x = 2;
        double eval1 = p1.evaluate(x);
        double eval2 = p2.evaluate(x);
        cout << "p1 evaluated at x=" << x << ": " << eval1 << endl;
        cout << "p2 evaluated at x=" << x << ": " << eval2 << endl;

        //Composition
        // Polynomial comp = p1.compose(p2);
        // cout << "p1 composed with p2: " << comp << endl;

        // Derivative
        Polynomial deriv1 = p1.derivative();
        Polynomial deriv2 = p2.derivative();
        cout << "Derivative of p1: " << deriv1 << endl;
        cout << "Derivative of p2: " << deriv2 << endl;

        // Integral
        Polynomial integ1 = p1.integral();
        Polynomial integ2 = p2.integral();
        cout << "Integral of p1: " << integ1 << endl;
        cout << "Integral of p2: " << integ2 << endl;

        //Definite integral
        double x1 = 0, x2 = 1;
        double defInteg1 = p1.integral(x1, x2);
        double defInteg2 = p2.integral(x1, x2);
        cout << "Definite integral of p1 from " << x1 << " to " << x2 << ": " << defInteg1 << endl;
        cout << "Definite integral of p2 from " << x1 << " to " << x2 << ": " << defInteg2 << endl;

        //Root finding
        // try {
        //     double root1 = p1.getRoot();
        //     cout << "Root of p1: " << root1 << endl;
        // } catch (const runtime_error& e) {
        //     cout << e.what() << endl;
        //     return;
        // }

        // try {
        //     double root2 = p2.getRoot();
        //     cout << "Root of p2: " << root2 << endl;
        // } catch (const runtime_error& e) {
        //     cout << e.what() << endl;
        //     return;
        // }
    }
    Polynomial inputPolynomial(int degree) {
        vector<double> coefficients(degree + 1);
        cout << "Enter the coefficients from highest degree to constant term:\n";
        for (int i = degree; i >= 0; --i) {
            cout << "Coefficient of x^" << i << ": ";
            cin >> coefficients[i];
        }
        return Polynomial(coefficients);
    }
    void displayPolynomials(const Polynomial& p1, const Polynomial& p2) {
        cout << "Polynomial p1: " << p1 << endl;
        cout << "Polynomial p2: " << p2 << endl;
    }

    void addPolynomials(const Polynomial& p1, const Polynomial& p2) {
        Polynomial sum = p1 + p2;
        cout << "p1 + p2: " << sum << endl;
    }

    void subtractPolynomials(const Polynomial& p1, const Polynomial& p2) {
        Polynomial diff = p1 - p2;
        cout << "p1 - p2: " << diff << endl;
    }

    void multiplyPolynomials(const Polynomial& p1, const Polynomial& p2) {
        Polynomial prod = p1 * p2;
        cout << "p1 * p2: " << prod << endl;
    }

    void checkEquality(const Polynomial& p1, const Polynomial& p2) {
        bool isEqual = (p1 == p2);
        cout << "p1 == p2: " << (isEqual ? "true" : "false") << endl;
    }

    void getDegree(const Polynomial& p1) {
        cout << "Degree of p1: " << p1.degree() << endl;
    }

    void evaluatePolynomial(const Polynomial& p1) {
        double x;
        cout << "Enter value of x: ";
        cin >> x;
        double eval = p1.evaluate(x);
        cout << "p1 evaluated at x=" << x << ": " << eval << endl;
    }

    void composePolynomials(const Polynomial& p1, const Polynomial& p2) {
        Polynomial comp = p1.compose(p2);
        cout << "p1 composed with p2: " << comp << endl;
    }

    void getDerivative(const Polynomial& p1) {
        Polynomial deriv = p1.derivative();
        cout << "Derivative of p1: " << deriv << endl;
    }

    void getIntegral(const Polynomial& p1) {
        Polynomial integ = p1.integral();
        cout << "Integral of p1: " << integ << endl;
    }

    void getDefiniteIntegral(const Polynomial& p1) {
        double x1, x2;
        cout << "Enter lower limit x1: ";
        cin >> x1;
        cout << "Enter upper limit x2: ";
        cin >> x2;
        double defInteg = p1.integral(x1, x2);
        cout << "Definite integral of p1 from " << x1 << " to " << x2 << ": " << defInteg << endl;
    }

    void findRoot(const Polynomial& p1) {
        try {
            double root = p1.getRoot();
            cout << "Root of p1: " << root << endl;
        } catch (const runtime_error& e) {
            cout << "Error finding root: " << e.what() << endl;
        }
    }

    void setCoefficients(Polynomial& p1) {
        vector<double> coefficients(p1.degree() + 1);
        cout << "Enter the coefficients: ";
        for (int i = 0; i <= p1.degree(); ++i) {
            cin >> coefficients[i];
        }
        p1.setCoefficients(coefficients);
        cout << "p1 after setting new coefficients: " << p1 << endl;
    }

    void getCoefficient(const Polynomial& p1) {
        try {
            double coeff = p1.getCoefficient(p1.degree());
            cout << "Coefficient of x^" << p1.degree() << " in p1: " << coeff << endl;
        } catch (const out_of_range& e) {
            cout << "Error getting coefficient: " << e.what() << endl;
        }
    }
};

int main() {
    int t = 20;
    while(t--){
        cout << "Test" << 20 - t << ':' << endl;
        PolynomialInterface interface;
        interface.runAllOperations();
    }
}