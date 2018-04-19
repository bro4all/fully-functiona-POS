#include "../inc/stack.h"
#include <string>
stack::stack()
{
    stack_top = nullptr;
}
stack::~stack()
{
    while (stack_top)
    {
        if(stack_top->next == nullptr)
        {
            stack_top = nullptr;
        }
        else
        {
            stack_node *temp = stack_top->next;
            delete stack_top;
            stack_top = temp;
        }
    }
}
void stack::pop()
{
    if (stack_top == nullptr)
        throw -1;
    if (stack_top->next == nullptr)
        stack_top = nullptr;
    else
    {
        stack_node *previous;
        stack_node *current = stack_top;
        while (current->next != nullptr)
        {
            previous = current;
            current = current->next;
        }
        previous ->next = nullptr;
        delete current;
    }
}
void stack::push(struct value_date input)
{
    stack_node *temp = new stack_node(input);
    if (stack_top == nullptr)
    {
        stack_top = temp;
    }
    else
    {
        stack_node *current = stack_top;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = temp;
        current = current->next;
    }
}
const struct value_date stack::top() const
{
    if (stack_top == nullptr)
        throw -1;
    else
    {
        stack_node *current = stack_top;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        return current->data;
    }
}
bool stack::empty()
{
    return (stack_top == nullptr);
}
stack &stack::operator=(const stack &RHS)
{
    if (RHS.stack_top == nullptr)
        stack_top = nullptr;
    else
    {
        stack_node *current = RHS.stack_top;
        while (current ->next != nullptr)
        {
            this->push(current->data);
            current = current->next;
        }
        this->push(current->data);
    }
    return *this;
}
stack stack::operator+(const stack &RHS) const {
    stack newplus;
    stack_node *a = stack_top;
    stack_node *b = RHS.stack_top;
    stack_node *top;
    while(a!= nullptr && b!= nullptr){
        if(a->data.date >= b->data.date){
            newplus.push(b->data);
            b = b->next;
        }
        else {
            newplus.push(a->data);
            a = a->next;
        }
    }
    while(a != nullptr){
        newplus.push(a->data);
        a = a->next;
    }
    while(b != nullptr){
        newplus.push(b->data);
        b = b->next;
    }
    return newplus;
}