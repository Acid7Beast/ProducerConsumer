#pragma once

#include "Constants.h"
#include "BufferBlock.h" 

#include <array>
#include <condition_variable>
#include <mutex>

namespace Parallelity
{
    class CircularBuffer
    {
    public:
        void Write(BufferBlock block);
        BufferBlock Read();
        bool HasBlock() const;
        bool HasFreeBlock() const;
        void Stop();
        inline bool IsStopped() const
        {
            return _done;
        }

    private:
        alignas(64) std::array<BufferBlock, kCapacity> _buffer;
        alignas(64) uint32_t _usedBlocks { 0 };
        mutable volatile bool _done = false;
        mutable std::condition_variable full;
        mutable std::condition_variable empty;
        mutable std::mutex _mutex;
    };
}