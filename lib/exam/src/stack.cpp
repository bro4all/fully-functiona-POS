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

bool stack::empty() {
    return stack_top == nullptr;
}

stack stack::operator+(const stack &RHS) const {
    stack* to_return = new stack();
    stack_node* left_runner = stack_top;
    stack_node* right_runner = RHS.stack_top;
    stack_node* return_runner = nullptr;
    while(left_runner || right_runner) {
        if(!return_runner && (left_runner && right_runner)){
            if(left_runner->data.date > right_runner->data.date){
                return_runner = new stack_node(left_runner->data);
                left_runner = left_runner->next;
            }
            else{
                return_runner = new stack_node(right_runner->data);
                right_runner = right_runner->next;
            }
            to_return->stack_top = return_runner;
        }
        else if(!return_runner && (left_runner && !right_runner)){
//            to_return->stack_top = return_runner;
//            return_runner = new stack_node(left_runner->data);
//            left_runner = left_runner->next;
//            to_return->stack_top = return_runner;
//            while(left_runner){
//                return_runner->next = new stack_node(left_runner->data);
//                left_runner = left_runner->next;
//                return_runner = return_runner->next;
//            }
            *to_return = *this;
            break;
        }
        else if(!return_runner && (!left_runner && right_runner)){
//            to_return->stack_top = return_runner;
//            return_runner = new stack_node(right_runner->data);
//            right_runner = right_runner->next;
//            to_return->stack_top = return_runner;
//            while(right_runner){
//                return_runner->next = new stack_node(right_runner->data);
//                right_runner = right_runner->next;
//                return_runner = return_runner->next;
//            }
            *to_return = RHS;
            break;
        }
        else if(left_runner && !right_runner){
            while(left_runner){
                return_runner->next = new stack_node(left_runner->data);
                left_runner = left_runner->next;
                return_runner = return_runner->next;
            }
        }
        else if(!left_runner && right_runner){
            while(right_runner){
                return_runner->next = new stack_node(right_runner->data);
                right_runner = right_runner->next;
                return_runner = return_runner->next;
            }
        }
        else if(left_runner->data.date > right_runner->data.date){
            return_runner->next = new stack_node(left_runner->data);
            left_runner = left_runner->next;
            return_runner = return_runner->next;
        }
        else{
            return_runner->next = new stack_node(right_runner->data);
            right_runner = right_runner->next;
            return_runner = return_runner->next;
        }
    }
    return *to_return;
}

