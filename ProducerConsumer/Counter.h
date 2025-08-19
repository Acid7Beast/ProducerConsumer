#pragma once

#include <array>
#include <atomic>
#include <mutex>


namespace Parallelity
{
    struct Counter
    {
        alignas(64) std::array<uint32_t, 256> frequency{};
        std::mutex _mutex;

        inline void Increment(uint8_t index)
        {
            std::scoped_lock lock(_mutex);
            frequency[index]++;
        }
    };
}