# Producer-Consumer Problem
## Description of Problem
1.  There is a buffer of n slots and each slot is capable of storing one unit of data.
2.  There are two processes running namely, producer & consumer, which are operating on the same buffer.
3.  The producer tries to insert data into an empty slot of the buffer.
4.  The consumer tries to remove data from an filled slot of the buffer.
5.  The producer must not insert data when the buffer is full.
6.  The consumer must not remove data when the buffer is empty.
7.  The producer and consumer should not insert & remove data simultaneously.

## Observations From Description:
1.  Create a buffer of size n (n=5)
2.  Create two processes or threads, one is called producer, another is called consumer.
3.  As both the process are operating on same buffer, accessing this buffer become critical section.
4.  Producer should verify empty slots before insertion.
5.  Consumer should verify filled slots before removal.
6.  Producer and consumer should not insert & remove data simultaneously. Hence, need to introduce mutual exclusion.

## Conclusions & Psuedo Algorithm:
1.  int buffer[5];
2.  int pos = 0;
3.  Mutex buffermutex;
4.  Semaphore emptySlot = 5;
5.  Semaphore filledSlot = 0;
6.  Create producer thread & consumer thread.
7.  Producer thread
    1.  Verify emptyslots using semaphore
    2.  buffermutex lock
    3.  Insert data
    4.  buffermutex unlock
    5.  update filledSlot using semaphore
8.  Consumer thread
    1.  Verify filledslots using semaphore
    2.  buffermutex lock
    3.  Remove data
    4.  buffermutex unlock
    5.  update emptyslot using semaphore


## Instructions to Run Solution
1.  C++ compiler that support atleast C++20.
2.  Tested with g++ version 14.2.0 in windows OS.
3.  Commands to run program:
    1.  g++ -std=c++20 producer_consumer.cpp -o  producer_consumer
    2.  producer_consumer.exe
