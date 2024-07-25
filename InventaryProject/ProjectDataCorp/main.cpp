#include <iostream>
#include "Item.h"
#include "Inventory.h"

int main() {
    Inventory inventory;
    std::string input;


    while (true) {
        std::cout << "Enter item name (or 'enough' to stop): ";
        std::getline(std::cin, input);
        if (input == "enough") break;
        std::string name = input;

        std::cout << "Enter quantity: ";
        int quantity;
        std::cin >> quantity;

        std::cout << "Enter price: ";
        double price;
        std::cin >> price;

        std::cin.ignore(); // Игнорирайте новия ред след въвеждането на числата

        std::cout << "Enter supplier: ";
        std::getline(std::cin, input);
        std::string supplier = input;

        static int id_counter = 1; // За генериране на уникален ID
        inventory.addItem(name, id_counter++, quantity, price, supplier);
    }

    std::cout << "Current inventory:" << std::endl;
    inventory.generateReport();

    



    //////////////// update

    while (true) {
        std::cout << "Enter item ID to update (or '0' to exit): ";
        int id;
        std::cin >> id;
        if (id == 0) break;
        inventory.updateItemAttribute(id);

        std::cout << "Updated inventory:" << std::endl;
        inventory.generateReport();
    }

    ///////////

    while (true) {
        std::cout << "Do you want to delete an item? (yes/no): ";
        std::string choice;
        std::cin >> choice;

        if (choice == "no") break;

        std::cout << "Enter item ID to delete (or '0' to skip): ";
        int id;
        std::cin >> id;
        if (id != 0) {
            inventory.deleteItemById(id);
        }
        else {
            std::cin.ignore(); // Игнорирайте новия ред
        }

        std::cin.ignore(); // Игнорирайте новия ред след въвеждането на числата

        std::cout << "Enter item name to delete (or 'none' to skip): ";
        std::string name;
        std::getline(std::cin, name);
        if (name != "none") {
            inventory.deleteItemByName(name);
        }

        std::cout << "Inventory after deletion:" << std::endl;
        inventory.generateReport();
    }

    ////////////////////////////

    

    while (true) {
        std::cout << "Do you want to search for an item? (yes/no): ";
        std::string choice;
        std::cin >> choice;

        if (choice == "no") break;

        std::cout << "Search by (Name, ID, Quantity, Supplier): ";
        std::string criterion;
        std::cin >> criterion;

        if (criterion == "Name") {
            std::cout << "Enter name: ";
            std::cin.ignore();
            std::getline(std::cin, input);
            Item* item = inventory.searchItemByName(input);
            if (item) {
                std::cout << "Found item - ID: " << item->getId()
                    << ", Name: " << item->getName()
                    << ", Quantity: " << item->getQuantity()
                    << ", Price: " << item->getPrice()
                    << ", Supplier: " << item->getSupplier()
                    << ", Date Added: " << item->getDateAdded() << std::endl;
            }
            else {
                std::cout << "Item not found." << std::endl;
            }
        }
        else if (criterion == "ID") {
            std::cout << "Enter ID: ";
            int id;
            std::cin >> id;
            Item* item = inventory.searchItemById(id);
            if (item) {
                std::cout << "Found item - ID: " << item->getId()
                    << ", Name: " << item->getName()
                    << ", Quantity: " << item->getQuantity()
                    << ", Price: " << item->getPrice()
                    << ", Supplier: " << item->getSupplier()
                    << ", Date Added: " << item->getDateAdded() << std::endl;
            }
            else {
                std::cout << "Item not found." << std::endl;
            }
        }
        else if (criterion == "Quantity") {
            std::cout << "Enter quantity: ";
            int quantity;
            std::cin >> quantity;
            std::vector<Item> items = inventory.searchItemsByQuantity(quantity);
            if (!items.empty()) {
                for (const auto& item : items) {
                    std::cout << "ID: " << item.getId()
                        << ", Name: " << item.getName()
                        << ", Quantity: " << item.getQuantity()
                        << ", Price: " << item.getPrice()
                        << ", Supplier: " << item.getSupplier()
                        << ", Date Added: " << item.getDateAdded() << std::endl;
                }
            }
            else {
                std::cout << "No items found with the specified quantity." << std::endl;
            }
        }
        else if (criterion == "Supplier") {
            std::cout << "Enter supplier: ";
            std::cin.ignore();
            std::getline(std::cin, input);
            std::vector<Item> items = inventory.searchItemsBySupplier(input);
            if (!items.empty()) {
                for (const auto& item : items) {
                    std::cout << "ID: " << item.getId()
                        << ", Name: " << item.getName()
                        << ", Quantity: " << item.getQuantity()
                        << ", Price: " << item.getPrice()
                        << ", Supplier: " << item.getSupplier()
                        << ", Date Added: " << item.getDateAdded() << std::endl;
                }
            }
            else {
                std::cout << "No items found with the specified supplier." << std::endl;
            }
        }
        else {
            std::cout << "Invalid search criterion." << std::endl;
        }

    }
        //Sorting
        //////////////////////////////

        while (true) {
            std::cout << "Do you want to sort the inventory? (yes/no): ";
            std::string choice;
            std::cin >> choice;

            if (choice == "no") break;

            inventory.sortItems();

            std::cout << "Sorted inventory:" << std::endl;
            inventory.generateReport();

        }


        ///////      report

        while (true) {
            std::cout << "Do you want to generate a report for the products? (yes/no): ";
            std::string choice;
            std::cin >> choice;
            if (choice == "no") break;

            std::cout << "Choose an option:\n1. Show products with quantity less than 10\n2. Show products with quantity greater than 50\n3. Show products suggested for promotion\n";
            int option;
            std::cin >> option;

            if (option == 1 || option == 2) {
                inventory.generateReportByQuantity(option);
            }
            else if (option == 3) {
                inventory.generatePromotionReport();
            }

            else {
                std::cout << "Invalid option." << std::endl;
            }
        }





    
    return 0;
}
