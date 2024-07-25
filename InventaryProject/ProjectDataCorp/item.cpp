#include "Item.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Item::Item(const std::string& name, int id, int quantity, double price, const std::string& supplier)
    : name(name), id(id), quantity(quantity), price(price), supplier(supplier), dateAdded(getCurrentDate()) {}

std::string Item::getName() const {
    return name;
}

int Item::getId() const {
    return id;
}

int Item::getQuantity() const {
    return quantity;
}

double Item::getPrice() const {
    return price;
}

std::string Item::getSupplier() const {
    return supplier;
}

std::string Item::getDateAdded() const {
    return dateAdded;
}

void Item::setName(const std::string& name) {
    this->name = name;
}

void Item::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Item::setPrice(double price) {
    this->price = price;
}

void Item::setSupplier(const std::string& supplier) {
    this->supplier = supplier;
}

std::string Item::getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm;
    localtime_s(&now_tm, &now_time); // Use localtime_s instead of localtime

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
