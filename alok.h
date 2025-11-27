/*
*       ALOKCATOR
*
*       by Jayden van Zuydam
*/
#ifndef ALOK_H
#define ALOK_H

#define NIL (void*)0
typedef unsigned long size_t;

// allocate n bytes on the heap
void* alok(size_t n); 

// reallocate ptr, with new size 'n'
void* alok_more(void* ptr, size_t n);

// free ptr from heap
void alok_free(void* ptr);

#endif
