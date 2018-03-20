#ifndef CMPE126EXAM1_TUESDAY_STACK_NODE_H
#define CMPE126EXAM1_TUESDAY_STACK_NODE_H

struct value_date{
    int value;
    int date;
};

class stack_node {
public:
    stack_node *next;
    struct value_date data;

    explicit stack_node(value_date data) : data(data), next(nullptr){};
};

#endif