#pragma once

#include "Constants.h"
#include "BufferBlock.h" 

#include <array>
#include <condition_variable>
#include <mutex>
#include <semaphore>

namespace Parallelity
{
	class CircularBuffer
	{
	public:
		void Write(BufferBlock block);
		BufferBlock Read();

	private:
		alignas(64) std::array<BufferBlock, kCapacity> _mBuffer;
		std::atomic<size_t> _mWriteIndex = 0;
		std::atomic<size_t> _mReadIndex = 0;

		std::counting_semaphore<kCapacity> _mReadLimiter{ 0 };
		std::counting_semaphore<kCapacity> _mWriteLimiter{ kCapacity };
		std::mutex _mMmutex;
	};
}