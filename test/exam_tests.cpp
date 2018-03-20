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

TEST(InventoryNodeTest, constructorTest){
    inventory_node test_node = inventory_node(1, "2", 3, 4, 5);
    EXPECT_EQ(1, test_node.upc);
    EXPECT_EQ("2", test_node.name);
    EXPECT_EQ(3, test_node.inventory_count);
    EXPECT_EQ(4, test_node.price.top().value);
    EXPECT_EQ(5, test_node.price.top().date);
    EXPECT_EQ(nullptr, test_node.next);
}

TEST(InventoryNodeTest, deconstructorTest){
    inventory_node* test_node = new inventory_node(1, "2", 3, 4, 5);
    delete test_node;
}


class InventoryFixture : public ::testing::Test {

protected:
    virtual void TearDown() {

    }

    virtual void SetUp() {
        test_inventory = inventory();
        // generate 100 random items
        srand(2018);
        for(int i = 0; i < 200; i++) {
            srand((rand()*i)%10000);
            int new_price = (rand())% 100;
            int new_count = (rand())% 1000;
            int new_date = 1521581400 + ((rand() % 31557600) - 31557600);
            std::string new_name = "Item";
            new_name += std::to_string(i);
            test_inventory.add_sku(new_name, new_price, new_count, new_date);
        }
        empty_inventory = inventory();
    }


public:
    inventory test_inventory;
    inventory empty_inventory;
};

TEST(crashTest, inventoryConstructorTest) {
    // Check to see if things crash during basic construction/deconstruction
    inventory crash_test = inventory();
    inventory* new_crash_test = new inventory();
    delete new_crash_test;
}

TEST(crashTest, inventoryAddSKU){
    inventory test_inventory = inventory();
    test_inventory.add_sku("test item", 42, 2000, 946713600);
}

TEST(crashTest, inventoryAccessSKU){
    inventory test_inventory = inventory();
    test_inventory.add_sku("test item", 42, 2000, 946713600);
    int item_code = test_inventory.get_upc(std::string("test item"))[0];

    test_inventory.get_inventory(item_code);
    test_inventory.get_price(item_code);
    test_inventory.get_name(item_code);
    test_inventory.get_lowest_price(item_code);
    test_inventory.get_highest_price(item_code);
}

TEST(crashTest, inventoryAdjustSKU){
    inventory test_inventory = inventory();
    test_inventory.add_sku("test item", 42, 2000, 946713600);
    std::vector<int> item_codes;

    item_codes = test_inventory.get_upc(std::string("test item"));
    int item_code = item_codes[0];
    test_inventory.adjust_inventory(item_code, 2001);
    test_inventory.adjust_price(item_code, 17, 1521581400);
}

TEST(crashTest, inventorySort){
    inventory test_inventory = inventory();
    test_inventory.add_sku("test item", 42, 2000, 946713600);
    test_inventory.add_sku("test item2", 420, 2001, 1521581400);
    test_inventory.sort_by_lowest_price();
}

TEST(crashTest, inventoryRemoveSKU){
    inventory test_inventory = inventory();
    test_inventory.add_sku("test item", 42, 2000, 946713600);
    test_inventory.add_sku("test item2", 420, 2001, 1521581400);
    int item_code = test_inventory.get_upc(std::string("test item"))[0];
    test_inventory.remove_sku(item_code);
}

