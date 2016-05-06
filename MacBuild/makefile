OBJS = HashTable.o HashedObj.o Graph.o Node.o
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
Graph.o: ../project1/Graph.cpp ../project1/Graph.h
		$(CC) $(CFLAGS) ../project1/Graph.cpp
Node.o: ../project1/Node.cpp ../project1/Node.h
		$(CC) $(CFLAGS) ../project1/Node.cpp
clean:
	rm *.o ../run/mac_output
