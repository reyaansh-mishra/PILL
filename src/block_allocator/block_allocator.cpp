/*
 * PILL/src/block-allocator/block_allocator.cpp
 * By Reyaansh Mishra
 */

#include <stddef.h>
#define MAX_ALLOCATE_REGIONS 512

#include <private-includes/blal/block_allocator.hpp>
#include <private-includes/new.hpp>

extern "C" {
        #include <private-includes/blal.h>
        #include <pill/memory.h>
        #include <pill/utils.h>

        #include <stdint.h>
}

// ------------------------------------------------------------------------------

struct ALLOCD_REGIONS {
        uintptr_t       offset;
        size_t          size;
};

struct ALLOCD_REGIONS allocated_region_at[MAX_ALLOCATE_REGIONS] = {};
size_t allocated_regions = 0;

block_allocator* allocator = nullptr;

// ------------------------------------------------------------------------------

bool register_region(uintptr_t pos, size_t size) {
        if (allocated_regions >= MAX_ALLOCATE_REGIONS) {
                return false; // I dont want printf dependency here yet.
                        // This is Page Table stuff, and printf itself depends on UART being mapped.
        };
        allocated_region_at[allocated_regions++] = {pos, size};
        return true;
};

// ------------------------------------------------------------------------------

void* block_allocator::alloc(size_t size) {
        uintptr_t cursor = 0;
        size = round_up(size, 16);

        for (size_t i = 0; i < allocated_regions; i++) {
                ALLOCD_REGIONS* region = &allocated_region_at[i];
                
                if ((cursor + size) <= region->offset) {
                        goto FINISH;
                };
                cursor = region->offset + region->size;
                cursor = round_up(cursor, 16);
        };

       if (size > block_allocator::size - cursor)
                return NULL;

        FINISH:
                if (!register_region(cursor, size))
                        return NULL;
                return (void*)(cursor + (uintptr_t)block_allocator::base);
};

void* blal_allocate(size_t size) {
        return allocator->alloc(size);
};

void blal_init(void* base, size_t size) {
        allocator = new (malloc(sizeof(block_allocator))) block_allocator(base, size);
};
