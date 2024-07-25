#pragma once
#include <vector>
#include "Item.h"

class Inventory {
public:

    //Functionalities about operating the Inventory

    void addItem(const std::string& name, int id, int quantity, double price, const std::string& supplier);
    void updateItemAttribute(int id);
    void deleteItemById(int id);
    void deleteItemByName(const std::string& name);
    Item* searchItemByName(const std::string& name);
    Item* searchItemById(int id);
    std::vector<Item> searchItemsByQuantity(int quantity);
    std::vector<Item> searchItemsBySupplier(const std::string& supplier);
    void generateReport();
    void sortItems();
    void generateReportByQuantity(int option);
    void generatePromotionReport();
    void addItemToFile(const Item& item);
private:
    std::vector<Item> items;
    
};
