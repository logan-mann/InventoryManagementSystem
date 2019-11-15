#include "Database.hpp"
#include <iostream>
#include <fstream>


Database::Database()
{
  customerTablesize = 500;
  productTablesize = 500;
}

Database::~Database()
{

}

void Database::specifcCust(std::string custEmail)
{
  Customer* customer = all_customers.searchCustomer(custEmail);
  if (customer == NULL)
  {
    std::cout << "Customer not found in database." << std::endl;
    return;
  }
        std::cout << "----------------------------------" <<std::endl;
  std::cout << "Customer name: " << customer->customer_name << std::endl;
  std::cout << "Customer email: " << customer->email << std::endl;
  std::cout << "Number of owned products: " << customer->num_products << std::endl << std::endl;
  std::cout << "Purchases: " << std::endl;
  customer->purchasedProducts.printHeap();
}

void Database::allCustomers()
{
  for (int i = 0; i < customerTablesize; i++)
  {
    Customer* currentCustomer = all_customers.getCustomerAtIndex(i);
    while (currentCustomer != NULL)
    {
      specifcCust(currentCustomer->email);
      currentCustomer = currentCustomer->next;
      std::cout << std::endl << std::endl;
    }
  }
}

void Database::mostBoughtItems(std::string custEmail)
{
  Customer* customer = all_customers.searchCustomer(custEmail);
  if (customer == NULL)
  {
    std::cout << "Customer does not exist in the database." <<std::endl;
    return;
  }
  customer->purchasedProducts.printTopThree();
}

void Database::numberProductsOwned(std::string custEmail)
{
  Customer* customer = all_customers.searchCustomer(custEmail);
  if (customer == NULL)
  {
    std::cout << "Customer does not exist in the database." <<std::endl;
    return;
  }
  std::cout << "Number of products owned by " << customer->customer_name << ": " << customer->purchasedProducts.getCurrentSize() << std::endl;
}

void printProduct(InventoryProduct* product)
{
  if (product != NULL)
  {
      std::cout << product->product_name << ", Category: " << product->catagory << ", Color: " << product->color << ", Size: " << product->size << ", Number Purchased: " << product->num_purchased << std::endl;
  }
}


//dynamically aloocate each index in the heap
void Database::mostPopularItems()
{
  int inventorySize = all_products.getTableSize();
  std::cout << "Here are the top 5 most purchased items: " << std::endl;
  int totalProducts = all_products.getNumProducts();
  InventoryHeap inventoryHeap = InventoryHeap(totalProducts);
  for (int i = 0; i < inventorySize; i++)
  {
    InventoryProduct* currProduct = all_products.getProductAtIndex(i);
    while (currProduct != NULL)
    {
      InventoryProduct* tempProduct = new InventoryProduct;
      *tempProduct = *currProduct;
      inventoryHeap.addToHeap(tempProduct);
      currProduct = currProduct->next;
    }
  }
  for (int i = 0; i < 5; i++)
  {
    std::cout << i+1 << ". " << std::endl;
    printProduct(inventoryHeap.removeFromHeap());
  }
  std::cout << std::endl;
}

void Database::whoBoughtItem(std::string productName)
{
  std::cout << "Here are all the customers who bought " << productName << ": " << std::endl;
  for (int i = 0; i < customerTablesize; i++)
  {
    Customer* currCustomer = all_customers.getCustomerAtIndex(i);
    while (currCustomer != NULL)
    {
      if (currCustomer->purchasedProducts.findProduct(productName) != NULL)
      {
        std::cout << "Name: " << currCustomer->customer_name << "E-mail: " << currCustomer->email << std::endl;
      }
      currCustomer = currCustomer->next;
    }
  }
}

void Database::reccLikeProduct(std::string custEmail)
{
  Customer* customer = all_customers.searchCustomer(custEmail);
  if (customer == NULL)
  {
    std::cout << "Customer does not exist in the database." << std::endl;
    return;
  }
  if (customer->num_products == 0)
  {
    std::cout << customer->customer_name << " has not purchased any products to make recommendations based on." << std::endl;
    return;
  }
  std::cout << "Here are some similar products to " << customer->customer_name << "'s most purchased item." << std::endl;
  Product* topProduct = customer->purchasedProducts.peekProduct();
  if (topProduct != NULL)
  {
    all_products.printLikeProducts(topProduct->product_name, topProduct->catagory);
  }
}

void Database::addCustomer(std::string custEmail, std::string custName)
{
  all_customers.addCustomer(custEmail, custName);
}

void Database::addPurchase(std::string custEmail, std::string custName, std::string productName, std::string catagory, std::string color, std::string size)
{
  if (all_customers.searchCustomer(custEmail) == NULL)
  {
    all_customers.addCustomer(custEmail, custName);
  }
  if (all_products.searchInventory(productName, catagory, color, size) == NULL)
  {
    std::cout << productName << " " << catagory << " " << color << " " << size << " does not exist in the database." << std::endl;
    return;
  }
  all_customers.addPurchase(custEmail, productName, catagory, color, size);
  all_products.incrememntNumPurchased(productName, catagory, color, size);
}

void Database::addProduct(std::string product_name, std::string catagory, std::string color, std::string size)
{
  all_products.addProduct(product_name, catagory, color, size);
}

void Database::saveToFile(std::string custFileName, std::string inventFileName)
{
  all_customers.writeToFile(custFileName);
  all_products.writeToFile(inventFileName);
}

void Database::printInventory()
{
  all_products.print_allProducts();
}

void Database::printPurchased()
{
  all_products.print_purchased();
}
