#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "CustomerHashTable.hpp"
#include "Inventory.hpp"
#include <iostream>

class Database
{

    //IMPORTANT: WHEN IMPLEMENTING A DRIVER FUNCTION TO ADD A PURCHASE FOR A CUSTOMER, MUST VERIFY THAT THE PRODUCT EXISTS IN INVENTORY;
    public:
         Database(); //constructor
        ~Database(); //destructor

        void allCustomers(); //Prints all customers
        void specifcCust(std::string custEmail); //Prints the specifics of a certain customer
        void mostBoughtItems(std::string custEmail); //Prints the most bought items by item name for a customer
        void numberProductsOwned(std::string custEmail); //Prints number of products owned by customer
        void mostPopularItems(); //Prints the 5 most bought products
        void whoBoughtItem(std::string productName); //Prints the all customers who bought specific product
        void reccLikeProduct(std::string custEmail); //reccomends a product in the same catagory as the most bought
        void addCustomer(std::string custEmail, std::string custName); //adds a customer to database
        void addPurchase(std::string custEmail, std::string custName, std::string productName, std::string catagory, std::string color, std::string size); //adds purchase for specific customer
        void addProduct(std::string product_name, std::string catagory, std::string color, std::string size); //adds a product to the inventory database
        void printInventory();
        void saveToFile(std::string custFileName, std::string inventFileName);
        void printPurchased();
    private:
        int customerTablesize;
        int productTablesize;
        Inventory all_products = Inventory(500); //hash table for all products
        CustomerHashTable all_customers = CustomerHashTable(500); //hash table for logged customers
        /*
        dont think these vars are neccessary

        Product* newProduct(std::string product_name, std::string catagory, std::string color, std::string date_purchased, Product* next);
        Customer* newCustomer(std::string email, std::string address, std::string customer_name, std::string birthday, Customer* next);
        */

};

#endif
