#include "../inc/inventory.h"
#include <cstdlib>
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
    if(val->first == input_upc && !val->second){
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
inventory::inventory()
{
    head  = nullptr;
    initialize_upc();
}
inventory::~inventory() {
    while (head)
    {
        if(head->next == NULL)
        {
            head = nullptr;
        }
        else
        {
            inventory_node *temp = head->next;
            delete head;
            head = temp;
        }
    }
}
void inventory::add_sku(std::string new_name, int initial_price, int initial_inventory, int initial_date)
{
    int newupc = reserve_upc();
    while (valid_upc(newupc) == false)
    {
        newupc = reserve_upc();
    }
    inventory_node *temp = new inventory_node (newupc, new_name, initial_inventory, initial_price, initial_date);
    if (head == nullptr)
    {
        head = temp;
    }
    else
    {
        inventory_node *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = temp;
        current = current->next;
    }
}
void inventory::remove_sku(int input_upc)
{
    if (valid_upc(input_upc) == false)
        throw -1;
    else if (head ->next == nullptr)
    {
        head = nullptr;
    }
    else if (head->upc == input_upc)
    {
        inventory_node *future = head->next;
        delete head;
        head = future;
    }
    else
    {
        inventory_node *previous;
        inventory_node *current = head;
        while (current->upc != input_upc)
        {
            previous = current;
            current = current->next;
        }
        previous ->next = current ->next;
        delete current;
    }
}
std::vector<int> inventory::get_upc(std::string input_name)
{
    std::vector<int> result;
    inventory_node *current = head;
    while (current != nullptr)
    {
        if (current->name == input_name)
        {
            result.push_back(current->upc);
        }
        current = current->next;
    }
    return result;
}
int inventory::get_price(int input_upc)
{
    if (valid_upc(input_upc) == false)
        throw -1;
    else if (head == nullptr)
    {
        throw -1;
    }
    else{
        inventory_node *current = head;
        while (current->upc != input_upc)
        {
            current = current->next;
        }
        return current->price.top().value;
    }
}
int inventory::get_inventory(int input_upc)
{
    if (valid_upc(input_upc) == false)
        throw -1;
    else if (head == nullptr)
    {
        throw -1;
    }
    else{
        inventory_node *current = head;
        while (current->upc != input_upc)
        {
            current = current->next;
        }
        return current->inventory_count;
    }
}
std::string inventory::get_name(int input_upc)
{
    if (valid_upc(input_upc) == false)
        throw -1;
    else if (head == nullptr)
    {
        throw -1;
    }
    else{
        inventory_node *current = head;
        while (current->upc != input_upc)
        {
            current = current->next;
        }
        return current->name;
    }
}
int inventory::get_lowest_price(int input_upc)
{
    if (valid_upc(input_upc) == false)
        throw -1;
    else if (head == nullptr)
    {
        throw -1;
    }
    else
    {
        inventory_node *current = head;
        while (current->upc != input_upc)
        {
            current = current->next;
        }
        stack find;
        find.operator=(current->price);
        int low = find.top().value;
        find.pop();
        while (find.empty() == false)
        {
            if (find.top().value < low)
                low = find.top().value;
            find.pop();
        }
        return low;
    }
}
int inventory::get_highest_price(int input_upc)
{
    if (valid_upc(input_upc) == false)
        throw -1;
    else if (head == nullptr)
    {
        throw -1;
    }
    else
    {
        inventory_node *current = head;
        while (current->upc != input_upc) {
            current = current->next;
        }
        stack find;
        find.operator=(current->price);
        int high = find.top().value;
        find.pop();
        while (find.empty() == false) {
            if (find.top().value > high)
                high = find.top().value;
            find.pop();
        }
        return high;
    }
}
void inventory::adjust_price(int input_upc, int new_price, int new_date)
{
    if (valid_upc(input_upc) == false)
        throw -1;
    else if (head == nullptr)
    {
        throw -1;
    }
    else{
        struct value_date input;
        input.date = new_date;
        input.value = new_price;
        inventory_node *current = head;
        while (current->upc != input_upc)
        {
            current = current->next;
        }
        current->price.push(input);
    }
}
void inventory::adjust_inventory(int input_upc, int new_inventory)
{
    if (valid_upc(input_upc) == false)
        throw -1;
    else if (head == nullptr)
    {
        throw -1;
    }
    else{
        inventory_node *current = head;
        while (current->upc != input_upc)
        {
            current = current->next;
        }
        current->inventory_count = new_inventory;
    }
}
void inventory::sort_by_lowest_price()
{
    inventory_node *current = head, *pre = nullptr, *next = nullptr;
    inventory_node * top = nullptr, *pre1 = nullptr, *next1 = nullptr;
    inventory_node *mini = nullptr, *mp = nullptr, *mn = nullptr;
    while(current){
        top = current->next;
        mini = current;
        while(top != nullptr){
            if(mini->price.top().value > top->price.top().value){
                mp = pre1;
                mini = top;
                mn = next1;
            }
            pre1 = top;
            top = top->next;
            if(top != nullptr) {
                next1 = top->next;
            }
            else {
                next1 = nullptr;
            }
        }
        if(current->next == mini){
            if(current == head){
                current->next = mini->next;
                mini->next = current;
                current = mini;
                head = mini;
            }
            else if (!mini->next){
                current->next = nullptr;
                mini->next = current;
                pre->next = mini;
                current = mini;
            }
            else{
                current->next = mn;
                mini->next = current;
                pre->next = mini;
                current = mini;
            }
        }
        else if(current == head && current->next != mini){
            if(!mini->next){
                mini->next = current->next;
                mp->next = current;
                current->next = nullptr;
                current = mini;
                head = mini;
            }
            else if(mini->next && mp){
                mini->next = current->next;
                mp->next = current;
                current->next = mn;
                current = mini;
                head = mini;
            }
            else if(!mp){
                mini->next = current->next;
                current->next = current;
                current->next = mn;
                current = mini;
                head = mini;
            }
        }
        else if(!mn && current->next != mini && current !=head){
            current ->next = nullptr;
            mp->next = current;
            pre->next = mini;
            mini->next = next;
            current = mini;
        }
        else {
            current ->next = mn;
            mp->next = current;
            pre->next = mini;
            mini->next = next;
            current = mini;
        }
        pre = current;
        current = current->next;
        if(current != nullptr) {
            next = current->next;
        }
        else {
            next = nullptr;
        }
    }
    inventory_node *a = head;
    int length=0;
    while(a){
        int b = a->price.top().value;
        int c = a->inventory_count;
        a = a->next;
        length ++;
    }
    inventory_node *x = head, *xp, *xn;
    inventory_node *y = nullptr, *yp, *yn;
    inventory_node *ls = nullptr, *lsp, *lsn;
    while(x){
        y = x->next;
        ls = x;
        while(y){
            if(ls->price.top().value == y->price.top().value){
                if(ls->inventory_count < y->inventory_count){
                    lsp = yp;
                    ls = y;
                    lsn = yn;
                }
            }
            yp = y;
            y = y->next;
            if(y != nullptr) {
                yn = y->next;
            }
            else {
                yn = nullptr;
            }
        }
        if(ls != x) {
            if (x->next == ls) {
                if (!lsn) {
                    x->next = nullptr;
                    xp->next = ls;
                    ls->next = x;
                    x = ls;
                } else {
                    x->next = lsn;
                    ls->next = x;
                    xp->next = ls;
                    x = ls;
                }
            } else if (!lsn && x->next != ls) {
                x->next = nullptr;
                lsp->next =x;
                xp->next =ls;
                ls->next = xn;
                x = ls;
            } else {
                x ->next = lsn;
                lsp->next = x;
                xp->next = ls;
                ls->next = xn;
                x = ls;
            }
        }
        xp = x;
        x = x->next;
        if(x != nullptr){
            xn = x->next;
        }
        else {
            xn = nullptr;
        }
    }

}
inventory_node *inventory::get_head()
{
    return head;
}