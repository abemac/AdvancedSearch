OBJS = HashTable.o HashedObj.o
CC = g++ -std=c++11
DEBUG = -g
LFLAGS = -Wall $(DEBUG)
CFLAGS = $(LFLAGS) -c

output: $(OBJS) ../main.cpp
		$(CC) $(LFLAGS) ../main.cpp $(OBJS) -o ../run/mac_output
HashedObj.o: ../project2/HashedObj.h
		$(CC) $(CFLAGS) ../project2/HashedObj.cpp
HashTable.o: ../project2/HashedObj.h ../project2/HashTable.h
		$(CC) $(CFLAGS) ../project2/HashTable.cpp
clean:
	rm *.o ../run/mac_output
