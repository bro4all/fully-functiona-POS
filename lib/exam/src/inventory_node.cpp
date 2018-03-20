#include "../inc/inventory_node.h"

inventory_node::inventory_node(int input_upc, std::string input_name, int input_count, int input_price, int date) {
    upc = input_upc;
    name = input_name;
    inventory_count = input_count;
    price = stack();

    struct value_date to_add = value_date();
    to_add.value = input_price;
    to_add.date = date;
    price.push(to_add);

    next = nullptr;
}

inventory_node::~inventory_node()=default;
