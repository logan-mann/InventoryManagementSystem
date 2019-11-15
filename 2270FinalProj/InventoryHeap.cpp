#include "InventoryHeap.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

void swap(InventoryProduct* node1, InventoryProduct* node2)
{
  InventoryProduct temp = *node1;
  *node1 = *node2;
  *node2 = temp;
}

InventoryHeap::InventoryHeap(int heapSize)
{
  currentSize = 0;
  this->heapSize = heapSize;
  productHeap = new InventoryProduct*[heapSize];
  for (int i = 0; i < heapSize; i++)
  {
    productHeap[i] = NULL;
  }
}

InventoryHeap::~InventoryHeap()
{
  delete [] productHeap;
}

void InventoryHeap::printHeap()
{
  for (int i = 0; i < currentSize; i++)
  {
    std::cout << productHeap[i]->product_name << ", Category: " << productHeap[i]->catagory << ", Color: " << productHeap[i]->color << ", Size: " << productHeap[i]->size << " Num purchased: " << productHeap[i]->num_purchased << std::endl;
  }
}

void InventoryHeap::addToHeap(InventoryProduct* addProduct)
{
  if (!isFull())
  {
    productHeap[currentSize] = addProduct;
    currentSize++;
    repairUpward(currentSize-1);
  }
  else
  {
    std::cout << "Heap full cannot add" << std::endl;
  }
}

InventoryProduct* InventoryHeap::removeFromHeap()
{
  if (currentSize > 0)
  {
    InventoryProduct* removedProduct = productHeap[0];
    productHeap[0] = productHeap[currentSize - 1];
    currentSize--;
    repairDownward(0);
    return removedProduct;
  }
  else
  {
    std::cout << "No additional products in inventory" << std::endl;
    return NULL;
  }
}

InventoryProduct* InventoryHeap::peekProduct()
{
  if (!isEmpty())
  {
    return productHeap[0];
  }
  else
  {
    std::cout << "heap empty, cannot peek" << std::endl;
    return NULL;
  }
}

bool InventoryHeap::isFull()
{
  return (currentSize == heapSize);
}

bool InventoryHeap::isEmpty()
{
  return (currentSize == 0);
}

int InventoryHeap::parent(int nodeIndex)
{
  return ((nodeIndex-1) / 2);
}

int InventoryHeap::leftChild(int nodeIndex)
{
  return ((nodeIndex*2) + 1);
}

int InventoryHeap::rightChild(int nodeIndex)
{
  return ((nodeIndex*2) + 2);
}

void InventoryHeap::repairUpward(int nodeIndex)
{
  while (nodeIndex > 0)
  {
    if (productHeap[parent(nodeIndex)]->num_purchased < productHeap[nodeIndex]->num_purchased)
    {
      swap(productHeap[parent(nodeIndex)], productHeap[nodeIndex]);
    }
    nodeIndex = parent(nodeIndex);
  }
}

void InventoryHeap::repairDownward(int nodeIndex)
{
  int largest = nodeIndex;
  if (leftChild(nodeIndex) < currentSize && productHeap[leftChild(nodeIndex)]->num_purchased > productHeap[nodeIndex]->num_purchased)
  {
    largest = leftChild(nodeIndex);
  }
  if (rightChild(nodeIndex) < currentSize && productHeap[rightChild(nodeIndex)]->num_purchased > productHeap[largest]->num_purchased)
  {
    largest = rightChild(nodeIndex);
  }
  if (largest != nodeIndex)
  {
    swap(productHeap[largest], productHeap[nodeIndex]);
    repairDownward(largest);
  }
}


InventoryProduct* InventoryHeap::findProduct(std::string productName)
{
  int index = 0;
  while (index < currentSize)
  {
    if (productHeap[index] != NULL)
    {
      if (productHeap[index]->product_name == productName)
      {
        return productHeap[index];
      }
    }
    index++;
  }
  return NULL;
}
int InventoryHeap::getCurrentSize()
{
  return currentSize;
}


void InventoryHeap::printTopThree()
{
  int i = 0;
  std::cout << productHeap[i]->product_name << ", Category: " << productHeap[i]->catagory << ", Color: " << productHeap[i]->color << ", Size: " << productHeap[i]->size << ", Number Purchased: " << productHeap[i]->num_purchased << std::endl;
  i = leftChild(0);
  std::cout << productHeap[i]->product_name << ", Category: " << productHeap[i]->catagory << ", Color: " << productHeap[i]->color << ", Size: " << productHeap[i]->size << ", Number Purchased: " << productHeap[i]->num_purchased << std::endl;
  i = rightChild(0);
  std::cout << productHeap[i]->product_name << ", Category: " << productHeap[i]->catagory << ", Color: " << productHeap[i]->color << ", Size: " << productHeap[i]->size << ", Number Purchased: " << productHeap[i]->num_purchased << std::endl;
}

void InventoryHeap::writeToFile(std::string writeFileName, std::string custEmail, std::string custName)
{
  std::ofstream writeFile;
  writeFile.open(writeFileName, std::ios_base::app);
  for (int i = 0; i < currentSize; i++)
  {
    writeFile << custEmail << "," << custName << "," << productHeap[i]->catagory << "," <<  productHeap[i]->product_name << "," << productHeap[i]->color << "," << productHeap[i]->size << "\n";
  }
  writeFile.close();
}
