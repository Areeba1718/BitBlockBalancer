#include <iostream>
using namespace std;

class BitBlockBalancer {
private:
    bool* memoryBlocks;  
    int totalBlocks;

public:
    BitBlockBalancer(int totalBlocks) : totalBlocks(totalBlocks) {
        memoryBlocks = new bool[totalBlocks]; 
        for (int i = 0; i < totalBlocks; i++)
        {
            memoryBlocks[i] = false;  
        }
    }
    ~BitBlockBalancer() {
        delete[] memoryBlocks;
    }
    int allocateBlock() {
        for (int i = 0; i < totalBlocks; i++) {
            if (!memoryBlocks[i]) {
                memoryBlocks[i] = true;  
                cout << "Allocated block at index: " << i << endl;
                return i;
            }
        }
        cout << "Error: No free blocks available!" << endl;
        return -1; 
    }

    
    void displayMemory() {
        cout << "Memory Blocks (0 = free, 1 = allocated): " << endl;
        for (int i = 0; i < totalBlocks; i++) {
            cout << memoryBlocks[i] << " ";
        }
        cout << endl;
    }

    void defragmentMemory() 
    {
        int writePointer = 0;
        for (int readPointer = 0; readPointer < totalBlocks; ++readPointer) 
        {
            if (memoryBlocks[readPointer]) 
            {
                if (readPointer != writePointer) 
                {
                    memoryBlocks[writePointer] = true;   
                    memoryBlocks[readPointer] = false;  
                }
                ++writePointer;
            }
        }
        cout << "Memory defragmented." << endl;
    }
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

int main()
{
    BitBlockBalancer memoryManager(10);
    memoryManager.displayMemory();
    memoryManager.allocateBlock();
    memoryManager.allocateBlock();
    memoryManager.allocateBlock();
    memoryManager.displayMemory();
    memoryManager.displayMemory();
    memoryManager.allocateBlock();
    memoryManager.defragmentMemory();
    memoryManager.displayMemory(); 
    cout << "Free Blocks: " << memoryManager.countFreeBlocks() << endl;

    return 0;
}
