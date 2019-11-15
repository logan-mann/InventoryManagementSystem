#include "Inventory.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include "InventoryHeap.hpp"

//implement member functions of the InventoryHashTable class here

//int I_tablesize;
//Product* *all_products;
//Product* *purchased_products;


//constructor
Inventory::Inventory(int Catagory)
{
    this->numCatagorys = Catagory;

    fullInventory = new InventoryProduct *[numCatagorys];

    for(int i = 0; i < numCatagorys; i++) fullInventory[i] = NULL;
    numProducts = 0;
}

//destructor
Inventory::~Inventory()
{
    for(int i = 0; i < numCatagorys; i++)
    {
        InventoryProduct *temp = fullInventory[i];

        while(temp != NULL)
        {
            InventoryProduct *del = temp;
            temp = temp->next;
            delete del;
        }
        delete temp;
    }
    delete [] fullInventory;
}

//turns string passed into int to be hashed
int turnIntoInt(std::string convrtString)
{
    int sum = 0;

    for(int i = 0; i < convrtString.length(); i++)
    {
        sum = sum + (convrtString[i] * i);
    }

    return sum;
}

//hash function for items, hashes category
unsigned int Inventory::HashProduct(std::string catagory)
{
    int icatagory = turnIntoInt(catagory);

    unsigned int hashValue = 5381;

    for(int i = 0; i < icatagory; i++)
    {
        hashValue = ((hashValue << 5) + hashValue) + icatagory;
    }

    hashValue %= numCatagorys;
    return hashValue;
}

//searches inventory for item passed, returns pointer if found, null if not found
InventoryProduct *Inventory::searchInventory(std::string productName, std::string findCatagory, std::string findColor, std::string findSize)
{
    int hash = HashProduct(findCatagory);

    InventoryProduct *temp = fullInventory[hash];

    while(temp != NULL)
    {
        if(temp->product_name == productName)
        {
            if(temp->color == findColor)
            {
                if(temp->size == findSize)
                {
                    return temp;
                }
            }
        }
        temp = temp->next;
    }

    return NULL;
}

//
void Inventory::print_purchased()
{
    for(int i = 0; i < numCatagorys; i++)
    {
        if(fullInventory[i] != NULL)
        {
            std::cout << "Product Catagory: " << fullInventory[i]->catagory << std::endl << std::endl;

            InventoryProduct *temp = fullInventory[i];

            while(temp != NULL)
            {
                if(temp->num_purchased != 0)
                {
                    std::cout << "Product Name: " << temp->product_name << std::endl;
                    std::cout << "  Color: " << temp->color << std::endl;
                    std::cout << "  Size: " << temp->size << std::endl;
                    std::cout << "  Number Purchased: " << temp->num_purchased << std::endl;
                }

                temp = temp->next;
            }
        }
    }
}

void Inventory::print_allProducts()
{
    for(int i = 0; i < numCatagorys; i++)
    {
        if(fullInventory[i] != NULL)
        {
            std::cout << "Product Catagory: " << fullInventory[i]->catagory << std::endl << std::endl;

            InventoryProduct *temp = fullInventory[i];

            while(temp != NULL)
            {
                std::cout << "  Product Name: " << temp->product_name << std::endl;
                std::cout << "  Color: " << temp->color << std::endl;
                std::cout << "  Size: " << temp->size << std::endl;
                std::cout << "  Number Purchased: " << temp->num_purchased << std::endl;
                std::cout << std::endl;
                temp = temp->next;
            }
        }
    }
}

void Inventory::print_numPurchased(std::string product_name, std::string catagory, std::string color, std::string size)
{
    InventoryProduct *temp = searchInventory(product_name, catagory, color, size);

    if(temp != NULL)
    {
        std::cout << "Number of: " << product_name << " in " << color << " size " << size << ": " << temp->num_purchased << std::endl;
    }

    else std::cout << "Product not found..." << std::endl;

}

bool Inventory::addProduct(std::string product_name, std::string catagory, std::string color, std::string size)
{
    InventoryProduct *temp = searchInventory(product_name, catagory, color, size);
    if(temp == NULL)
    {
        int hash = HashProduct(catagory);

        InventoryProduct *currenthead = fullInventory[hash];
        InventoryProduct *newNode = new InventoryProduct;
        newNode->product_name = product_name;
        newNode->catagory = catagory;
        newNode->color = color;
        newNode->size = size;
        newNode->num_purchased = 0;

        fullInventory[hash] = newNode;
        newNode->next = currenthead;
        numProducts++;
        return true;
    }

    return false;
}

void Inventory::addPurchse(std::string product_name, std::string catagory, std::string color, std::string size)
{
    InventoryProduct *temp = searchInventory(product_name, catagory, color, size);

    if(temp != NULL)
    {
        temp->num_purchased++;
        return;
    }

    else std::cout << "Cannot add purcahse because product is not in the database..." << std::endl;
 }

int Inventory::getNumProducts()
{
  return numProducts;
}

void Inventory::printLikeProducts(std::string productName, std::string category)
{
  int reccomendations = 0;
  int index = HashProduct(category);
  InventoryProduct* previousRecc = NULL;
  InventoryProduct* currProduct = fullInventory[index];
  while (currProduct != NULL && reccomendations < 3)
  {
    if (currProduct->product_name != productName)
    {
      if (previousRecc == NULL)
      {
        std::cout << currProduct->product_name << ", Color: " << currProduct->color << std::endl;
        previousRecc = currProduct;
        reccomendations++;
      }
      else if (previousRecc != NULL && currProduct->product_name != previousRecc->product_name)
      {
        std::cout << currProduct->product_name << ", Color: " << currProduct->color << std::endl;
        previousRecc = currProduct;
        reccomendations++;
      }
    }
    currProduct = currProduct->next;
  }
  std::cout << std::endl;
}

void Inventory::writeToFile(std::string writeFileName)
{
  std::ofstream writeFile;
  writeFile.open(writeFileName);
  InventoryProduct* currProduct;
  for (int i = 0; i < numCatagorys; i++)
  {
    currProduct = fullInventory[i];
    while (currProduct != NULL)
    {
      writeFile << currProduct->catagory << "," << currProduct->product_name << "," << currProduct->color << "," << currProduct->size << "\n";
      currProduct = currProduct->next;
    }
  }
}

InventoryProduct* Inventory::getProductAtIndex(int index)
{
  return fullInventory[index];
}

int Inventory::getTableSize()
{
  return numCatagorys;
}

void Inventory::incrememntNumPurchased(std::string product_name, std::string catagory, std::string color, std::string size)
{
  InventoryProduct* foundProduct = searchInventory(product_name, catagory, color, size);
  if (foundProduct != NULL)
  {
    foundProduct->num_purchased++;
  }
}
