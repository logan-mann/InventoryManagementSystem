#include <iostream>
#include "CustomerHashTable.hpp"
#include <fstream>
#include <sstream>
#include <vector>

void printCustomerData(Customer* customer)
{
  std::cout << "Customer Name: " << customer->customer_name << std::endl;
  std::cout << "Customer E-mail: " << customer->email << std::endl;
  std::cout << "Customer Address: " << customer->address << std::endl;
  std::cout << "Customer Birthday: " << customer->birthday << std::endl;
  if (customer->purchasedProducts.isEmpty() == true)
  {
    std::cout << customer->customer_name << " has not purchased anything." << std::endl;
    std::cout << std::endl << std::endl;
    return;
  }
  std::cout << customer->customer_name << "'s Purchases: "<< std::endl;
  Product* currProduct = customer->purchasedProducts.peekProduct();
  //while (currProduct != NULL)
  //{
    std::cout << currProduct->product_name << ", Amount purchased: " << currProduct->num_purchased << std::endl;
    //currProduct = currProduct->next;
  //}
  std::cout << std::endl << std::endl;
  return;
}

int main(int argc, char* argv[])
{
  CustomerHashTable myCustHash(20);
  std::ifstream custData;
  std::string currentCustLine;
  std::string currentCustEmail;
  std::string currentCustName;
  std::string currentCustAddress;
  std::string currentCustBirthday;
  std::vector<std::string> emailVector;
  custData.open(argv[1]);
  if (custData.fail())
  {
    std::cout << "Failed to open file." << std::endl;
    return 0;
  }
  while (getline(custData, currentCustLine))
  {
    std::stringstream currentCustData(currentCustLine);
    getline(currentCustData, currentCustEmail, ',');
    getline(currentCustData, currentCustAddress, ',');
    getline(currentCustData, currentCustName, ',');
    getline(currentCustData, currentCustBirthday, ',');
    myCustHash.addCustomer(currentCustEmail, currentCustAddress, currentCustName, currentCustBirthday);
    emailVector.push_back(currentCustEmail);
  }
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Fur Jacket", "Jackets", "Black", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Fur Jacket", "Jackets", "Red", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Button up Shirt", "Shirts", "Red", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Shoes", "Shoes", "Red", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Button up Shirt", "Shirts", "Red", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Shoes", "Shoes", "Red", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Button up Shirt", "Shirts", "Red", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Shoes", "Shoes", "Red", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Button up Shirt", "Shirts", "Red", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Shoes", "Shoes", "Red", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Button up Shirt", "Shirts", "Red", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Shoes", "Shoes", "Red", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Button up Shirt", "Shirts", "Red", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Shoes", "Shoes", "Red", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Fur Jacket", "Jackets", "Black", "4/16/19");
  myCustHash.addPurchase("johnny_appleseed@gmail.com", "Fur Jacket", "Jackets", "Red", "4/16/19");
  for (int i = 0; i < emailVector.size(); i++)
  {
    printCustomerData(myCustHash.searchCustomer(emailVector[i]));
  }
  myCustHash.removeCustomer(emailVector[emailVector.size() - 1]);
  emailVector.pop_back();
  {
    printCustomerData(myCustHash.searchCustomer(emailVector[i]));
  }
  return 0;
}
