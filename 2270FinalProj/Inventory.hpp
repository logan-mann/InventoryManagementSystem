

/*
struct InventoryProduct
{
    std::string product_name, catagory, color, size; //product info
    int num_purchased; //number of specific product purchased

    InventoryProduct *previous, *next; //linked list
};
*/

#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <iostream>
#include <string>
#include "InventoryHeap.hpp"


class Inventory //Possibly make one inventory
{
    private:
    int numCatagorys;
    InventoryProduct* *fullInventory;
    int numProducts = 0;
    public:
    Inventory(int Catagorys);
    ~Inventory();
    unsigned int HashProduct(std::string catagory);
    int getNumProducts();
    void print_purchased();
    void print_allProducts();

    void print_numPurchased(std::string product_name, std::string catagory, std::string color, std::string size);

    void printLikeProducts(std::string productName, std::string category);
    bool addProduct(std::string product_name, std::string catagory, std::string color, std::string size);
    void addPurchse(std::string product_name, std::string catagory, std::string color, std::string size);
    void writeToFile(std::string writeFileName);
    InventoryProduct* getProductAtIndex(int index);
    int getTableSize();
    InventoryProduct *searchInventory(std::string product_name, std::string catagory, std::string color, std::string size);
    void printInventory();
    void incrememntNumPurchased(std::string product_name, std::string catagory, std::string color, std::string size);
};


#endif
