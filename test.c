#include "alok.h"
#include "stdio.h"

#include "assert.h"

typedef unsigned char byte;

int main() {
    byte* integers = alok(10);
    printf("ptr: %p\n", integers);
    for (int i = 0; i < 10; ++i) {
        integers[i] = i * 2 + 1;
    }

    for (int i = 0; i < 10; ++i) {
        printf("%d ", integers[i]);
    }
    printf("\n");

    byte* other_integers = alok(10);
    printf("ptr: %p\n", other_integers);
    assert(other_integers - integers == 10);
    alok_free(integers);

    byte* next_ints = alok(10);
    printf("ptr: %p\n", next_ints);
    assert(next_ints == integers);

    alok_free(next_ints);

    byte* cantfitstart = alok(11);
    printf("ptr: %p\n", cantfitstart);
    assert(cantfitstart > integers);

    alok_free(other_integers);
    alok_free(cantfitstart);

    return 0;
}
