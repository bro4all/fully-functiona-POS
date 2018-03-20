#ifndef CMPE126EXAM1_TUESDAY_INVENTORY_H
#define CMPE126EXAM1_TUESDAY_INVENTORY_H

#include "inventory_node.h"
#include <map>
#include <vector>

class inventory{
    inventory_node* head;

    static std::map<unsigned, bool> upc_generator;
    static unsigned get_unique_upc();
    static void remove_upc(int upc);

public:
    inventory();
    ~inventory();

    void add_sku(std::string name, int price, int inventory, int date);
    void remove_sku(int upc);

    std::vector<unsigned int> get_upc(std::string name);
    int get_price(int upc);
    int get_inventory(int upc);
    int get_name(int upc);

    int get_lowest_price(int upc);
    int get_highest_price(int upc);

    void adjust_price(int upc, int price, int date);
    void adjust_inventory(int upc, int inventory);

    void sort_by_lowest_price();
};

#endif
