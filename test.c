#include "mymalloc.h"

void main() {
    
    bool run = true;

    while(true) {

        printf("\n\t\t  # Instructions #\t\t\t\n");
        printf("---------------------------------------------------\n");
        printf("Press 'a' to allocate memory\n");
        printf("Press 'f' to free memory\n");
        printf("Press 'p' to print the status of memory blocks\n");
        printf("Press 'q' to quit\n");

        char input;
        scanf(" %c",&input);

        if(input=='a') {

            printf("Enter the size of the block you want to allocate: ");
            int size;
            scanf("%d",&size);
            MyMalloc(size);

        }
        else if(input=='f') {
            
            printf("Enter the memory address of the block you want to free: ");
            char address[20];
            scanf("%s",address);
            char* add;
            sscanf(address,"%p",&add);
            MyFree(add);
            
        }
        else if(input=='p') {
            printMemory();
        }
        else if(input=='q') {
            break;
        }
        else {
            printf("Invalid Input! Enter your input again\n");
        }

    }
    
//    char* addr1 = MyMalloc(8);
//    char* addr2 = MyMalloc(400);
//    char* addr3 = MyMalloc(100);
//    char* addr4 = MyMalloc(50);
//    char* addr5 = MyMalloc(200);
//
//    printf("addr1(8) : %p \n",addr1);
//    printf("addr2(400) : %p \n",addr2);
//    printf("addr3(8) : %p \n",addr3);
//    printf("addr4(50) : %p \n",addr4);
//    printf("addr5(200) : %p \n",addr5);
//
//
//    MyFree(addr2);//100
//    MyFree(addr4);//400
//
//    char* addr6 = MyMalloc(40);
//    printf("addr6(40) : %p \n",addr6);
//
//    printMemory();
    
}