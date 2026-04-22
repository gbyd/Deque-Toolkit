/**
 * @file deque.h
 * @author Gabbie Dement
 * @date 2026-04-21
 * @brief Definition of custom double ended que using 2D blockmap
 * 
 * Defienes a deque structure using a dynamic array of pointers.
 */

#ifndef DEQUE_H
#define DEQUE_H

typedef int T;


/**
 * Manages a 2D memory structure for dynamic growth at both ends without full reallocation to be possible. Has the core functionality for indexing and standard container operations like push and pop.
 *
 * @class deque{ deque.h "deque-toolkit/deque.h"
 * @brief Container class implementing a double ended queue using a blockmap.
 *
 */
class deque{
 private:
  T** blockmap; //2d array of pointers
  int mapSize; //capacity of blockmap (rows)
  int blockSize; //capacity of each individual block (columns)

  //tracking the range of elements
  int firstBlock; //index of row containing the first element
  int firstElement; //index of the column in that row
  int lastBlock; //index of row containing the last element
  int lastElement; //index of the column in that row

  int numElements; //count


/**
 * Reallocates the blockmap to a larger size to allow more blocks
 *
 * @pre Front or back boundary of the map has been reached
 * @return void 
 * @post Map capacity is increased
 * 
 */
  void resizeBlockmap(); //helper for when blockmap is full

 public:

/**
 * Intializes empty deque with base blockmap and default pointers
 *
 * @pre 
 * @post A valid deque object is created with allocated memory for the map
 * 
 */
  deque();

/**
 * Deallocates all blocks and primary blockmap
 *
 * @pre Deque object exists
 * @post All dynamically allocated memory is freed
 * 
 */
  ~deque();


/**
 * Adds new element at front of the deque
 *
 * @param T item Value of type T to be added to the container
 * @pre Valid item of type T is provided
 * @return void 
 * @post Size increase by one and new memory is allocated if the block is full
 * 
 */
  void push_front(T item);

/**
 * Adds new element at back of the deque
 *
 * @param T item Value of type T to be added to the container
 * @pre Valid item of type T is provided
 * @return void 
 * @post Size increases by one and new memory is allocated if the blcok is full
 * 
 */
  void push_back(T item);

/**
 * Removes element from front of the deque
 *
 * @pre Deque can't be empty
 * @return void 
 * @post Size decreases by one and indexes are updated to the next valid element
 * 
 */
  void pop_front();

/**
 * Removes element from back of the deque
 *
 * @pre Deque can't be empty
 * @return void 
 * @post Size decreases by one and indexes are updated to the next valid element
 * 
 */
  void pop_back();

  //element access

/**
 * Accesses element at the front of the deque
 *
 * @pre Deque can't be empty
 * @return T Copy of the item at the front
 * @post Deque is unchanged
 * 
 */
  T front() const;

/**
 * Accesses element at the back of the deque
 *
 * @pre Deque can't be empty
 * @return T Copy of the item at the back
 * @post Deque is unchanged
 * 
 */
  T back() const;

/**
 * Gives random access to elements
 *
 * @param int index Position of the element
 * @pre Index must be valid
 * @return T& A reference to the element at the specified index
 * @post Returns a reference to the item at that position
 * 
 */
  T& operator[](int index);

  //capacity

/**
 * Checks if container is holding any elements
 *
 * @pre 
 * @return bool True if size is 0, false if not
 * @post Deque doesn't change
 * 
 */
  bool empty() const;

/**
 * Returns the total count of elements stored in the deque
 *
 * @pre 
 * @return int The count of stored elements
 * @post Deque doesn't change
 * 
 */
  int size() const;
};

#endif