TEST_F(InventoryFixture, AccessSKU){
    test_inventory.add_sku("test item", 42, 2000, 946713600);
    int item_count = 0, item_price = 0;
    std::vector<int> item_codes;
    std::string item_name;

    EXPECT_NO_THROW(item_codes = test_inventory.get_upc(std::string("test item")));
    EXPECT_EQ(1,item_codes.size());
    int item_code = item_codes[0];

    EXPECT_NO_THROW(item_count = test_inventory.get_inventory(item_code));
    EXPECT_EQ(2000, item_count);
    EXPECT_NO_THROW(item_price = test_inventory.get_price(item_code));
    EXPECT_EQ(42, item_price);
    EXPECT_NO_THROW(item_name = test_inventory.get_name(item_code));
    EXPECT_EQ("test item", item_name);

    for(int i = 0; i < 25; i++){
        int item_to_adjust = rand()%100;
        std::string item_name_to_adjust = "Item" + std::to_string(item_to_adjust);
        std::vector<int> item_upc_vec;
        EXPECT_NO_THROW(item_upc_vec = test_inventory.get_upc(item_name_to_adjust));
        EXPECT_EQ(1, item_upc_vec.size());
        int item_upc = item_upc_vec[0];

        int price;
        EXPECT_NO_THROW(price = test_inventory.get_price(item_upc));
        EXPECT_NO_THROW(price = test_inventory.get_price(item_upc));
        EXPECT_NO_THROW(price = test_inventory.get_price(item_upc));
        EXPECT_NO_THROW(price = test_inventory.get_price(item_upc));
        EXPECT_NO_THROW(price = test_inventory.get_price(item_upc));

        int count;
        EXPECT_NO_THROW(count = test_inventory.get_inventory(item_upc));
        EXPECT_NO_THROW(count = test_inventory.get_inventory(item_upc));
        EXPECT_NO_THROW(count = test_inventory.get_inventory(item_upc));
        EXPECT_NO_THROW(count = test_inventory.get_inventory(item_upc));
        EXPECT_NO_THROW(count = test_inventory.get_inventory(item_upc));
    }
}

TEST_F(InventoryFixture, AdjustSKU){
    for(int i = 0; i < 25; i++){
        int item_to_adjust = rand()%100;
        std::string item_name_to_adjust = "Item" + std::to_string(item_to_adjust);
        std::vector<int> item_upc_vec;
        EXPECT_NO_THROW(item_upc_vec = test_inventory.get_upc(item_name_to_adjust));
        EXPECT_EQ(1, item_upc_vec.size());
        int item_upc = item_upc_vec[0];
        int price;
        EXPECT_NO_THROW(price = test_inventory.get_price(item_upc));
        EXPECT_NO_THROW(test_inventory.adjust_price(item_upc, price+i*2, 1337));
        int new_price;
        EXPECT_NO_THROW(new_price = test_inventory.get_price(item_upc));
        EXPECT_EQ(price+i*2, new_price);
    }

    for(int i = 0; i < 25; i++){
        int item_to_adjust = rand()%100;
        std::string item_name_to_adjust = "Item" + std::to_string(item_to_adjust);
        std::vector<int> item_upc_vec;
        EXPECT_NO_THROW(item_upc_vec = test_inventory.get_upc(item_name_to_adjust));
        EXPECT_EQ(1, item_upc_vec.size());
        int item_upc = item_upc_vec[0];
        int count;
        EXPECT_NO_THROW(count = test_inventory.get_inventory(item_upc));
        EXPECT_NO_THROW(test_inventory.adjust_inventory(item_upc, count*i));
        int new_count;
        EXPECT_NO_THROW(new_count = test_inventory.get_inventory(item_upc));
        EXPECT_EQ(count*i, new_count);
    }

}

TEST_F(InventoryFixture, RemoveSKU){
    inventory test_inventory = inventory();
    test_inventory.add_sku("test item", 42, 2000, 946713600);
    test_inventory.add_sku("test item2", 420, 2001, 1521581400);
    int item_code = test_inventory.get_upc(std::string("test item"))[0];
    test_inventory.remove_sku(item_code);
}

