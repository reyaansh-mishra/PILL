/*
 * src/memory/memory.c
 * By Reyaansh Mishra
 */

#include <stdbool.h>
#include <stddef.h>

#include <pill/memory.h>
#include <pill/uefi.h>

#include <private-includes/blal.h>

void* malloc(size_t size) {
        switch ((int)is_uefi_alive) {
                case true:
                        return pre_malloc_malloc_provider(size);
                case false:
                        return blal_allocate(size);
        };
        return NULL;
};

void free(void* __attribute__((unused)) ptr) {
        return; // Not implemented
};

void* memcpy(void* dest, const void* src, size_t size) {
        uint8_t* d              = (uint8_t *)dest;
        const uint8_t* s        = (uint8_t *)src;

        for (size_t i = 0; i < size; i++) {
                d[i] = s[i];
        };

        return dest;
};

void* memset(void* dest, int val, size_t size) {
        uint8_t* d = (uint8_t *)dest;

        for (size_t i = 0; i < size; i++) {
                d[i] = (uint8_t)val;
        };
        return dest;
};

void* memmove(void* dest, const void* src, size_t size) {
    uint8_t* d          = dest;
    const uint8_t* s    = src;

    if (d < s) {
        for (size_t i = 0; i < size; i++) d[i] = s[i];
    } else {
        for (size_t i = size; i > 0; i--) d[i-1] = s[i-1];
    };
    return dest;
};
