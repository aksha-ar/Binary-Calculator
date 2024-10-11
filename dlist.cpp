#include <iostream>
#include <limits.h>

using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

typedef Node* DList;

void init(DList& l) {
    l = NULL;
}

void append(DList& l, int d) {
    Node* p = new Node();
    p->data = d;
    p->prev = p->next = NULL;
    Node* a = l;
    if (l == NULL) {
        l = p;
        return;
    }
    while (a->next != NULL) {
        a = a->next;
    }
    a->next = p;
    p->prev = a;
}

void insert_at(DList& l, int d) {
    Node* p = new Node();
    p->data = d;
    p->prev = p->next = NULL;
    Node* a = l;
    if (l == NULL) {
        l = p;
        return;
    }
    p->next = a;
    a->prev = p;
    l = p;
}

int length(DList l) {
    Node* p = l;
    int len = 0;
    if (p == NULL) {
        return 0;
    }
    while (p) {
        p = p->next;
        len++;
    }
    return len;
}

Node* lastptr(DList l) {
    Node* p = l;
    if (!p) return NULL;
    while (p->next != NULL) {
        p = p->next;
    }
    return p;
}

int greater(DList l1, DList l2) {
    Node* a = l1;
    Node* b = l2;
    int j = 0;
    if (a->data > b->data) {
        return 1;
    } else if (a->data < b->data) {
        return 0;
    } else {
        while (a && b) {
            if (a->data > b->data) {
                return 1;
            } else if (a->data < b->data) {
                return 0;
            } else {
                j = 0;
            }
            a = a->next;
            b = b->next;
        }
        return j;
    }
}

int equal(DList l1, DList l2) {
    Node* a = l1;
    Node* b = l2;
    int l = length(l1);
    int m = length(l2);
    int ct1 = 0, ct2 = 0;
    while (a && (a->data == 0)) {
        ct1++;
        a = a->next;
    }
    while (b && b->data == 0) {
        ct2++;
        b = b->next;
    }
    while (a && b) {
        if (a->data == b->data) {
            ct1++;
            ct2++;
        }
        a = a->next;
        b = b->next;
    }
    return (ct1 == l && ct2 == m) ? 1 : 0;
}

void display(DList l, int dpos, ostream& os) {
    if (l == NULL) return;
    if (dpos == -1) {  // If no decimal point
        Node* p = l;
        while (p) {
            if (p->data != 0) break;
            p = p->next;
        }
        while (p) {
            os << p->data;
            p = p->next;
        }
        return;
    } else {
        int i = 0, k = 0, j = 0;
        Node* p = l;
        Node* q = l;
        while (q) {
            if (q->data == 0 && j < dpos) {
                j++;
                k = 1;
                q = q->next;
                continue;
            }
            if (q->data != 0 && j < dpos) {
                k = 0;
                break;
            } else break;
        }
        if (k == 0) {
            if (dpos == 1 && p->data == 0) {
                os << p->data;
                p = p->next;
                i++;
            } else {
                while (p && p->data == 0) {
                    dpos--;
                    p = p->next;
                }
            }
        }
        while (p && i < dpos) {
            os << p->data;
            p = p->next;
            i++;
        }
        q = p;
        i = 0;
        j = 0;
        while (q) {
            if (q->data != 0) i++;
            q = q->next;
        }
        if (i == 0) return;
        os << ".";
        while (p) {
            os << p->data;
            p = p->next;
        }
    }
}

void delete1(DList& l) {
    if (l == NULL) return;
    Node* p = l;
    Node* a = l;
    while (p) {
        a = p;
        p = p->next;
        delete a;
    }
    l = NULL;
}

void delete_at(DList& l) {
    if (l == NULL) return;
    Node* p = l;
    Node* a = p;
    if (!p->next) {
        delete p;
        l = NULL;
    } else {
        p->next->prev = NULL;
        l = p->next;
        delete a;
    }
}