TEST_F(InventoryFixture, EmptyTests){
    std::vector<int> item_upc_vec;
    EXPECT_NO_THROW(item_upc_vec = empty_inventory.get_upc("Empty Test"));
    EXPECT_EQ(0, item_upc_vec.size());
    int price = 0;
    EXPECT_ANY_THROW(price = empty_inventory.get_price(0));
    EXPECT_EQ(0, price);

    int inventory = 0;
    EXPECT_ANY_THROW(price = empty_inventory.get_inventory(0));
    EXPECT_EQ(0, inventory);

    std::string name = "";
    EXPECT_ANY_THROW(name = empty_inventory.get_name(0));
    EXPECT_EQ("", name);

    int highest_price = 0;
    EXPECT_ANY_THROW(price = empty_inventory.get_highest_price(0));
    EXPECT_EQ(0, highest_price);

    int lowest_price = 0;
    EXPECT_ANY_THROW(price = empty_inventory.get_lowest_price(0));
    EXPECT_EQ(0, lowest_price);

    price = rand()%100;
    EXPECT_ANY_THROW(empty_inventory.adjust_price(0, price, 0));

    inventory = rand()%100;
    EXPECT_ANY_THROW(empty_inventory.adjust_inventory(0, inventory));

    EXPECT_ANY_THROW(empty_inventory.remove_sku(1));
}

TEST_F(InventoryFixture, InvalidUPCTests){
    for(int i = 0; i<100; i++) {
        int upc_value = rand()%10000 + rand()%100*i + i;
        int price = 0;
        EXPECT_ANY_THROW(price = test_inventory.get_price(upc_value));
        EXPECT_EQ(0, price);

        int inventory = 0;
        EXPECT_ANY_THROW(price = test_inventory.get_inventory(upc_value));
        EXPECT_EQ(0, inventory);

        std::string name = "";
        EXPECT_ANY_THROW(name = test_inventory.get_name(upc_value));
        EXPECT_EQ("", name);

        int highest_price = 0;
        EXPECT_ANY_THROW(price = test_inventory.get_highest_price(upc_value));
        EXPECT_EQ(0, highest_price);

        int lowest_price = 0;
        EXPECT_ANY_THROW(price = test_inventory.get_lowest_price(upc_value));
        EXPECT_EQ(0, lowest_price);

        price = rand() % 100;
        EXPECT_ANY_THROW(test_inventory.adjust_price(0, price, upc_value));

        inventory = rand() % 100;
        EXPECT_ANY_THROW(test_inventory.adjust_inventory(upc_value, inventory));

        EXPECT_ANY_THROW(test_inventory.remove_sku(upc_value));
    }
}

TEST_F(InventoryFixture, HighLowPriceTests){
    for(int item_to_adjust = 20; item_to_adjust<30;item_to_adjust++) {
        std::string item_name_to_adjust = "Item" + std::to_string(item_to_adjust);
        std::vector<int> item_upc_vec;
        EXPECT_NO_THROW(item_upc_vec = test_inventory.get_upc(item_name_to_adjust));
        EXPECT_EQ(1, item_upc_vec.size());
        int item_upc = item_upc_vec[0];

        int low_value = 0;
        int high_value = 0;
        EXPECT_NO_THROW(low_value = test_inventory.get_price(item_upc));
        EXPECT_NO_THROW(high_value = test_inventory.get_price(item_upc));
        for (int i = 5; i < 25; i++) {
            int price;
            EXPECT_NO_THROW(price = test_inventory.get_price(item_upc));
            price = (price + i*rand()%127)% 100 - 100;
            if(price < low_value) low_value = price;
            if(price > high_value) high_value = price;
            EXPECT_NO_THROW(test_inventory.adjust_price(item_upc, price, 1521581400 + 3600*i));
        }
        int calculated_low_value = 0;
        int calculated_high_value = 0;
        EXPECT_NO_THROW(calculated_high_value = test_inventory.get_highest_price(item_upc));
        EXPECT_NO_THROW(calculated_low_value = test_inventory.get_lowest_price(item_upc));

        EXPECT_EQ(high_value, calculated_high_value);
        EXPECT_EQ(low_value, calculated_low_value);
    }
}

TEST_F(InventoryFixture, SortTests){
    test_inventory.sort_by_lowest_price();
    inventory_node* runner = test_inventory.get_head();
    while(runner && runner->next) {
        int price_a = runner->price.top().value;
        int price_b = runner->next->price.top().value;
        EXPECT_LE(price_a, price_b);
        if(price_a == price_b){
            int inv_a = runner->inventory_count;
            int inv_b = runner->next->inventory_count;
            EXPECT_LE(inv_a,inv_b);
        }
        runner = runner->next;
    }
}