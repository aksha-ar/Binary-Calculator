#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>
#include "eval.h"

int main() {
    std::string ex;
    std::stack<number> s1;
    number N5;
    initn(&N5);
    std::stack<char> s2;
    inits(&s1, 100);
    init1(&s2, 100);

    std::ofstream fp("E:/SYBTECH SEM 1/BCalculator_Project/History1.txt", std::ios::app);
    
    while (true) {
        std::cout << ">>>> ";
        std::getline(std::cin, ex);
        
        fp << ex;
        
        if (ex[0] == 'q') {
            fp << "\n";
            break;
        }

        expression(ex.c_str(), &s1, &s2);
        N5 = pop(&s1);
        
        if (!(N5.l)) {
            std::cout << "Error\n";
            fp << "\nError\n";
        } else {
            fp << "\n";
            putno(N5, fp);
            destroy(&N5);
        }
        
        std::cout << "\n";
        fp << "\n";
    }

    return 0;
}
