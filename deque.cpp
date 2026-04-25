/**
 * @file deque.cpp
 * @author AJ Hopkins
 * @date 2026-04-22
 * @brief Implementation of custom double ended queue using 2D blockmap
 *
 * Implements all deque operations using a dynamic 2D blockmap structure.
 */
 
#include "deque.h"
#include <iostream>
 
// Default block size (number of elements per block)
static const int DEFAULT_BLOCK_SIZE = 8;
// Initial number of block pointers in the map
static const int DEFAULT_MAP_SIZE = 8;
 
deque::deque() {
  blockSize = DEFAULT_BLOCK_SIZE;
  mapSize = DEFAULT_MAP_SIZE;
  numElements = 0;
 
  blockmap = new T*[mapSize];
  for (int i = 0; i < mapSize; i++)
    blockmap[i] = nullptr;
 
  // Start in the middle of the map so we can grow both ways
  firstBlock = mapSize / 2;
  lastBlock  = mapSize / 2;
  firstElement = blockSize / 2;
  lastElement  = blockSize / 2 - 1; // empty: lastElement is one before firstElement
}
 
deque::~deque() {
  for (int i = 0; i < mapSize; i++) {
    if (blockmap[i] != nullptr)
      delete[] blockmap[i];
  }
  delete[] blockmap;
}
 
// Grow the blockmap when we've run out of rows at either end
void deque::resizeBlockmap() {
  int newMapSize = mapSize * 2;
  T** newMap = new T*[newMapSize];
  for (int i = 0; i < newMapSize; i++)
    newMap[i] = nullptr;

  // Copy existing block pointers into the middle of the new map
  int offset = (newMapSize - mapSize) / 2;
  for (int i = 0; i < mapSize; i++)
    newMap[i + offset] = blockmap[i];

  delete[] blockmap;
  blockmap = newMap;

  firstBlock += offset;
  lastBlock  += offset;
  mapSize = newMapSize;
}

void deque::push_back(T item) {
  // Advance lastElement; if we fall off the end of the block, move to the next block
  if (numElements == 0) {
    // First element: allocate starting block if needed
    if (blockmap[lastBlock] == nullptr)
      blockmap[lastBlock] = new T[blockSize];
    lastElement = blockSize / 2;
    firstElement = blockSize / 2;
    blockmap[lastBlock][lastElement] = item;
  } else {
    lastElement++;
    if (lastElement >= blockSize) {
      // Need the next block row
      lastBlock++;
      if (lastBlock >= mapSize)
	resizeBlockmap();
      if (blockmap[lastBlock] == nullptr)
	blockmap[lastBlock] = new T[blockSize];
      lastElement = 0;
    }
    blockmap[lastBlock][lastElement] = item;
  }
  numElements++;
}

void deque::push_front(T item) {
  if (numElements == 0) {
    if (blockmap[firstBlock] == nullptr)
      blockmap[firstBlock] = new T[blockSize];
    firstElement = blockSize / 2;
    lastElement  = blockSize / 2;
    blockmap[firstBlock][firstElement] = item;
  } else {
    firstElement--;
    if (firstElement < 0) {
      // Need the previous block row
      firstBlock--;
      if (firstBlock < 0) {
	resizeBlockmap();
      }
      if (blockmap[firstBlock] == nullptr)
	blockmap[firstBlock] = new T[blockSize];
      firstElement = blockSize - 1;
    }
    blockmap[firstBlock][firstElement] = item;
  }
  numElements++;
}

void deque::pop_front() {
  if (numElements == 0) return;

  numElements--;
  if (numElements == 0) {
    firstElement = blockSize / 2;
    lastElement  = blockSize / 2 - 1;
    return;
  }

  firstElement++;
  if (firstElement >= blockSize) {
    firstBlock++;
    firstElement = 0;
  }
}

void deque::pop_back() {
  if (numElements == 0) return;

  numElements--;
  if (numElements == 0) {
    firstElement = blockSize / 2;
    lastElement  = blockSize / 2 - 1;
    return;
  }

  lastElement--;
  if (lastElement < 0) {
    lastBlock--;
    lastElement = blockSize - 1;
  }
}

T deque::front() const {
  return blockmap[firstBlock][firstElement];
}

T deque::back() const {
  return blockmap[lastBlock][lastElement];
}

T& deque::operator[](int index) {
  // Map logical index to (block, element) coordinates
  int absIndex = (firstBlock * blockSize + firstElement) + index;
  int block = absIndex / blockSize;
  int elem  = absIndex % blockSize;
  return blockmap[block][elem];
}

bool deque::empty() const {
  return numElements == 0;
}

int deque::size() const {
  return numElements;
}
