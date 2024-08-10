# Reader-Writer Process Synchronization Problem
## Description of Problem
1.  A database is to be shared among several concurrent processes.
2.  Some of these processes may only want to read the database, whereas others may want to read and write to the database.
3.  We can distinguish these processes as readers & writers.
4.  If two readers access the shared data simultaneously, result & database will stay consistent.
5.  If a writer and any other thread (reader or writer) access the database simultaneously, result & database may become inconsistent.
6.  To ensure consistency, writers must have exclusive access to the shared database.
7.  Design a solution such that both the processes (readers & writers) are synchronized (where required) and consistency of the database is maintained.

## Observations From Description:
1.  Create multiple instances of reader thread & writer thread.
2.  Writer thread should be allowed to access only when no other writer and reader thread is accessing database. (Mutex required)
3.  Reader thread should be allowed to access database only when no writer thread is accessing database.
4.  Multiple readers should be allowed to access database concurrently.
5.  Writer thread requires mutual exclusion with any other thread.
6.  Reader thread requires mutual exclusion from writer thread. That means unless and until any writer thread is executing, reader thread have to wait. And once reader thread start execution other reader threads can execute simultaneously but writer thread have to wait.

## Conclusions & Psuedo Algorithm:
1.  Mutex writerMutex;
2.  Mutex ReaderCountMutex;
3.  int ReaderCount = 0;
4.  Writer Thread
    1.  Lock writerMutex
    2.  Perform write operation on DB
    3.  Unlock writerMutex
5.  Reader Thread
    1.  Lock ReaderCountMutex
    2.  Increment ReaderCount
    3.  If (ReaderCount == 1) then Lock writerMutex
    4.  Unlock ReaderCountMutex
    5.  Perform read operation on DB
    6.  Lock ReaderCountMutex
    7.  Decrement ReaderCount
    8.  If (ReaderCount == 0) then Unlock writerMutex
    9.  Unlock ReaderCountMutex;

## Instructions to Run Solution
1.  C++ compiler that support atleast C++20.
2.  Tested with g++ version 14.2.0 in windows OS.
3.  Commands to run program:
    1.  g++ -std=c++20 reader_writer.cpp -o reader_writer
    2.  reader_writer.exe
