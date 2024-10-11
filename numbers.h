#ifndef NUMBERS_H_INCLUDED
#define NUMBERS_H_INCLUDED

#include <iostream>
#include <fstream>
#include "dlist.h"

class Number {
public:
    DList l;  // Assuming DList is a previously defined class for the doubly linked list
    int flag;           // Flag for negative numbers (1 for negative, 0 for positive)
    int decimalflag;    // Flag to indicate if the number is decimal
    int decimalpos;     // Position of the decimal point

    // Constructor to initialize Number
    Number() : flag(0), decimalflag(0), decimalpos(0) {}

    // Member functions for number operations
    void init();
    void giveno(int data);
    Number add(const Number& N2) const;
    Number subtract(const Number& N2) const;
    Number multiply(const Number& N2) const;
    Number multiply_sdigit(int dig) const;
    void padding(const Number& N2);
    bool equalto(const Number& N2) const;
    bool greaterthan(const Number& N2) const;
    void putno(std::ofstream& fp) const;
    void destroy();
    Number power(const Number& b) const;
    bool equaltozero() const;
    void divideby(const Number& N2, Number& N3) const;
    void dividedecimal(const Number& N2, Number& N3) const;
    void decimal(const Number& N2, Number& N3) const;
};

// Type alias for pointers to Number
using num = Number*;

#endif // NUMBERS_H_INCLUDED
