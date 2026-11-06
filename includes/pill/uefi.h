/*
 * includes/pill/uefi.h
 * By Reyaansh Mishra
 */

#include <stdbool.h>
#include <stddef.h>

typedef void* (*pill_malloc_provider_t)(size_t);
typedef void (*pill_free_provider_t)(void*);

extern bool is_uefi_alive; 

extern pill_malloc_provider_t   pre_malloc_malloc_provider;
extern pill_free_provider_t     pre_free_free_provider;
