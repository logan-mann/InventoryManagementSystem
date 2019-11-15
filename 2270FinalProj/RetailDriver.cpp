#include "PurchasedHeap.hpp"
#include "Database.hpp"
#include "Inventory.hpp"
#include "CustomerHashTable.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void displayMenu()
{
  cout << endl;
  cout << "======= Main Menu =======" << endl << endl;
  cout << "1. Read products from a file into inventory" << endl<<endl;
  cout << "2. Read customer purchases from a file into the database" << endl<<endl;
  cout << "3. Add a customer to the database" << endl<<endl;
  cout << "4. Add a purchase to a customer's record" << endl<<endl;
  cout << "5. Add a product to inventory" << endl<<endl;
  cout << "6. Print all customer information" << endl<<endl;
  cout << "7. Print all of a specific customer's information" << endl<<endl;
  cout << "8. Print a customer's top three most bought items" << endl<<endl;
  cout << "9. Print the number of products a customer has purchased" << endl<<endl;
  cout << "10. Print the store's top 5 most popular items" << endl<<endl;
  cout << "11. Print all the customers who purchased a specific item" << endl<<endl;
  cout << "12. Get product recommendations for a specific customer" << endl<<endl;
  cout << "13. Print all items that have been purchased" << endl<<endl;
  cout << "14. Quit" << endl<<endl;
}

