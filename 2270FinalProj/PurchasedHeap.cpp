#include "PurchasedHeap.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

void swap(Product* node1, Product* node2)
{
  Product temp = *node1;
  *node1 = *node2;
  *node2 = temp;
}

PurchasedHeap::PurchasedHeap(int heapSize)
{
  currentSize = 0;
  this->heapSize = heapSize;
  productHeap = new Product*[heapSize];
  for (int i = 0; i < heapSize; i++)
  {
    productHeap[i] = NULL;
  }
}

PurchasedHeap::~PurchasedHeap()
{
  for (int i = 0; i < heapSize; i++)
  {
    if (productHeap[i] != NULL)
    {
      delete productHeap[i];
    }
  }
  delete [] productHeap;
}

void PurchasedHeap::printHeap()
{
  for (int i = 0; i < currentSize; i++)
  {
    std::cout << productHeap[i]->product_name << ", Category: " << productHeap[i]->catagory << ", Color: " << productHeap[i]->color << ", Size: " << productHeap[i]->size <<  ", Number purchased: " << productHeap[i]->num_purchased << std::endl;
  }
}

void PurchasedHeap::addToHeap(Product* addProduct)
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

Product* PurchasedHeap::removeFromHeap()
{
  if (currentSize > 0)
  {
    Product* removedProduct = productHeap[0];
    productHeap[0] = productHeap[currentSize - 1];
    currentSize--;
    repairDownward(0);
    return removedProduct;
  }
  else
  {
    std::cout << "Heap empty, cannot dequeue" << std::endl;
    return NULL;
  }
}

Product* PurchasedHeap::peekProduct()
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

bool PurchasedHeap::isFull()
{
  return (currentSize == heapSize);
}

bool PurchasedHeap::isEmpty()
{
  return (currentSize == 0);
}

int PurchasedHeap::parent(int nodeIndex)
{
  return ((nodeIndex-1) / 2);
}

int PurchasedHeap::leftChild(int nodeIndex)
{
  return ((nodeIndex*2) + 1);
}

int PurchasedHeap::rightChild(int nodeIndex)
{
  return ((nodeIndex*2) + 2);
}

void PurchasedHeap::repairUpward(int nodeIndex)
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

void PurchasedHeap::repairDownward(int nodeIndex)
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


Product* PurchasedHeap::findProduct(std::string productName)
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

void PurchasedHeap::repairFromChangedProduct(Product* repairProduct)
{
  int i = 0;
  while (i < currentSize && (productHeap[i]->product_name != repairProduct->product_name || productHeap[i]->color != repairProduct->color || productHeap[i]->size != repairProduct->size || productHeap[i]->catagory != repairProduct->catagory))
  {
      i++;
  }
  repairUpward(i);
}

int PurchasedHeap::getCurrentSize()
{
  return currentSize;
}


void PurchasedHeap::printTopThree()
{
  int i = 0;
  if (productHeap[i] != NULL)
  {
    std::cout << productHeap[i]->product_name << ", Category: " << productHeap[i]->catagory << ", Color: " << productHeap[i]->color << ", Size: " << productHeap[i]->size << ", Number Purchased: " << productHeap[i]->num_purchased << std::endl;
  }
  i = leftChild(0);
  if (productHeap[i] != NULL)
  {
    std::cout << productHeap[i]->product_name << ", Category: " << productHeap[i]->catagory << ", Color: " << productHeap[i]->color << ", Size: " << productHeap[i]->size << ", Number Purchased: " << productHeap[i]->num_purchased << std::endl;
  }
  i = rightChild(0);
  if (productHeap[i] != NULL)
  {
    std::cout << productHeap[i]->product_name << ", Category: " << productHeap[i]->catagory << ", Color: " << productHeap[i]->color << ", Size: " << productHeap[i]->size << ", Number Purchased: " << productHeap[i]->num_purchased << std::endl;
  }
}

void PurchasedHeap::writeToFile(std::string writeFileName, std::string custEmail, std::string custName)
{
  std::ofstream writeFile;
  writeFile.open(writeFileName, std::ios_base::app);
  for (int i = 0; i < currentSize; i++)
  {
    writeFile << custEmail << "," << custName << "," << productHeap[i]->catagory << "," <<  productHeap[i]->product_name << "," << productHeap[i]->color << "," << productHeap[i]->size << "\n";
  }
  writeFile.close();
}
