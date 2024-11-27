#include "allocator.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#define MEMORY_SIZE 1024 * 1024 // 1MB for testing

typedef struct Block {
    size_t size;
    struct Block* next;
} Block;

static void* memory = NULL;
static Block* free_list = NULL;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void initialize_memory() {
    memory = sbrk(MEMORY_SIZE);
    if (memory == (void*)-1) {
        fprintf(stderr, "Failed to initialize memory\n");
        return;
    }
    free_list = (Block*)memory;
    free_list->size = MEMORY_SIZE - sizeof(Block);
    free_list->next = NULL;
}

void* mymalloc(size_t size) {
    pthread_mutex_lock(&mutex);
    if (!memory) {
        initialize_memory();
    }

    Block* current = free_list;
    Block* previous = NULL;

    while (current) {
        if (current->size >= size) {
            if (current->size > size + sizeof(Block)) {
                Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->next = current->next;
                current->size = size;
                current->next = NULL;
                if (previous) {
                    previous->next = new_block;
                } else {
                    free_list = new_block;
                }
            } else {
                if (previous) {
                    previous->next = current->next;
                } else {
                    free_list = current->next;
                }
            }
            memset((char*)current + sizeof(Block), 0, size);
            pthread_mutex_unlock(&mutex);
            return (char*)current + sizeof(Block);
        }
        previous = current;
        current = current->next;
    }

    fprintf(stderr, "Failed to allocate memory\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void myfree(void* ptr) {
    pthread_mutex_lock(&mutex);
    if (!ptr) {
        pthread_mutex_unlock(&mutex);
        return;
    }

    Block* block = (Block*)((char*)ptr - sizeof(Block));
    block->next = free_list;
    free_list = block;
    pthread_mutex_unlock(&mutex);
}

void* myrealloc(void* ptr, size_t size) {
    pthread_mutex_lock(&mutex);
    if (!ptr) {
        pthread_mutex_unlock(&mutex);
        return mymalloc(size);
    }

    Block* block = (Block*)((char*)ptr - sizeof(Block));
    if (block->size >= size) {
        pthread_mutex_unlock(&mutex);
        return ptr;
    }

    void* new_ptr = mymalloc(size);
    if (new_ptr) {
        memcpy(new_ptr, ptr, block->size);
        myfree(ptr);
    }
    pthread_mutex_unlock(&mutex);
    return new_ptr;
}