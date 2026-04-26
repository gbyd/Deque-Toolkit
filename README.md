Names: Gabrielle Dement and AJ Hopkins

Date Made: 04/21/2026

Description:
The deque is a sequence container that has fast insertion and deletion at both its beginning and its end. This implementation uses a 2D blockmap to store data without having to move everything in memory around.

Division of Labor:

--- Gabrielle Dement: ---
- Designed the deque.h file.
- Created Makefile.

--- AJ Hopkins: ---
- Wrote the logic for the deque.cpp file.
- Wrote the main.cpp driver to run automated tests.
- Handled math for the indexing and blockmap resizing.

How to Run:
1. Type 'make' to compile.
2. Run './deque'
4. Run 'make clean' to remove objects and the executable.

Design Decisions:

--- deque.h ---
- I used a 'T** blockmap' so we could have a dynamic array of pointers.
- I made sure to include the 'const' keyword on the getter functions so they don't accidentally change any data.A README.md describing your implementation (try to mimic the STL documentation) and describe what seems to work correctly, and any bugs that you encountered that you could not fix in time.  Make sure to include a section on how you divided work for this assignment!

--- deque.cpp ---
- Intialized the first element in the middle of the blockmap so the deque has room to grow in both directions before needing a full resize.
- A new block (row) is only created with new T[] when an elkemnt actually needs to be placed there to save memory.
- For resizeBlockmap(), the map size doubles and an offset is used to re center the existin pointers to help prevent the map from hitting a boundary immediately after a resize.

--- main.cpp ---
- Used the random std::rand() to simulate 5,000 mixed operations in a random order. 
- Used check() that tracks passed and failed tests instead of just printing the values. Makes the output cleaner and that the final count is clear.
- Pushed 10,000 elements to both the front and back to trigger resizeBlockmap() multiple times. Doing so confirmed that the 2D memory expansion logic doesn't lose data even with repeatiting resizes.

Complexity and Performance:
- Accessing any item with the [] operator happens in constant time.
- Pushing or popping is also constant time.
- The blockmap handles all the growth, so we only have to allocate new memory when a specific block gets totally full.

Challenges:
- Memory management is always something you have to be careful with to avoid leaks; especially with 2D arrays since you have to keep up with two different dimensions of pointers.
