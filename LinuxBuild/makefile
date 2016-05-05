OBJS = HashTable.o HashedObj.o
CC = g++ -std=c++11
DEBUG = -g
LFLAGS = -Wall $(DEBUG)
CFLAGS = $(LFLAGS) -c

output: $(OBJS) ../main.cpp
		$(CC) $(LFLAGS) ../main.cpp $(OBJS) -o ../run/linux_output
HashedObj.o: ../HashedObj.h
		$(CC) $(CFLAGS) ../HashedObj.cpp
HashTable.o: ../HashedObj.h ../HashTable.h
		$(CC) $(CFLAGS) ../HashTable.cpp
clean:
	rm *.o ../run/linux_output
