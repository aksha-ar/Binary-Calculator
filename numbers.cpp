#include<bits/stdc++.h>
#include "numbers.h"
using namespace std;

void initn(num& N1) {
    N1.decimalflag = 0;
    N1.flag = 0;
    N1.decimalpos = -1;
    init(N1.l);
}

void giveno(num& N1, int data) {
    append(N1.l, data);
}

void putno(number N1, ofstream& fp) {
    if (equaltozero(N1)) {
        cout << "0";
        fp << "0";
        return;
    }
    if (N1.flag == 1) {
        cout << "-";
        fp << "-";
    }
    if (N1.decimalflag == 0) {
        display(N1.l, -1, fp);
    } else {
        display(N1.l, N1.decimalpos, fp);
    }
}

int greaterthan(number N1, number N2) {
    return greater(N1.l, N2.l);
}

int equalto(number N1, number N2) {
    return equal(N1.l, N2.l);
}

void destroy(num& N1) {
    delete1(N1.l);
}

int equaltozero(number N1) {
    node* a = N1.l;
    while (a) {
        if (a->data != 0) return 0;
        a = a->next;
    }
    return 1;
}

void padding(num& N1, num& N2) {
    if (N1.decimalflag == 1 && N2.decimalflag == 1) {
        if (N1.decimalpos > N2.decimalpos) {
            for (int i = 0; i < (N1.decimalpos - N2.decimalpos); i++) {
                insert_at(N2.l, 0);
            }
            N2.decimalpos = N1.decimalpos;
        } else if (N1.decimalpos < N2.decimalpos) {
            for (int i = 0; i < (N2.decimalpos - N1.decimalpos); i++) {
                insert_at(N1.l, 0);
            }
            N1.decimalpos = N2.decimalpos;
        }
        int a = (length(N1.l) - N1.decimalpos);
        int b = (length(N2.l) - N2.decimalpos);
        if (a > b) {
            for (int i = 0; i < (a - b); i++) {
                append(N2.l, 0);
            }
        } else if (b > a) {
            for (int i = 0; i < (b - a); i++) {
                append(N1.l, 0);
            }
        }
    }
    // other cases omitted for brevity, similar handling applies
}

number add(number N1, number N2) {
    number N3;
    initn(N3);
    if (!(N2.l) || !(N1.l)) {
        N3.l = nullptr;
        return N3;
    }
    padding(N1, N2);
    if ((N1.flag == 1 && N2.flag == 1) || (N1.flag == 0 && N2.flag == 0)) {
        int carry = 0, a1 = 0, result = 0;
        node* a = lastptr(N1.l);
        node* b = lastptr(N2.l);
        while (a && b) {
            result = a->data + b->data + carry;
            if ((result / 10) >= 1) {
                a1 = result % 10;
                carry = result / 10;
            } else {
                a1 = result;
                carry = 0;
            }
            insert_at(N3.l, a1);
            a = a->prev;
            b = b->prev;
        }
        if (carry != 0) {
            insert_at(N3.l, carry);
        }
        N3.decimalflag = N1.decimalflag;
        N3.decimalpos = (carry != 0) ? (N1.decimalpos + 1) : N1.decimalpos;
        N3.flag = N1.flag;
        return N3;
    }
    // Handle cases for flags
    if (N1.flag == 1 && N2.flag == 0) {
        N1.flag = 0;
        N3 = subtract(N2, N1);
        N1.flag = 1;
        return N3;
    } else {
        N2.flag = 0;
        N3 = subtract(N1, N2);
        N2.flag = 1;
        return N3;
    }
}

number subtract(number N1, number N2) {
    number N3;
    initn(N3);
    if (!(N2.l) || !(N1.l)) {
        N3.l = nullptr;
        return N3;
    }
    padding(N1, N2);
    if (N1.flag == 0 && N2.flag == 0) {
        node* a = lastptr(N1.l);
        node* b = lastptr(N2.l);
        int borrow = 0, result = 0;
        if (greaterthan(N1, N2)) {
            while (a && b) {
                if (a->data >= (b->data + borrow)) {
                    result = a->data - (b->data + borrow);
                    borrow = 0;
                } else {
                    result = 10 + a->data - (b->data + borrow);
                    borrow = 1;
                }
                insert_at(N3.l, result);
                a = a->prev;
                b = b->prev;
            }
        } else if (equalto(N1, N2)) {
            for (int i = 0; i < length(N1.l); i++) {
                insert_at(N3.l, 0);
            }
            return N3;
        } else {
            while (a && b) {
                if (b->data >= (a->data + borrow)) {
                    result = b->data - (a->data + borrow);
                    borrow = 0;
                } else {
                    result = 10 + b->data - (a->data + borrow);
                    borrow = 1;
                }
                insert_at(N3.l, result);
                a = a->prev;
                b = b->prev;
            }
            N3.flag = 1;
        }
        N3.decimalflag = N1.decimalflag;
        N3.decimalpos = N1.decimalpos;
        return N3;
    }
    // Handle flag cases for subtraction
    if (N1.flag == 0 && N2.flag == 1) {
        N2.flag = 0;
        N3 = add(N1, N2);
        N2.flag = 1;
        return N3;
    }
    if (N1.flag == 1 && N2.flag == 0) {
        N2.flag = 1;
        N3 = add(N1, N2);
        N2.flag = 0;
        return N3;
    }
    // other cases omitted for brevity
}

number multiply_sdigit(number N1, int dig) {
    number N3;
    initn(N3);
    int k = length(N1.l);
    for (int i = 1; i <= k; i++) {
        append(N3.l, 0);
    }
    if (dig == 0) return N3;
    while (dig != 0) {
        N3 = add(N3, N1);
        dig--;
    }
    return N3;
}

number multiply(number N1, number N2) {
    number N3, N4;
    initn(N3);
    initn(N4);
    if (!(N2.l) || !(N1.l)) {
        N3.l = nullptr;
        return N3;
    }
    int f1 = N1.flag, f2 = N2.flag;
    N1.flag = N2.flag = 0;
    int df1 = N1.decimalflag, df2 = N2.decimalflag;
    int dp1 = length(N1.l) - ((df1 == 1) ? (N1.decimalpos) : length(N1.l));
    int dp2 = length(N2.l) - ((df2 == 1) ? (N2.decimalpos) : length(N2.l));
    N1.decimalflag = N2.decimalflag = 0;

    for (int k = 1; k <= length(N1.l); k++) {
        append(N4.l, 0);
    }
    int i = 0, len = length(N2.l);
    node* b = lastptr(N2.l);
    while (b && i < len) {
        N3 = multiply_sdigit(N1, b->data);
        for (int j = 0; j < i; j++) {
            append(N3.l, 0);
        }
        N4 = add(N4, N3);
        i++;
        b = b->prev;
    }
    if (f1 + f2 == 1) {
        N4.flag = 1;
    } else {
        N4.flag = 0;
    }
    if ((df1 + df2) != 0) {
        N4.decimalflag = 1;
        N4.decimalpos = dp1 + dp2;
    } else {
        N4.decimalflag = 0;
        N4.decimalpos = -1;
    }
    return N4;
}