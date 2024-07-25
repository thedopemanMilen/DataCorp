#include "Inventory.h"
#include <iostream>
#include <fstream>   
#include <vector>
#include <algorithm>

void Inventory::addItem(const std::string& name, int id, int quantity, double price, const std::string& supplier) {
    Item newItem(name, id, quantity, price, supplier);
    items.emplace_back(newItem);
    addItemToFile(newItem); // Записване на новия артикул в текстовия файл
}

void Inventory::addItemToFile(const Item& item) {
    std::ofstream file("C:\\Users\\mena\\source\\repos\\ProjectDataCorp\\ProjectDataCorp\\inventory.txt", std::ios_base::app);

    if (file.is_open()) {
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


void Inventory::updateItemAttribute(int id) {
    for (auto& item : items) {
        if (item.getId() == id) {
            std::string attribute;
            std::cout << "Enter the attribute to update (Name, Quantity, Price, Supplier): ";
            std::cin >> attribute;

            if (attribute == "Name") {
                std::string newName;
                std::cout << "Enter new name: ";
                std::cin.ignore();
                std::getline(std::cin, newName);
                item.setName(newName);
            }
            else if (attribute == "Quantity") {
                int newQuantity;
                std::cout << "Enter new quantity: ";
                std::cin >> newQuantity;
                item.setQuantity(newQuantity);
            }
            else if (attribute == "Price") {
                double newPrice;
                std::cout << "Enter new price: ";
                std::cin >> newPrice;
                item.setPrice(newPrice);
            }
            else if (attribute == "Supplier") {
                std::string newSupplier;
                std::cout << "Enter new supplier: ";
                std::cin.ignore();
                std::getline(std::cin, newSupplier);
                item.setSupplier(newSupplier);
            }
            else {
                std::cout << "Invalid attribute." << std::endl;
            }
            break;
        }
    }
}

void Inventory::deleteItemById(int id) {
    items.erase(std::remove_if(items.begin(), items.end(),
        [id](const Item& item) { return item.getId() == id; }), items.end());
}

void Inventory::deleteItemByName(const std::string& name) {
    items.erase(std::remove_if(items.begin(), items.end(),
        [name](const Item& item) { return item.getName() == name; }), items.end());
}

Item* Inventory::searchItemByName(const std::string& name) {
    for (auto& item : items) {
        if (item.getName() == name) {
            return &item;
        }
    }
    return nullptr;
}

Item* Inventory::searchItemById(int id) {
    for (auto& item : items) {
        if (item.getId() == id) {
            return &item;
        }
    }
    return nullptr;
}

std::vector<Item> Inventory::searchItemsByQuantity(int quantity) {
    std::vector<Item> result;
    for (const auto& item : items) {
        if (item.getQuantity() == quantity) {
            result.push_back(item);
        }
    }
    return result;
}

std::vector<Item> Inventory::searchItemsBySupplier(const std::string& supplier) {
    std::vector<Item> result;
    for (const auto& item : items) {
        if (item.getSupplier() == supplier) {
            result.push_back(item);
        }
    }
    return result;
}

void Inventory::generateReport() {
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

void Inventory::sortItems() {
    std::cout << "Sort by (Name, Price, ID): ";
    std::string criterion;
    std::cin >> criterion;

    std::cout << "Order (asc, desc): ";
    std::string order;
    std::cin >> order;

    if (criterion == "Name") {
        if (order == "asc") {
            std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
                return a.getName() < b.getName();
                });
        }
        else if (order == "desc") {
            std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
                return a.getName() > b.getName();
                });
        }
        else {
            std::cout << "Invalid order." << std::endl;
        }
    }
    else if (criterion == "Price") {
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
    else if (criterion == "ID") {
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

void Inventory::generateReportByQuantity(int option) {
    if (option == 1) {
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
    else if (option == 2) {
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

void Inventory::generatePromotionReport() {
    std::cout << "Products suggested for promotion (Price is >10% of Quantity):" << std::endl;
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
