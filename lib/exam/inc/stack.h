#ifndef CMPE126EXAM1_TUESDAY_LINKED_LIST_H
#define CMPE126EXAM1_TUESDAY_LINKED_LIST_H

struct value_date{
    int value;
    int date;
};

class node_stack {
public:
    node_stack *next;
    struct value_date data;
    explicit node_stack(value_date data) : data(data), next(nullptr){};
};


class stack{
    node_stack* head;

public:
    stack();
    ~stack();

    void pop();
    void push(struct value_date input);
    const struct value_date top() const;
    bool empty();

    stack& operator=(const stack& RHS);
    stack merge(const stack& RHS) const;
};

#endif
