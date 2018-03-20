#include "../inc/inventory.h"
#include <random>
int inventory::reserve_upc() {
    srand(42);
    auto random_upc_location = int(rand()%upc_generator.size());
    auto a = upc_generator.begin();
    for(auto a = upc_generator.begin(); --random_upc_location != 0; a++);
    while(!a->second && a != upc_generator.end()) a++;
    a->second = false;
    return a->first;
}

void inventory::release_upc(int input_upc) {
    auto val =  upc_generator.find(input_upc);
    if(val->first == input_upc && val->second == false){
        val->second = true;
        return;
    }
    else throw "UPC not valid";
}

bool inventory::valid_upc(int input_upc) {
    if(input_upc == 0) return false;
    auto val = inventory::upc_generator.find(input_upc);
    return val->first == input_upc;
}

void inventory::initialize_upc() {
    srand(17); // Initial seed
    for(int i = 1; i< 1000; i++) {
        int unique_upc = 1000000 + rand() % 9000000;
        inventory::upc_generator.insert(std::pair<int, bool>(unique_upc, true));
    }
}

inventory::inventory(){
    // Initialize UPCs
    initialize_upc();

    head = nullptr;
}

inventory::~inventory() {
    while(head){
        inventory_node* temp = head->next;
        delete head;
        head = temp;
    }
}

void inventory::add_sku(std::string name, int price, int inventory, int date) {
    int unique_upc = reserve_upc();
    inventory_node *temp = new inventory_node(unique_upc, name, inventory, price, date);
    temp->next = head;
    head = temp;
}

void inventory::remove_sku(int input_upc) {
    if(valid_upc(input_upc)) {
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
                    temp->next = nullptr;
                    delete temp;
                    release_upc(input_upc);
                    return;
                }
            }
        }
    }
    throw "not found";
}

std::vector<int> inventory::get_upc(std::string input_name) {
    std::vector<int> upcs_to_return;
    for(inventory_node* current = head; current; current = current->next){
        if(current->name.compare(input_name) == 0) upcs_to_return.push_back(current->upc);
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
            stack pricing_history = stack();
            pricing_history = current->price;
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
            stack pricing_history = stack();
            pricing_history = current->price;
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
    for(inventory_node* current = head; current; current = current->next){
        if(current->upc == input_upc){
            value_date new_pricing = value_date();
            new_pricing.value = new_price;
            new_pricing.date = new_date;
            current->price.push(new_pricing);
            return;
        }
    }
    throw "not found";
}

void inventory::adjust_inventory(int input_upc, int new_inventory) {
    for(inventory_node* current = head; current; current = current->next){
        if(current->upc == input_upc){
            current->inventory_count = new_inventory;
            return;
        }
    }
    throw "not found";
}

inventory_node* inventory::get_head() {
    return head;
}
void inventory::sort_by_lowest_price() {
    //TODO: Double Sort Function
}
