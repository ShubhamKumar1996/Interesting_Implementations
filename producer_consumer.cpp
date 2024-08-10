// Program to implement solution of Producer-Consumer Problem

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>
#include <semaphore>

int buffer[5] = { 0 };
int pos = 0;
std::mutex bufferMutex;         // Ensures Mutual Exclusion while accessing buffer
std::counting_semaphore<5> emptyslot(5);    // Allows at max 5 threads to write into buffer at a time.
std::counting_semaphore<5> filledslot(0);   // Allows at max 5 threads to read from buffer at a time.


void produce() {
    for(int i=0; i<10; i++) {
        emptyslot.acquire();    // Ensures at max 5 producer threads enter into buffer at a time.
        bufferMutex.lock();     // Ensures Mutual Exclusion while accessing buffer
        std :: cout << std::endl << "Producer Thread: Producing at Position: " << pos << std::endl;
        buffer[pos] = 100;      // Write data into buffer
        pos++;                  // Update position
        std::cout << "Buffer Status: " << std:: endl;
        for(int i=0;i<5;i++) {  // Print buffer status
            std::cout << "buffer[" << i << "] = " << buffer[i] << ", ";
        }
        std::cout << std::endl << "Producer Thread: Produced" << std::endl;
        bufferMutex.unlock();   // Release lock on buffer
        filledslot.release();   // Update filledslot, increment filledslot by 1
        std::this_thread::sleep_for(std::chrono::microseconds(500));   // Added to increase chances of context switch.
    }
}

void consume() {
    for(int i=0;i<10;i++) {
        filledslot.acquire();   // Ensures at max 5 consumer threads enter into buffer at a time.
        bufferMutex.lock();     // Ensures Mutual Exclusion while accessing buffer
        std :: cout << std::endl << "Consumer Thread: Consuming at Position: " << pos - 1 << std::endl;
        buffer[pos - 1] = 0;    // Read data from buffer and modify it to 0
        pos--;                  // Update position
        std::cout << "Buffer Status: " << std:: endl;
        for(int i=0;i<5;i++) {  // Print buffer status
            std::cout << "buffer[" << i << "] = " << buffer[i] << ", ";
        }
        std::cout << std::endl << "Consumer Thread: Consumed" << std::endl;
        bufferMutex.unlock();   // Release lock on buffer
        emptyslot.release();    // Update emptyslot, increment emptyslot by 1
        std::this_thread::sleep_for(std::chrono::microseconds(500));    // Added to increase chances of context switch.
    }
}

int main()
{
    // Intentionally initiated consumer thread before producer thread to showcase that 
    // Consumer will not consume before Producer produce some data.
    std::thread consumerThread(consume);  
    std::thread producerThread(produce);
    
    producerThread.join();
    consumerThread.join();

    return 0;
}