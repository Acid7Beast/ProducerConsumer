#pragma once

#include "Constants.h"

#include <array>

namespace Parallelity
{
    struct BufferBlock {
        std::array<char, kBlockSize> data{};
        size_t size = 0; // To support partial reads

        BufferBlock() = default;
        BufferBlock(const char* src, size_t n);
    };
}