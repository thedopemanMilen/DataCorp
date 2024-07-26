#include "Inventory.h"
#include <iostream>
#include <fstream>   
#include <vector>
#include <algorithm>

void Inventory::addItem(const std::string& name, int id, int quantity, double price, const std::string& supplier) {
    Item newItem(name, id, quantity, price, supplier);      //adding items in dynamic massive
    items.emplace_back(newItem);                            //adding 'newItem' at the back of the container
    addItemToFile(newItem);                                 //calling function to add the items in a txt file
}

void Inventory::addItemToFile(const Item& item) {
    std::ofstream file("C:\\Users\\mena\\source\\repos\\ProjectDataCorp\\ProjectDataCorp\\inventory.txt", std::ios_base::app);      //the path to my repo

    if (file.is_open()) {           //takes the info from 'newItem' to write it in the txt file
        file << item.getId() << ","
            << item.getName() << ","
            << item.getQuantity() << ","
            << item.getPrice() << ","
            << item.getSupplier() << ","
            
            << item.getDateAdded() << "\n";
        file.close();
    }
    else {
        std::cerr << "Unable to open file for writing!" << std::endl;
    }
}


void Inventory::updateItemAttribute(int id) {           //updating attribute
    for (auto& item : items) {
        if (item.getId() == id) {           //True if there is item with the ID which the user typed
            std::string attribute;              
            std::cout << "Enter the attribute to update (Name, Quantity, Price, Supplier): ";
            std::cin >> attribute;

            if (attribute == "Name") {      //if user wrote 'name 'changing the new name
                std::string newName;
                std::cout << "Enter new name: ";
                std::cin.ignore();
                std::getline(std::cin, newName);
                item.setName(newName);
            }
            else if (attribute == "Quantity") {      //if user wrote 'quantity 'changing the new quantity
                int newQuantity;
                std::cout << "Enter new quantity: ";
                std::cin >> newQuantity;
                item.setQuantity(newQuantity);
            }
            else if (attribute == "Price") {        //if user wrote 'price 'changing the new price
                double newPrice;
                std::cout << "Enter new price: ";
                std::cin >> newPrice;
                item.setPrice(newPrice);
            }
            else if (attribute == "Supplier") {     //if user wrote 'supplier 'changing the new supplier
                std::string newSupplier;
                std::cout << "Enter new supplier: ";
                std::cin.ignore();
                std::getline(std::cin, newSupplier);
                item.setSupplier(newSupplier);
            }
            else {
                std::cout << "Invalid attribute." << std::endl;     //if the is no item with the typed ID 
            }
            break;
        }
    }
}
    
void Inventory::deleteItemById(int id) {        //deleting item by ID
    items.erase(std::remove_if(items.begin(), items.end(),      //erasing it 
        [id](const Item& item) { return item.getId() == id; }), items.end());
}

void Inventory::deleteItemByName(const std::string& name) {     //deleting item by name
    items.erase(std::remove_if(items.begin(), items.end(),
        [name](const Item& item) { return item.getName() == name; }), items.end());
}

Item* Inventory::searchItemByName(const std::string& name) {        //searching item by name
    for (auto& item : items) {
        if (item.getName() == name) {       //the logic is in the Main.cpp
            return &item;
        }
    }
    return nullptr;
}

Item* Inventory::searchItemById(int id) {
    for (auto& item : items) {
        if (item.getId() == id) {       //the logic is in the Main.cpp
            return &item;
        }
    }
    return nullptr;
}

std::vector<Item> Inventory::searchItemsByQuantity(int quantity) {
    std::vector<Item> result;
    for (const auto& item : items) {
        if (item.getQuantity() == quantity) {       //the logic is in the Main.cpp
            result.push_back(item);
        }
    }
    return result;
}

std::vector<Item> Inventory::searchItemsBySupplier(const std::string& supplier) {
    std::vector<Item> result;
    for (const auto& item : items) {
        if (item.getSupplier() == supplier) {           //the logic is in the Main.cpp
            result.push_back(item);
        }
    }
    return result;
}

