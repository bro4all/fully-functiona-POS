#include "../inc/stack.h"
#include "iostream"
stack::stack() {
stack_top= nullptr;
}

stack::~stack() {
    while (stack_top) {
        stack_node *temp = stack_top->next;
        delete stack_top;
        stack_top = temp;
    }
}

void stack::pop() {
    {
        if(stack_top == nullptr) {
            throw "nothing to pop";
        }
        else
        {
            stack_node * old = top;
            top = top->next;
            count--;
            delete(old);
        }
    }
}

void stack::push(struct value_date input) {

}

const struct value_date stack::top() const {
    return value_date();
}

bool stack::empty() {
    return false;
}

stack &stack::operator=(const stack &RHS) {
    //return <#initializer#>;
}

stack stack::operator+(const stack &RHS) const {
    return stack();
}
