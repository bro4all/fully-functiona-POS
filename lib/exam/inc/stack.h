#ifndef CMPE126EXAM1_TUESDAY_LINKED_LIST_H
#define CMPE126EXAM1_TUESDAY_LINKED_LIST_H

#include "stack_node.h"

class stack{
    stack_node* stack_top;

public:
    stack();
    ~stack();

    void pop();
    void push(struct value_date input);
    const struct value_date top() const;

    stack& operator=(const stack& RHS);
    stack operator+(const stack& RHS) const;
};

#endif
