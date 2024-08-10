#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

std :: mutex writerMutex;       // Ensures mutual exclusion for writer thread
std :: mutex readerCountMutex;  // Ensures only one reader thread modify read count.
int readerCount = 0;            // Counter to keep track of number of reader thread executing in critical section

void write(int threadId) {
    writerMutex.lock();         // Ensure no other writer thread enter into critical section.
    std::cout << std::endl << "Writer Thread ID: " << threadId << " Entry.";
    std::cout << std::endl << "Writer Thread ID: " << threadId << " Performing Write Operation";
    std::cout << std::endl << "Writer Thread ID: " << threadId << " Exit." << std::endl;
    writerMutex.unlock();       // Allows other writer & reader thread to enter into critical section.
}

void read(int threadId) {
    readerCountMutex.lock();    // Mutual Exclusion for modifying read counter
    std::cout << std::endl << "Reader Thread ID: " << threadId << " Entry.";
    readerCount++;
    if(readerCount == 1) {      // Ensure writeMutex lock happens only when this is first reader thread in a batch of simultaneously executing reader threads.
        writerMutex.lock();
    }
    readerCountMutex.unlock();  
    
    std::cout << std::endl << "Reader Thread ID: " << threadId << " Performing Read Operation"; // Simulate DB opeartion
    std::this_thread::sleep_for(std::chrono::microseconds(500));

    readerCountMutex.lock();
    readerCount--;
    if(readerCount == 0) {      // Ensure writeMutex is unlocked only when this is the last reader thread in a batch of simultaneously executing reader threads.
        writerMutex.unlock();
    }
    std::cout << std::endl << "Reader Thread ID: " << threadId << " Exit." << std::endl;
    readerCountMutex.unlock();
}

int main() {
    std::vector<std::thread> threads;   
    
    // Starting 5 Writer & 5 Reader Threads.
    for(int i=1;i<=5;i++) {
        threads.emplace_back(write, i);     //Initializing threads
        threads.emplace_back(read, i);
    }

    for(int i=0;i<10;i++) {
        threads[i].join();
    }

    return 0;
}