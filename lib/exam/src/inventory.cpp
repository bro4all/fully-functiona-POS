#include "../inc/inventory.h"

unsigned inventory::get_unique_upc() {
    return 0;
}

void inventory::remove_upc(int upc) {

}

inventory::inventory() {

}

inventory::~inventory() {

}

void inventory::add_sku(std::string name, int price, int inventory, int date) {

}

void inventory::remove_sku(int upc) {

}

unsigned inventory::get_upc(std::string name) {
    return 0;
}

int inventory::get_price(int upc) {
    return 0;
}

int inventory::get_inventory(int upc) {
    return 0;
}

int inventory::get_name(int upc) {
    return 0;
}

int inventory::get_lowest_price(int upc) {
    return 0;
}

int inventory::get_highest_price(int upc) {
    return 0;
}

void inventory::adjust_price(int upc, int price, int date) {

}

void inventory::adjust_inventory(int upc, int inventory) {

}

void inventory::sort_by_lowest_price() {

}
