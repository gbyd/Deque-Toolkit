# file Makefile
# author Gabbie Dement
# date 2026-04-21
# brief Builds the deque

CC = g++
TARGET = deque
CFLAGS = -c -Wall -Wextra

all: $(TARGET)

$(TARGET): main.o deque.o
	$(CC) -g main.o deque.o -o $(TARGET)

main.o: main.cpp deque.h
	$(CC) $(CFLAGS) main.cpp

deque.o: deque.cpp deque.h
	$(CC) $(CFLAGS) deque.cpp

clean:
	$(RM) $(TARGET) *.o *~