void Inventory::generateReport() {      //generating report with all items without sorting
    std::cout << "Inventory Report:" << std::endl;
    for (const auto& item : items) {
        std::cout << "ID: " << item.getId()
            << ", Name: " << item.getName()
            << ", Quantity: " << item.getQuantity()
            << ", Price: " << item.getPrice()
            << ", Supplier: " << item.getSupplier()
            << ", Date Added: " << item.getDateAdded() << std::endl;
    }
}

void Inventory::sortItems() {       //sorting items
    std::cout << "Sort by (Name, Price, ID): ";
    std::string criterion;
    std::cin >> criterion;

    std::cout << "Order (asc, desc): ";
    std::string order;
    std::cin >> order;

    if (criterion == "Name") {      //if the user wanted the sort the items by their names
        if (order == "asc") {       //sort the ascending
            std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
                return a.getName() < b.getName();
                });
        }
        else if (order == "desc") { //sort them descending
            std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
                return a.getName() > b.getName();
                });
        }
        else {
            std::cout << "Invalid order." << std::endl;
        }
    }
    else if (criterion == "Price") {        //if the user wanted the sort the items by their prices
        if (order == "asc") {
            std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
                return a.getPrice() < b.getPrice();
                });
        }
        else if (order == "desc") {
            std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
                return a.getPrice() > b.getPrice();
                });
        }
        else {
            std::cout << "Invalid order." << std::endl;
        }
    }
    else if (criterion == "ID") {           //if the user wanted the sort the items by their IDs
        if (order == "asc") {
            std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
                return a.getId() < b.getId();
                });
        }
        else if (order == "desc") {
            std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
                return a.getId() > b.getId();
                });
        }
        else {
            std::cout << "Invalid order." << std::endl;
        }
    }
    else {
        std::cout << "Invalid criterion." << std::endl;
    }
}

void Inventory::generateReportByQuantity(int option) {          //report by quantity
    if (option == 1) {                                          //if the user wrote '1' he wanted to see which items are under 10 by quantity
        std::cout << "Items with quantity less than 10:" << std::endl;
        for (const auto& item : items) {
            if (item.getQuantity() < 10) {
                std::cout << "ID: " << item.getId()
                    << ", Name: " << item.getName()
                    << ", Quantity: " << item.getQuantity()
                    << ", Price: " << item.getPrice()
                    << ", Supplier: " << item.getSupplier()
                    << ", Date Added: " << item.getDateAdded() << std::endl;
            }
        }
    }
    else if (option == 2) {                                     //if the user wrote '1' he wanted to see which items are over 50 by quantity
        std::cout << "Items with quantity greater than 50:" << std::endl;
        for (const auto& item : items) {
            if (item.getQuantity() > 50) {
                std::cout << "ID: " << item.getId()
                    << ", Name: " << item.getName()
                    << ", Quantity: " << item.getQuantity()
                    << ", Price: " << item.getPrice()
                    << ", Supplier: " << item.getSupplier()
                    << ", Date Added: " << item.getDateAdded() << std::endl;
            }
        }
    }
    else {
        std::cout << "Invalid option." << std::endl;
    }
}

void Inventory::generatePromotionReport() {                                     //Other function which is for suggesting items for promotion 
    std::cout << "Products suggested for promotion (Price is >10% of Quantity):" << std::endl;          //their price is 10% of their quantity
    for (const auto& item : items) {
        if (item.getPrice() > 0.1 * item.getQuantity()) {
            std::cout << "ID: " << item.getId()
                << ", Name: " << item.getName()
                << ", Quantity: " << item.getQuantity()
                << ", Price: " << item.getPrice()
                << ", Supplier: " << item.getSupplier()
                << ", Date Added: " << item.getDateAdded() << std::endl;
        }
    }
}
