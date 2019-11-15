#ifndef CUSTOMER_HASH_HPP
#define CUSTOMER_HASH_HPP

#include <iostream>
#include "PurchasedHeap.hpp"
/*
struct Product
{
    std::string product_name, catagory, color, date_purchased; //product info
    int num_purchased; //number of specific product purchased

    //Product *previous, *next; //linked list
};
*/

struct Customer
{
    std::string email, customer_name; //customer information
    int num_products = 0;//number of owned products
    //max heap of purchased products
    PurchasedHeap purchasedProducts = PurchasedHeap(500);
    //Product *purchased_head; //linked list sorted by catagory and date bought, ie, catagories will be 1,2,3,4 and if it was bought sooner then it comes first in the list
    Customer *next; //linked list for hash collisions
};

class CustomerHashTable
{
  public:
    //constructor, tablesize = max size of hash table
    CustomerHashTable (int newTablesize);
    //destructor
    ~CustomerHashTable();
    //adds a customer w/ info passed to the table
    void addCustomer(std::string email, std::string customer_name);
    //removes customer from hash table
    void removeCustomer(std::string email);
    //adds a purchase for the customer with the email passed
    void addPurchase(std::string custEmail, std::string productName, std::string catagory, std::string color, std::string size); //IMPORTANT ADD COLOR PARAMETER
    //searches the hash table for a specific customer, returns pointer to that customer
    Customer* searchCustomer(std::string email);
    //writes data to file
    void writeToFile(std::string writeFileName);

    Customer* getCustomerAtIndex(int index);
  private:
    //hashes customer email passed
    unsigned int hashCust(std::string email);
    //max size of customer hash table
    int tablesize;
    //hash table of all customers
    Customer** all_Customers;
};

#endif