int main()
{
  Database storeDatabase;
  ifstream fileData;
  ifstream custFileData;
  ofstream saveFileData;
  string inventoryFileName;
  string customerFileName;
  string purchaseLineDataStr;
  string productLineDataStr;
  //Variables for adding a purchase for a customer
  string currCustEmail;
  string currCustName;
  string currPurchaseItem;
  string currPurchaseCategory;
  string currPurchaseColor;
  string currPurchaseSize;
  //variables for adding a product to inventory
  string currProductItem;
  string currProductCategory;
  string currProductColor;
  string currProductSize;

  //functionality for menu
  string choiceStr;
  int choice = 0;
  string saveChoiceString;
  int saveChoice = 0;
  string custFileName;
  string inventFileName;
  while (choice <= 14 && choice >= 0)
  {
    displayMenu();
    cin >> choice;
    switch (choice) {
      case 1:
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter an inventory file name" << endl;
        getline(cin, inventoryFileName);
        fileData.open(inventoryFileName);
        if (fileData.fail())
        {
          cout << "Failed to open file" << endl;
          break;
        }
        while (getline(fileData, productLineDataStr))
        {
          stringstream productLineData(productLineDataStr);
          getline(productLineData, currProductCategory, ',');
          getline(productLineData, currProductItem, ',');
          getline(productLineData, currProductColor, ',');
          getline(productLineData, currProductSize);
          storeDatabase.addProduct(currProductItem, currProductCategory, currProductColor, currProductSize);
        }
        cout << "Inventory items succesfully added" << endl;
        cout << endl << endl;
        fileData.close();
        break;
      case 2:
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter an customer purchases file name" << endl;
        getline(cin, customerFileName);
        custFileData.open(customerFileName);
        if (custFileData.fail())
        {
          cout << "Failed to open file" << endl;
          break;
        }
        while (getline(custFileData, purchaseLineDataStr))
        {
          stringstream purchaseLineData(purchaseLineDataStr);
          getline(purchaseLineData, currCustEmail, ',');
          getline(purchaseLineData, currCustName, ',');
          getline(purchaseLineData, currPurchaseCategory, ',');
          getline(purchaseLineData, currPurchaseItem, ',');
          getline(purchaseLineData, currPurchaseColor, ',');
          getline(purchaseLineData, currPurchaseSize);
          storeDatabase.addPurchase(currCustEmail, currCustName, currPurchaseItem, currPurchaseCategory, currPurchaseColor, currPurchaseSize);
        }
        cout << endl << "Customer purchases successfully added" << endl;
        custFileData.close();
        break;
      case 3:
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter the email of the customer you would like to add" << endl;
        getline(cin, currCustEmail);
        cout << "Enter the name of the customer you would like to add" << endl;
        getline(cin, currCustName);
        storeDatabase.addCustomer(currCustEmail, currCustName);
        break;
      case 4:
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter the purchasing customer's email" << endl;
        getline(cin, currCustEmail);
        cout << "Enter the purchasing customer's name" << endl;
        getline(cin, currCustName);
        cout << "Enter the name of the product being purchased" << endl;
        getline(cin, currPurchaseItem);
        cout << "Enter the category of the product being purchased" << endl;
        getline(cin, currPurchaseCategory);
        cout << "Enter the color of the item being purchased" << endl;
        getline(cin, currPurchaseColor);
        cout << "Enter the size of the item being purchased" << endl;
        getline(cin, currPurchaseSize);
        storeDatabase.addPurchase(currCustEmail, currCustName, currPurchaseItem, currPurchaseCategory, currPurchaseColor, currPurchaseSize);
        break;
      case 5:
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter the name of the product being added to inventory" << endl;
        getline(cin, currProductItem);
        cout << "Enter the category of the product being added to inventory" << endl;
        getline(cin, currProductCategory);
        cout << "Enter the color of the product being added to inventory" << endl;
        getline(cin, currProductColor);
        cout << "Enter the size of the product being added to inventory" << endl;
        getline(cin, currProductSize);
        storeDatabase.addProduct(currProductItem, currProductCategory, currProductColor, currProductSize);
        break;
      case 6:
        storeDatabase.allCustomers();
        break;
      case 7:
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter the email of the customer whose information you wish to view" << endl;
        getline(cin, currCustEmail);
        cout << endl;
        storeDatabase.specifcCust(currCustEmail);
        break;
      case 8:
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter the email of the customer who's information you wish to view" << endl;
        getline(cin, currCustEmail);
        storeDatabase.mostBoughtItems(currCustEmail);
        break;
      case 9:
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter the email of the customer who's information you wish to view" << endl;
        getline(cin, currCustEmail);
        storeDatabase.numberProductsOwned(currCustEmail);
        break;
      case 10:
        storeDatabase.mostPopularItems();
        break;
      case 11:
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter a product name" << endl;
        getline(cin, currProductItem);
        storeDatabase.whoBoughtItem(currProductItem);
        break;
      case 12:
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter the email of the customer you want to receive recommendations for" << endl;
        getline(cin, currCustEmail);
        storeDatabase.reccLikeProduct(currCustEmail);
        break;
      case 14:
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Do you want to save this database? 1. Yes 2. No" << endl;
        getline(cin, saveChoiceString);
        saveChoice = stoi(saveChoiceString);
        while (saveChoice != 1 && saveChoice != 2)
        {
          cout << "Invalid choice, please enter either 1 for Yes or 2 for No" << endl;
          cin.clear();
          cin.ignore(100, '\n');
          getline(cin, saveChoiceString);
          if (saveChoiceString != "1" && saveChoiceString != "2")
          {
            saveChoice = 0;
          }
          else
          {
            saveChoice = stoi(saveChoiceString);
          }
        }
        if (saveChoice == 1)
        {
          cin.clear();
          cin.ignore(100, '\n');
          cout << "Enter the name of the file you wish to write customer data to" << endl;
          getline(cin, custFileName);
          cout << "Enter the name of the file you wish to write inventory data to" << endl;
          getline(cin, inventFileName);
          storeDatabase.saveToFile(custFileName, inventFileName);
          cout << "Database saved. Goodbye!" << endl;
          return 0;
        }
        else
        {
          cout << "Goodbye!" << endl;
          return 0;
        }
        break;
        case 13:
          storeDatabase.printPurchased();
          break;
      default:
        cout << "Please enter a valid option" << endl;
        choice = 0;
        cin.clear();
        cin.ignore(100, '\n');
        break;
    }
  }
}
