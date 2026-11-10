/*
 * PILL/private-includes/new.hpp
 * By ChatGPT
 */

#include <stddef.h>

inline void* operator new(size_t, void* ptr) noexcept {
    return ptr;
}

inline void operator delete(void*, void*) noexcept {}
