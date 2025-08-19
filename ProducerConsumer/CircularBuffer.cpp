#include "CircularBuffer.h"

#include <cassert>

namespace Parallelity
{
    void CircularBuffer::Write(BufferBlock block) {
        _mWriteLimiter.acquire();

        {
            std::scoped_lock lock(_mMmutex);
            _mBuffer[_mWriteIndex] = block;
            _mWriteIndex = (_mWriteIndex + 1) % kCapacity;
        }

        _mReadLimiter.release();
    }

    BufferBlock CircularBuffer::Read() {
        _mReadLimiter.acquire();

        BufferBlock result;
        {
            std::scoped_lock lock(_mMmutex);
            result = _mBuffer[_mReadIndex];
            _mReadIndex = (_mReadIndex + 1) % kCapacity;
        }

        _mWriteLimiter.release();
        return result;
    }
}