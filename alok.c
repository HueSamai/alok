#include "alok.h"

typedef unsigned char byte;

// 4 MB
byte the_heap[1024 * 4] = {0};

// each section start has a number indicating how many bytes are associated with it
// if there is a zero, and its not in a sections domain, it means that that byte of memory is free
size_t heap_info[sizeof(the_heap)] = {0};

size_t idx(void* ptr) {
    return (size_t)ptr - (size_t)the_heap;
}

void* alok(size_t n) {
    // look for open slot
    size_t i = 0;
    for (;;) {

        // check if there is enough free space
        if (!heap_info[i]) {
            int enough_space = 1;
            for (size_t j = i; j < i + n; ++j) {
                if (heap_info[j]) {
                    enough_space = 0;
                    break;
                }
            }

            if (enough_space) {
                heap_info[i] = n;
                return the_heap + i;
            }
        }


        size_t a = heap_info[i];
        i += a;
        if (a == 0) ++i;

        if (i >= sizeof(the_heap)) break;
    }

    return NIL;
}

void* alok_more(void* ptr, size_t n) {
    if (!ptr) return alok(n);

    // otherwise do some magic
    // lets check if there is space after the current ptr
    size_t prev_size = heap_info[idx(ptr)]; 

    // if the prev size is larger then we know there's enough space
    if (prev_size >= n) {
        heap_info[idx(ptr)] = n;
        return ptr;
    }
    
    size_t j = prev_size + idx(ptr);
    if (!heap_info[j]) {
        int enough_space = 1;
        size_t extension = n - prev_size;
        for (size_t k = j; k < j + extension; ++k) {
            if (heap_info[k]) {
                enough_space = 0;
                break;
            }
        }

        if (enough_space) {
            heap_info[idx(ptr)] = n;
            return ptr;
        }
    }
    
    // done in this order to save look time
    void* newptr = alok(n);
    alok_free(ptr);
    return newptr;
}

void alok_free(void* ptr) {
    // mark as not used
    heap_info[idx(ptr)] = 0;
}
