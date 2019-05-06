#include <stdio.h>
#include <stdbool.h>

#define MEMORY_SIZE 25000

char* MyMalloc(size_t size);
char* searchBlock(size_t size);
void splitBlock(char* block, size_t size);
void MyFree(char* address);

char memory[MEMORY_SIZE] = {'\0'};

char* base = memory;

char freeMem = 'f';
char allocateMem = 'a';

char* MyMalloc(size_t size) {

    if(size<=0) {
        return NULL;
    }

    if(!*base) {
        *base = freeMem;
        *(int*)(base+1) = MEMORY_SIZE;
    }

    char* block = searchBlock(size);

    if(block) {
        splitBlock(block,size);
        printf("Allocating block of size %lu\n",size);
        return block;
    }
    else {
        printf("Can not allocate a block\n");
        return NULL;
    }

}

char* searchBlock(size_t size) {

    char* movingPointer = base;
    int currentBlockSize = 0;
    int minSize = 0;
    char* minAdr = NULL;

    while(true) {

        currentBlockSize = *(int*)(movingPointer+1);

        if(*movingPointer == freeMem && currentBlockSize >= size+5) {
            if(minSize == 0) {
                minSize = currentBlockSize;
                minAdr = movingPointer;
            }
            else {
                if(minSize > currentBlockSize) {
                    minSize = currentBlockSize;
                    minAdr = movingPointer;
                }
            }
            movingPointer = movingPointer + currentBlockSize;
        }
        else {
            if(movingPointer + currentBlockSize + size + 5 > memory + MEMORY_SIZE - 1) {
                if(minSize == 0) {
                    printf("There is not enough space in the memory!\n");
                }
                break;
            }
            movingPointer = movingPointer + currentBlockSize;
        }

    }

    return minAdr;
    
}

void splitBlock(char* block, size_t size) {

    int blockSize = *(int*)(block+1);
    char* temp;
    int newBlockSize;

    if(blockSize == size+5) {
        *block = allocateMem;
    }
    else {

        newBlockSize = blockSize - size - 5;
        temp = block + size + 5;
        *temp = freeMem;
        *(int*)(temp+1) = newBlockSize;
        *block = allocateMem;
        *(int*)(block+1) = size + 5;

    }

}

void MyFree(char* address) {
    
    char* movingPointer = base;
    int currentBlockSize = 0;
    char* prevBlock = NULL;
    int prevBlockSize = 0;
    bool found = false;

    while(true) {

        currentBlockSize = *(int*)(movingPointer+1);

        if(movingPointer==base && movingPointer==address) {
            *movingPointer = freeMem;
            char* nextBlock = movingPointer + currentBlockSize;

            if(*nextBlock == freeMem) {
                *(int*)(movingPointer+1) = currentBlockSize + *(int*)(nextBlock+1);
                *(int*)(nextBlock+1) = NULL;
                *(nextBlock) = NULL;
            }
            found = true;
            break;
        }
        else if(movingPointer==address && (movingPointer+currentBlockSize-1 == memory+MEMORY_SIZE-1)) {
            if(*prevBlock == freeMem) {
                *(int*)(prevBlock+1) = prevBlockSize + currentBlockSize;
                *movingPointer = NULL;
                *(int*)(movingPointer+1) = NULL;
            }
            else {
                *movingPointer = freeMem;
            }
            found = true;
            break;
        }
        else if(movingPointer == address) {
            char* nextBlock = movingPointer + currentBlockSize;
            int nextBlockSize = *(int*)(nextBlock+1);

            if(*nextBlock == freeMem) {
                *movingPointer = freeMem;
                *(int*)(movingPointer+1) = currentBlockSize + nextBlockSize;
                currentBlockSize = currentBlockSize + nextBlockSize;
                *nextBlock = NULL;
                *(int*)(nextBlock+1) = NULL;
            }
            if(*prevBlock == freeMem) {
                *movingPointer = NULL;
                *(int*)(movingPointer+1) = NULL;
                *(int*)(prevBlock+1) = prevBlockSize + currentBlockSize;
            } else {
                *(movingPointer) = freeMem;
            }
            found = true;
            break;
        }
        else if(!movingPointer) {
            break;
        }
        else {
            prevBlock = movingPointer;
            prevBlockSize = currentBlockSize;
            movingPointer = movingPointer + currentBlockSize;
        }

    }

    if(found) {
        printf("Memory block with the address %p is freed\n",address);
    }
    else {
        printf("Cannot find the memory address!\n");
    }

}

void printMemory() {
    
    char* movingPointer = base;

    if(*movingPointer==NULL) {
        printf("Memory not initialized!\n");
    }
    else {
        while(movingPointer <= memory + MEMORY_SIZE - 1) {
            
            char status = *(movingPointer);
            int blockSize = *(int*)(movingPointer+1);
            char* startAddress = movingPointer;
            char* endAddress = movingPointer + blockSize - 1;
            
            movingPointer = movingPointer + blockSize;
            
            if(status == 'a') {
                printf("-----------------------------------------------\n");
                printf("Block size: %d\n",blockSize);
                printf("Block status: Allocated\n");
                printf("Starting Memory Address: %p\n",startAddress);
                printf("Ending Memory Address: %p\n",endAddress);
                printf("-----------------------------------------------\n");
            }
            else {
                printf("-----------------------------------------------\n");
                printf("Block size: %d\n",blockSize);
                printf("Block status: Free\n");
                printf("Starting Memory Address: %p\n",startAddress);
                printf("Ending Memory Address: %p\n",endAddress);
                printf("-----------------------------------------------\n");
            }
            
        }
    }
    
}