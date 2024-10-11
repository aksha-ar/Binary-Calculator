#ifndef EVAL_H_INCLUDED
#define EVAL_H_INCLUDED

#include "stack.h"
#include <stack>
#include <string>

// Function declarations
int preced(char c);
bool isOperator(char c);
void evaluate(char ch, std::stack<number>& s);
void expression(const std::string& ex, std::stack<number>& s1, std::stack<char>& s2);

#endif // EVAL_H_INCLUDED
