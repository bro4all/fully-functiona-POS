#include "../inc/inventory.h"
//TODO: Write UPC Functions
int inventory::reserve_upc() {
    return 0;
}

void inventory::release_upc(int upc) {

}

bool inventory::valid_upc(int input_upc) {

}

inventory::inventory(){
    // Initialize UPCs
    //TODO: initialize the UPC Generator

    head = nullptr;
}

inventory::~inventory() {
    while(head){
        inventory_node* temp = head;
        delete head;
        head = temp;
    }
}

void inventory::add_sku(std::string name, int price, int inventory, int date) {
    unsigned unique_upc = reserve_upc();
    inventory_node *temp = new inventory_node(unique_upc, name, inventory, price, date);
    temp->next = head;
    head = temp;

}

void inventory::remove_sku(int input_upc) {
    if(valid_upc) {
        if (head->upc == input_upc) {
            inventory_node *temp = head;
            head = head->next;
            delete temp;
            release_upc(input_upc);
        }
        else {
            for (inventory_node *current = head; current->next; current = current->next) {
                if (current->next->upc == input_upc) {
                    inventory_node *temp = current->next;
                    current->next = current->next->next;
                    delete temp;
                    release_upc(input_upc);
                }
            }
        }
    }
    throw "not found";
}

std::vector<int> inventory::get_upc(std::string input_name) {
    std::vector upcs_to_return;
    for(inventory_node* current = head; current; current = current->next){
        if(current->name == input_name) upcs_to_return.push_back(current->upc);
    }
    return upcs_to_return;
}

int inventory::get_price(int input_upc) {
    for(inventory_node* current = head; current; current = current->next){
        if(current->upc == input_upc) return current->price.top().value;
    }
    throw "not found";
}

int inventory::get_inventory(int input_upc) {
    for(inventory_node* current = head; current; current = current->next){
        if(current->upc == input_upc) return current->inventory_count;
    }
    throw "not found";
}

std::string inventory::get_name(int input_upc) {
    for(inventory_node* current = head; current; current = current->next){
        if(current->upc == input_upc) return current->name;
    }
    throw "not found";
}

int inventory::get_lowest_price(int input_upc) {
    for(inventory_node* current = head; current; current = current->next){
        if(current->upc == input_upc){
            stack pricing_history = current->price;
            int lowest_price = pricing_history.top().value;
            while(!pricing_history.empty()){
                if(pricing_history.top().value<lowest_price) lowest_price = pricing_history.top().value;
                pricing_history.pop();
            }
            return lowest_price;
        }
    }
    throw "not found";
}

int inventory::get_highest_price(int input_upc) {
    for(inventory_node* current = head; current; current = current->next){
        if(current->upc == input_upc){
            stack pricing_history = current->price;
            int highest_price = pricing_history.top().value;
            while(!pricing_history.empty()){
                if(pricing_history.top().value>highest_price) highest_price = pricing_history.top().value;
                pricing_history.pop();
            }
            return highest_price;
        }
    }
    throw "not found";
}

void inventory::adjust_price(int input_upc, int new_price, int new_date) {
    void inventory::adjust_inventory(int input_upc, int new_inventory) {
        for(inventory_node* current = head; current; current = current->next){
            if(current->upc == input_upc){
                value_date new_pricing = value_date();
                new_pricing.value = new_price;
                new_pricing.date = new_date;
                current->price.push(new_pricing);
            }
        }
        throw "not found";
    }
}

void inventory::adjust_inventory(int input_upc, int new_inventory) {
    for(inventory_node* current = head; current; current = current->next){
        if(current->upc == input_upc) current->inventory_count = new_inventory;
    }
    throw "not found";
}

void inventory::sort_by_lowest_price() {
    //TODO: Double Sort Function
}
