#include <iostream>
using namespace std;

class cubic {
private:
    double a, b, c, d;  

public:
    // Constructor with initial values 
    cubic(double a_val = 0, double b_val = 0, double c_val = 0, double d_val = 0);

    // Operator+ overload 
    cubic operator+(const cubic& other) const;

    // Overload << for printing 
    friend ostream& operator<<(ostream& os, const cubic& poly);

    // Overload >> for reading 
    friend istream& operator>>(istream& is, cubic& poly);

    // Eval function for computing value at a given x 
    double eval(double x) const;
};


int main() {
    cubic poly1, poly2;

    // Read the coefficients of the first polynomial
    cout << "Enter coefficients for polynomial 1 (a b c d): ";
    cin >> poly1;  // Use overloaded >> to enter coefficients
 
    
    cout << "Enter coefficients for polynomial 2 (a b c d): ";
    cin >> poly2; 

    // Output two polynomials
    cout << "Polynomial 1: " << poly1 << endl;  // Use overloaded << to print polynomials
    cout << "Polynomial 2: " << poly2 << endl;  

    // Compute the sum of two polynomials
    cubic sum = poly1 + poly2;  // Use overloaded + to add polynomials
    cout << "Sum of polynomials: " << sum << endl;  

    //Computes the value of a polynomial at some value of x
    double x;
    cout << "Enter a value for x to evaluate both polynomials: ";
    cin >> x;
    cout << "Value of polynomial 1 at x = " << x << ": " << poly1.eval(x) << endl;
    cout << "Value of polynomial 2 at x = " << x << ": " << poly2.eval(x) << endl;
    cout << "Value of sum at x = " << x << ": " << sum.eval(x) << endl;

    return 0;
}

// Constructor definition
cubic::cubic(double a_val, double b_val, double c_val, double d_val) {
    this->a = a_val;
    this->b = b_val;
    this->c = c_val;
    this->d = d_val;
}

// Operator+ overload definition
cubic cubic::operator+(const cubic& other) const {
    return cubic(a + other.a, b + other.b, c + other.c, d + other.d);
}

// Overload << definition
ostream& operator<<(ostream& os, const cubic& poly) {
    os << poly.a << "x^3 + " << poly.b << "x^2 + " << poly.c << "x + " << poly.d;
    return os;
}

// Overload >> definition
istream& operator>>(istream& is, cubic& poly) {
    is >> poly.a >> poly.b >> poly.c >> poly.d;
    return is;
}

// Eval definition
double cubic::eval(double x) const {
    return a * x * x * x + b * x * x + c * x + d;
}