#include <bits/stdc++.h>
#include <codecvt>
#include "Polynomial.h"
using namespace std;
#define endl '\n'
#define ll long long

void displayMenu() {
        int choice = 15;

        do {
            cout << "Polynomial Operations Menu:\n";
            cout << "1. Display Polynomials\n";
            cout << "2. Add Polynomials\n";
            cout << "3. Subtract Polynomials\n";
            cout << "4. Multiply Polynomials\n";
            cout << "5. Check Equality of Polynomials\n";
            cout << "6. Get Degree of Polynomial\n";
            cout << "7. Evaluate Polynomial\n";
            cout << "8. Compose Polynomials\n";
            cout << "9. Get Derivative of Polynomial\n";
            cout << "10. Get Integral of Polynomial\n";
            cout << "11. Get Definite Integral of Polynomial\n";
            cout << "12. Find Root of Polynomial\n";
            cout << "13. Set Coefficients of Polynomial\n";
            cout << "14. Get Coefficient of Polynomial\n";
            cout << "15. Input Polynomials and Run All Operations\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            Polynomial p1, p2;
            int degree;
            switch (choice) {
                case 1:
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    p2 = inputPolynomial(degree);
                    displayPolynomials(p1, p2);
                    break;
                case 2:
                    
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    p2 = inputPolynomial(degree);
                    addPolynomials(p1, p2);
                    break;
                case 3:
                    
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    p2 = inputPolynomial(degree);
                    subtractPolynomials(p1, p2);
                    break;
                case 4:
                    
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    p2 = inputPolynomial(degree);
                    multiplyPolynomials(p1, p2);
                    break;
                case 5:
                    
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    p2 = inputPolynomial(degree);
                    checkEquality(p1, p2);
                    break;
                case 6:
                    
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    getDegree(p1);
                    break;
                case 7:
                    
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    evaluatePolynomial(p1);
                    break;
                case 8:
                    
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    p2 = inputPolynomial(degree);
                    composePolynomials(p1, p2);
                    break;
                case 9:
                    
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    getDerivative(p1);
                    break;
                case 10:
                    
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    getIntegral(p1);
                    break;
                case 11:
                    
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    getDefiniteIntegral(p1);
                    break;
                case 12:
                    
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    findRoot(p1);
                    break;
                case 13:
                    
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    setCoefficients(p1);
                    break;
                case 14:
                    
                    cout << "Enter the degree of the polynomial: ";
                    cin >> degree;
                    p1 = inputPolynomial(degree);
                    getCoefficient(p1);
                    break;
                case 15:
                    runAllOperations();
                    break;
                case 0:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 0);
    }