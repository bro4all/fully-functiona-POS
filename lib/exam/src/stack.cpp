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
    stack_node *temp;
    if(stack_top==NULL)
    {
        throw "stack is empty";
    }
    temp=stack_top;
    stack_top=stack_top->next;

    delete temp;

}

void stack::push(struct value_date input) {
    stack_node * nodeIn=new stack_node;
    if(stack_top == NULL) {
        stack_node = nodeIn;
    }else {
        nodeIn = stack_top;
        stack_node= nodeIn;
    }
}

const struct value_date stack::top() const {
    return value_date();
}

bool stack::empty() {
    if(stack_top == nullptr){
        return true;
    }
    else
        return false;
}

stack &stack::operator=(const stack &RHS) {
    //return <#initializer#>;
}

stack stack::operator+(const stack &RHS) const {
    return stack();
}
