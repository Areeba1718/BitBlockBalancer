#include <iostream>
using namespace std;

class BitBlockBalancer {
private:
    bool* memoryBlocks;  // Dynamically allocated array of memory blocks
    int totalBlocks;

public:
    // Constructor to initialize memory manager with total blocks
    BitBlockBalancer(int totalBlocks) : totalBlocks(totalBlocks) {
        memoryBlocks = new bool[totalBlocks];  // Dynamically allocate the array
        for (int i = 0; i < totalBlocks; i++) {
            memoryBlocks[i] = false;  // Initialize all blocks to be free
        }
    }

    // Destructor to free dynamically allocated memory
    ~BitBlockBalancer() {
        delete[] memoryBlocks;
    }

    // Function to allocate memory block using first-fit strategy
    int allocateBlock() {
        for (int i = 0; i < totalBlocks; i++) {
            if (!memoryBlocks[i]) {
                memoryBlocks[i] = true;  // Mark block as allocated
                cout << "Allocated block at index: " << i << endl;
                return i;  // Return the index of the allocated block
            }
        }
        cout << "Error: No free blocks available!" << endl;
        return -1;  // Allocation failed
    }

    // Function to free memory block
    void freeBlock(int index) {
        if (index < 0 || index >= totalBlocks) {
            cout << "Error: Invalid block index!" << endl;
            return;
        }
        if (!memoryBlocks[index]) {
            cout << "Error: Block at index " << index << " is already free!" << endl;
        }
        else {
            memoryBlocks[index] = false;  // Mark block as free
            cout << "Freed block at index: " << index << endl;
        }
    }

    // Function to display the current state of memory blocks
    void displayMemory() {
        cout << "Memory Blocks (0 = free, 1 = allocated): " << endl;
        for (int i = 0; i < totalBlocks; i++) {
            cout << memoryBlocks[i] << " ";
        }
        cout << endl;
    }

    // Function to defragment memory by moving allocated blocks together
    void defragmentMemory() {
        int writePointer = 0;
        for (int readPointer = 0; readPointer < totalBlocks; ++readPointer) {
            if (memoryBlocks[readPointer]) {
                if (readPointer != writePointer) {
                    memoryBlocks[writePointer] = true;   // Move allocated block forward
                    memoryBlocks[readPointer] = false;   // Mark the old spot as free
                }
                ++writePointer;
            }
        }
        cout << "Memory defragmented." << endl;
    }

    // Function to check the number of free blocks
    int countFreeBlocks() {
        int freeBlocks = 0;
        for (int i = 0; i < totalBlocks; i++) {
            if (!memoryBlocks[i]) {
                freeBlocks++;
            }
        }
        return freeBlocks;
    }
};

int main() {
    // Initialize BitBlockBalancer with 10 memory blocks
    BitBlockBalancer memoryManager(10);

    // Display initial state of memory
    memoryManager.displayMemory();

    // Allocate a few memory blocks
    memoryManager.allocateBlock();
    memoryManager.allocateBlock();
    memoryManager.allocateBlock();

    // Display state of memory after allocation
    memoryManager.displayMemory();

    // Free one block
    memoryManager.freeBlock(1);

    // Display state of memory after freeing
    memoryManager.displayMemory();

    // Allocate another block
    memoryManager.allocateBlock();

    // Defragment the memory
    memoryManager.defragmentMemory();

    // Display memory after defragmentation
    memoryManager.displayMemory();

    // Check the number of free blocks
    cout << "Free Blocks: " << memoryManager.countFreeBlocks() << endl;

    return 0;
}
