#include "../inc/stack.h"

stack::stack() {
    stack_top = nullptr;
}

stack::~stack(){
    while(stack_top) pop();
}

void stack::pop() {
    if(stack_top){
        stack_node* temp = stack_top;
        stack_top = stack_top->next;
        delete[] temp;
    }
}

void stack::push(struct value_date input) {
    auto to_push = new stack_node(input);
    to_push->next = stack_top;
    stack_top = to_push;
}

const struct value_date stack::top() const {
    if(stack_top) return stack_top->data;
    throw "empty";
}

stack &stack::operator=(const stack &RHS) {
    while(stack_top) pop();
    if(this != &RHS && RHS.stack_top)
    {
        stack_node* copy_temp = RHS.stack_top;
        auto this_temp = new stack_node(copy_temp->data);
        stack_top = this_temp;
        while(copy_temp->next){
            copy_temp = copy_temp->next;
            this_temp->next = new stack_node(copy_temp->data);
            this_temp = this_temp->next;
        }
    }
    return *this;
}

stack stack::operator+(const stack &RHS) const {
    stack* to_return = new stack();
    stack left = *this;
    stack right = RHS;
    stack_node* left_runner = stack_top;
    stack_node* right_runner = RHS.stack_top;
    while(left_runner || right_runner) {
        if(left_runner && !right_runner){
            while(left_runner){
                to_return->push(left_runner->data);
                left_runner = left_runner->next;
            }
        }
        else if(!left_runner && right_runner){
            while(right_runner){
                to_return->push(right_runner->data);
                right_runner = right_runner->next;
            }
        }
        else if(left_runner->data.date > right_runner->data.date){
            to_return->push(left_runner->data);
            left_runner = left_runner->next;
        }
        else{
            to_return->push(right_runner->data);
            right_runner = right_runner->next;
        }
    }
    return *to_return;
}

