/*
 * private-includes/blal.h
 * By Reyaansh Mishra
 */

#include <stddef.h>

void* blal_allocate(size_t size);
void  blal_allocator_free(void* ptr);

void blal_init(void* base, size_t size);
