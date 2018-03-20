# Lab Exam 1 #
###### Tuesday, 20 March 2018 ######

For this exam you will be implementing a basic inventory system using linked lists and stacks. The framework and tests for the exam have been provided for you in this repository. You will have 3 hour to implement all of the functions and verify they work using the tests provided to you. These are the tests you lab exam will be graded on. 

**Submissions that don't compile will receive a zero.**

**Submissions that have `using namespace std` in them will receive a zero.**

## Instructions ##

The framework you have been given has everything you need to finish this exam. You will need to implement all of the functions that haven't been implemented yet and verify that they work using the provided tests. 

Your inventory system will be stored using a singly linked list. This means that adding an item to the inventory should be done in constant time. An abstract representation of inventory can be seen in the image below.

![Inventory](https://i.imgur.com/jBjNMID.png)

Each inventory item will have a unique UPC, a name, the current inventory price, and a stack of all of the previous prices a long with their date. This means that your inventory node will have a stack inside of it. An abstract representation of the stack can be seen in the image below.

![Stack](https://i.imgur.com/5mP0DE6.png)

Because the stack holds on to two items, the price and the date, we need to encapsulate the input and output into a struct named `value_date`. 

### Recommended order for completion ###
* Implement `stack_node` and verify it works
* Implement `stack` and verify it works
* Implement `inventory_node` and verify it works
* Implement `inventory` and verify it works

### Advice ###
This exam may look overwhelming, but it really shouldn't be. Take a minute and count how many simply getter's and setters you have been tasked with implementing. Most of those will be copy and paste with a line or two changed. 

We have provided you with all of the tests you need to be successful on this exam. We will not be changing out these tests when we grade your exam. You have all of the answers to this exam, you just need to write the code to make the answers work.  

Remember, this is open every thing other than a person answering your questions. You can use all of the resources available to you to finish this exam. Look at your past labs for ideas on how to implement these functions. 

While you haven't seen a linked list implemented like this before, where you don't have all of the standard functions, it functions exactly the same. 

## Class Functions ##

### Stack ###
`stack()`: Default constructor for a stack object. Takes in no parameters.

`~stack()`: Deconstructor for stack object. Takes in no parameters. 

`void pop()`: Remove the top item from the stack. Takes in no parameters. No return value.

`void push(struct value_date)`: Pushes a new `stack_node` that contains the structure `value_date` onto the stack. Takes in a `value_date` struct. No return value.

`struct value_date top()`: Retrieves the `value_date` struct that is located at in the `stack_node` at the top of the stack. Takes in no parameters. Returns a `value_date` struct. If there is nothing in the stack, return an empty `value_date`.

`stack& operator=(const stack& RHS)`: Creates a deep copy of the reference `stack` passed into the function on the right side of the `=` operator. Takes in a `stack&` as a parameter. Returns a `stack&`.

`stack operator+(const stack& RHS) const`: Create a deep copy of the current `stack` and the passed in `stack` and merge the two stacks together in order. You will be merging them according to the date. Takes in a `stack&` as a parameter. Returns a `stack`.

### Inventory Node ###

`inventory_node(int upc, std::string name, int count, int price)`: Constructor for an `inventory_node` that takes in all of the necessary values to create an inventory node. You will need to create the price `stack` from the input `int` price.

`~inventory_node()`: Deconstructor for an `inventory_node` that fully deconstructs all of the elements within it. 

### Inventory ###

`inventory()`: Constructor for an empty `inventory` data structure.

`~inventory()`: Deconstructor to properly deconstruct an `inventory`.

`void add_sku(std::string name, int price, int inventory_count, int date)`: Add an item to the `inventory` given all of the necessary information for an item. You will need to get a new UPC for every SKU you add to the `inventory`. There can be multiple items in the inventory with the same name, price, and inventory amount; each of them should have a unique UPC.

`void remove_sku(int upc)`: Remove an item from the `inventory` given it's UPC. If there is no item located in the `inventory` with that UPC, do nothing.  

`std::vector<unsigned> get_upc(std::string name)`: Retrieve a `vector` containing all of the UPC's that match the provided item name. Matches must be perfect. You can use standard `string` comparison. If there is no item by that name in the `inventory`, return an empty `vector`. 

`int get_price(int upc)`: Given a UPC, retrieve the current price of that item. If the UPC doesn't exist throw an error.

`int get_inventory(int upc)`: Given a UPC, retrieve the inventory count of that item. If the UPC doesn't exist throw an error.

`int get_name(int upc)`: Given a UPC, retrieve the name of that item. If the UPC doesn't exist throw an error.

`int get_lowest_price(int upc)`: Given a UPC, retrieve the lowest historical price of that item. If the UPC doesn't exist throw an error.

`int get_highest_price(int upc)`: Given a UPC, retrieve the highest historical price of that item. If the UPC doesn't exist throw an error.

`void adjust_price(int upc, int price, int date)`: Given a UPC, price, and date, update the price of the UPC. Remember price is stored in a stack; you need to add a new item to the stack with the new price and date. If the UPC doesn't exist, throw an error. 

`void adjust_inventory(int upc, int inventory_count)`: Given a UPC and inventory count, update the inventory count. If the UPC doesn't exist, throw an error. 

`void sort_by_lowest_price()`: Sort the inventory by lowest price, and then by inventory. You can use any sorting algorithm you have learned.


## Hints ##
* Every UPC is unique. When you find the one you are looking for, you are done looking.
* When in doubt, look at `exam_tests.cpp` for the expected behavior of a function.
* Read the readme before asking a question. It has probably already been answered. 