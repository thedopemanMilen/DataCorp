#pragma once
#include <string>
#include <chrono>

class Item {
public:
    Item(const std::string& name, int id, int quantity, double price, const std::string& supplier);

    //getters
    std::string getName() const;
    int getId() const;
    int getQuantity() const;
    double getPrice() const;
    std::string getSupplier() const;
    std::string getDateAdded() const;

    //setters
    void setName(const std::string& name);
    void setQuantity(int quantity);
    void setPrice(double price);
    void setSupplier(const std::string& supplier);

private:
    std::string name;
    int id;
    int quantity;
    double price;
    std::string supplier;
    std::string dateAdded; 

    std::string getCurrentDate(); 
};
