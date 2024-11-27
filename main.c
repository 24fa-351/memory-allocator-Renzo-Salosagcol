#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_malloc_free() {
    printf("Running test_malloc_free...\n");
    void* ptr = mymalloc(100);
    if (ptr) {
        printf("Allocated 100 bytes\n");
        myfree(ptr);
        printf("Freed 100 bytes\n");
    } else {
        printf("Failed to allocate 100 bytes\n");
    }
}

void test_realloc() {
    printf("Running test_realloc...\n");
    void* ptr = mymalloc(100);
    if (ptr) {
        printf("Allocated 100 bytes\n");
        ptr = myrealloc(ptr, 200);
        if (ptr) {
            printf("Reallocated to 200 bytes\n");
            myfree(ptr);
            printf("Freed 200 bytes\n");
        } else {
            printf("Failed to reallocate to 200 bytes\n");
        }
    } else {
        printf("Failed to allocate 100 bytes\n");
    }
}

void test_multiple_allocations() {
    printf("Running test_multiple_allocations...\n");
    void* ptr1 = mymalloc(50);
    void* ptr2 = mymalloc(150);
    if (ptr1 && ptr2) {
        printf("Allocated 50 and 150 bytes\n");
        myfree(ptr1);
        myfree(ptr2);
        printf("Freed 50 and 150 bytes\n");
    } else {
        printf("Failed to allocate memory\n");
    }
}

void test_fill_pattern() {
    printf("Running test_fill_pattern...\n");
    size_t size = 100;
    void* ptr = mymalloc(size);
    if (ptr) {
        memset(ptr, 0xAA, size);
        printf("Filled 100 bytes with pattern 0xAA\n");
        myfree(ptr);
        printf("Freed 100 bytes\n");
    } else {
        printf("Failed to allocate 100 bytes\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        int test_num = atoi(argv[1]);
        switch (test_num) {
            case 1:
                test_malloc_free();
                break;
            case 2:
                test_realloc();
                break;
            case 3:
                test_multiple_allocations();
                break;
            case 4:
                test_fill_pattern();
                break;
            default:
                printf("Invalid test number\n");
                break;
        }
    } else {
        test_malloc_free();
        test_realloc();
        test_multiple_allocations();
        test_fill_pattern();
    }
    return 0;
}