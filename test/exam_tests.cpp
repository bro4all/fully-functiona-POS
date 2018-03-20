#include "gtest/gtest.h"
#include "inventory.h"

class StackFixture : public ::testing::Test {

protected:
    virtual void TearDown() {
        delete stack1;
        delete stack2;
    }

    virtual void SetUp() {
        stack1 = new stack();
        stack2 = new stack();
    }


public:
    stack *stack1, *stack2;
};

TEST(crashTest, stackConstructorTest) {
    // Check to see if things crash during basic construction/deconstruction
    stack crash_test = stack();
    stack* new_crash_test = new stack();
    delete new_crash_test;
}

TEST_F(StackFixture, stackBasicFunctions){
    // push data to the stacks
    value_date to_add = value_date();
    for(int i = 1; i < 100; i++) {
        to_add.date = i;
        to_add.value = i;
        stack1->push(to_add);
    }
    for(int i = 1; i < 100; i++) {
        to_add.date = 3*i;
        to_add.value = -i;
        stack2->push(to_add);
    }

    // Check for throws when reading the top value
    // Also check to see if the output value is the same
    // as what was put in
    value_date top_received;
    for(int i = 99; i>0; i--){
        EXPECT_NO_THROW(stack1->top());
        top_received = stack1->top();
        EXPECT_EQ(i, top_received.value);
        EXPECT_EQ(i, top_received.date);
        stack1->pop();
    }
    // Check to see what happens when top is called multiple
    // times on an empty stack
    for(int i = 0; i < 20; i++) EXPECT_ANY_THROW(stack1->top());

    // Pop off the first 75 items from the stack and verify
    // they are correct
    for(int i = 99; i > 25; i--){
        top_received = stack2->top();
        EXPECT_EQ(-i, top_received.value);
        EXPECT_EQ(3*i, top_received.date);
        stack2->pop();
    }
    // Push some more values to the not empty stack
    for(int i = 1; i < 25; i++) {
        to_add.date = (11*i) % 41;
        to_add.value = -i*-i;
        stack2->push(to_add);
    }
    // Pop the values off
    for(int i = 24; i > 0; i--){
        top_received = stack2->top();
        EXPECT_EQ(-i*-i, top_received.value);
        EXPECT_EQ((11*i) % 41, top_received.date);
        stack2->pop();
    }
    for(int i = 25; i > 0; i--){
        top_received = stack2->top();
        EXPECT_EQ(-i, top_received.value);
        EXPECT_EQ(3*i, top_received.date);
        stack2->pop();
    }
    // Check for multiple empty top calls again
    for(int i = 0; i < 20; i++) EXPECT_ANY_THROW(stack2->top());


    // Destructor check
    stack* stack4 = new stack();
    to_add = value_date();
    for(int i = 1; i < 100; i++) {
        to_add.date = i;
        to_add.value = i;
        stack4->push(to_add);
    }
    delete stack4;

}

TEST_F(StackFixture, stackOperatorEqualsOverload) {
    // Check to make sure empty stacks are properly handled
    *stack1 = *stack2;

    // Fill the stack1 with data
    value_date to_add = value_date();
    to_add.date = 17;
    to_add.value = 42;
    stack1->push(to_add);
    for (int i = 8; i < 1008; i++) {
        to_add.date = (i * stack1->top().date) % (stack1->top().value);
        to_add.value = i + stack1->top().value;
        stack1->push(to_add);
    }

    // Copy stack1 into stack2
    *stack2 = *stack1;

    // Check to see if it was properly copied
    for(int i = 0; i < 500; i++) {
        EXPECT_EQ(stack1->top().value, stack2->top().value);
        EXPECT_EQ(stack1->top().date, stack2->top().date);
        stack1->pop();
        stack2->pop();
    }

    // Verify that the data was deep copied
    value_date top_2_original;
    EXPECT_EQ(stack1->top().value, stack2->top().value);
    EXPECT_EQ(stack1->top().date, stack2->top().date);
    top_2_original = stack2->top();
    stack1->pop();
    for(int i = 0; i < 500; i++){
        EXPECT_NO_THROW(stack1->top());
        EXPECT_NE(stack1->top().value, stack2->top().value);
        EXPECT_NE(stack1->top().date, stack2->top().date);
        EXPECT_EQ(top_2_original.value, stack2->top().value);
        EXPECT_EQ(top_2_original.date, stack2->top().date);
        stack1->pop();
    }

    //Check empty top values on stack1
    for(int i = 0; i < 20; i++) EXPECT_ANY_THROW(stack1->top());

    //Check for proper handling of empty stacks
    *stack2 = *stack1;
    for(int i = 0; i < 20; i++){
        EXPECT_ANY_THROW(stack1->top());
        EXPECT_ANY_THROW(stack2->top());
    }
}

TEST_F(StackFixture, stackOperatorPlusOverload) {
    // Fill up 2 stacks
    value_date to_add = value_date();
    to_add.date = 1;
    to_add.value = 1;
    for (int i = 1; i < 1000; i+=2) {
        to_add.date = i;
        stack1->push(to_add);
    }
    to_add.date = 2;
    to_add.value = 2;
    for (int i = 0; i < 1000; i+=2) {
        to_add.date = i;
        stack2->push(to_add);
    }

    // Do the merge operation
    stack stack3 = *stack1 + *stack2;

    // Check simple merge operation
    for (int i = 1; i<1000; i++) {
        int higher = stack3.top().date;
        stack3.pop();
        int lower = stack3.top().date;
        EXPECT_LT(lower, higher);
    }
    // refill 2 stacks with different values
    stack1 = new stack();
    stack2 = new stack();
    to_add = value_date();
    to_add.date = 2;
    to_add.value = 1;
    stack1->push(to_add);
    for (int i = 1; i <= 10; i++) {
        to_add.date = 2 * stack1->top().date;
        to_add.value = i;
        stack1->push(to_add);
    }
    to_add.date = 1000;
    to_add.value = 2;
    stack2->push(to_add);
    for (int i = 1; i <= 10; i++) {
        to_add.date = 2* i + stack2->top().date;
        to_add.value = -i;
        stack2->push(to_add);
    }

    // Do the merge operation
    stack3 = *stack1 + *stack2;

    // Check simple merge operation
    for (int i = 1; i<20; i++) {
        int higher = stack3.top().date;
        stack3.pop();
        int lower = stack3.top().date;
        EXPECT_LT(lower, higher);
    }

    // check simple empty merge
    stack3 = stack() + stack();
    EXPECT_ANY_THROW(stack3.top());

    // Check 1 sided empty merge
    stack3 = *stack1 + stack();
    EXPECT_NO_THROW(stack3.top());
    stack3 = stack() + *stack2;
    EXPECT_NO_THROW(stack3.top());
}

class NodeFixture : public ::testing::Test {

protected:
    virtual void TearDown() {

    }

    virtual void SetUp() {

    }


public:

};

