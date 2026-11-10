/*
 * PILL/private-includes/blal/block_allocator.hpp
 * By Reyaansh Mishra
 */

#include <stddef.h>

// blal works in BYTES, not Pages.

class block_allocator {
        public:
                block_allocator(void* start, size_t size) : base(start), size(size) {};
                void*   alloc(size_t size);

        private:
                void* base;
                size_t size;
};
