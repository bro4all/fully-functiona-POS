#include "../inc/inventory_node.h"

inventory_node::inventory_node(int input_upc, std::string input_name, int input_count, int input_price, int date) {
    upc = input_upc;
    name = input_name;
    inventory_count = input_count;
    value_date a;
    a.value = input_price;
    a.date = date;
    price.push(a);
    next = nullptr;
    
}

inventory_node::~inventory_node()=default;

