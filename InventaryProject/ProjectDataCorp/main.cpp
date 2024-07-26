#include <iostream>
#include "Item.h"
#include "Inventory.h"

int main() {
    Inventory inventory;
    std::string input;


    // adding new items
    ///////
    while (true) {
        std::cout << "Enter item name (or 'enough' to stop): "; //key word enough breaks the function for adding new products 
        std::getline(std::cin, input);                          // so user can continue his work with the next functions
        if (input == "enough") break;
        std::string name = input;

        std::cout << "Enter quantity: ";    
        int quantity;
        std::cin >> quantity;

        std::cout << "Enter price: ";
        double price;
        std::cin >> price;

        std::cin.ignore(); 

        std::cout << "Enter supplier: ";
        std::getline(std::cin, input);
        std::string supplier = input;

        static int id_counter = 1; // the coutner starts from 1
        inventory.addItem(name, id_counter++, quantity, price, supplier);
    }

    std::cout << "Current inventory:" << std::endl;
    inventory.generateReport(); // generating report, cuse i want the ID of the products to be visible for the next operations

    



    //////////////// update

    while (true) {
        std::cout << "Enter item ID to update (or '0' to exit): ";          // '0' to break the function and procceed
        int id;
        std::cin >> id;
        if (id == 0) break;
        inventory.updateItemAttribute(id);  //update product with the taken ID

        std::cout << "Updated inventory:" << std::endl;
        inventory.generateReport();     //new report to check the updated info
    }


    //deleting
    ///////////

    while (true) {
        std::cout << "Do you want to delete an item? (yes/no): ";
        std::string choice;
        std::cin >> choice;

        if (choice == "no") break;

        std::cout << "Enter item ID to delete (or '0' to skip): ";  //deleting byID
        int id;
        std::cin >> id;
        if (id != 0) {
            inventory.deleteItemById(id);   //calls funciton deleteByID
        }
        else {
            std::cin.ignore();
        }

        std::cin.ignore();

        std::cout << "Enter item name to delete (or 'none' to skip): "; //deleting by name
        std::string name;
        std::getline(std::cin, name);
        if (name != "none") {
            inventory.deleteItemByName(name);
        }

        std::cout << "Inventory after deletion:" << std::endl;
        inventory.generateReport();     // new report to check if the item is deleted
    }




    //searching
    ////////////////////////////

    while (true) {
        std::cout << "Do you want to search for an item? (yes/no): ";
        std::string choice;
        std::cin >> choice;

        if (choice == "no") break;

        std::cout << "Search by (Name, ID, Quantity, Supplier): ";
        std::string criterion;
        std::cin >> criterion;

        if (criterion == "Name") {      //searching with Name
            std::cout << "Enter name: ";
            std::cin.ignore();
            std::getline(std::cin, input);
            Item* item = inventory.searchItemByName(input); //checks if the inputed info is found in the massive
            if (item) {
                std::cout << "Found item - ID: " << item->getId()   //if found the info about the item is displayed on the console
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
        else if (criterion == "ID") {       //search by ID
            std::cout << "Enter ID: ";
            int id;
            std::cin >> id;
            Item* item = inventory.searchItemById(id);          //if found the info about the item is displayed on the console
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
        else if (criterion == "Quantity") {     //search by qunatity
            std::cout << "Enter quantity: ";
            int quantity;
            std::cin >> quantity;
            std::vector<Item> items = inventory.searchItemsByQuantity(quantity);        //if found the info about the item is displayed on the console
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
        else if (criterion == "Supplier") {         //searching by supplier
            std::cout << "Enter supplier: ";
            std::cin.ignore();
            std::getline(std::cin, input);
            std::vector<Item> items = inventory.searchItemsBySupplier(input);   //if found the info about the item is displayed on the console
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
            std::cout << "Do you want to sort the inventory? (yes/no): ";       //nothing speacial to add here
            std::string choice;                                                 // jsut the program call function sortItems and generates report
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
                inventory.generateReportByQuantity(option);         //based on the option 1 or 2 the program displays info
            }                                                       //about items with <10 or >50 quantity
            else if (option == 3) {                                 //if the option is 3 the program shows items suggested for promotion
                inventory.generatePromotionReport();
            }

            else {
                std::cout << "Invalid option." << std::endl;
            }
        }





    
    return 0;
}
