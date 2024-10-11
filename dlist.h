#ifndef DLIST_H_INCLUDED
#define DLIST_H_INCLUDED

#include <iostream> // For ostream in display function

struct Node {
    int data;
    Node* prev;
    Node* next;
};

typedef Node* DList;

void init(DList& l);
void append(DList& l, int data);
void insert_at(DList& l, int data);
void display(DList l, int dpos, std::ostream& os); // Using ostream for output
int length(DList l);
Node* lastptr(DList l);
int equal(DList l1, DList l2);
int greater(DList l1, DList l2);
void delete1(DList& l);
void delete_at(DList& l);

#endif // DLIST_H_INCLUDED
