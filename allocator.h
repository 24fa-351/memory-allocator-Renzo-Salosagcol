#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

void* mymalloc(size_t size);
void myfree(void* ptr);
void* myrealloc(void* ptr, size_t size);

#endif // MYMALLOC_H