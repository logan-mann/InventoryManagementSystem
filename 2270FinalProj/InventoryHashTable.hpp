#ifndef INVENTORY_HASH_HPP
#define INVENTORY_HASH_HPP

#include <iostream>

struct InventoryItem
{
  std::string itemName;
  std::string category;
};

class InventoryHashTable
{
  public:
    //constructor, tablesize = max size of the hash table
    InventoryHashTable(int tablesize);
    //destructor
    ~InventoryHashTable();
    //searches the inventory hash table for the item passed, returns pointer to that item
    Item* searchInventory(std::string name, std::string category);
    //adds an item to the table
    void addItem(std:string name, std::string itemCategory);
    //removes an item from the inventory hash table
    void removeItem(std::string name, std::string itemCategory);
  private:
    //max size of the hash table
    int tablesize;
    //hashes an item category, returns the index in the table of said category
    unsigned int hashItem(std::string category);
    //hash table of all the items the store carries
    InventoryItem** all_Items;
};
