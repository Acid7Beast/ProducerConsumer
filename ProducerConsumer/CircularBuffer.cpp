#include "CircularBuffer.h"

#include <cassert>

namespace Parallelity
{
	void CircularBuffer::Write(BufferBlock block)
	{
		std::unique_lock tmpMutex{ _mutex };
		full.wait(tmpMutex, [&] { return _usedBlocks < kCapacity; });

		assert(_usedBlocks >= 0 && _usedBlocks < kCapacity);
		_buffer[_usedBlocks++] = block;

		empty.notify_one();
	}

	BufferBlock CircularBuffer::Read()
	{
		BufferBlock result;
		std::unique_lock tmpMutex{ _mutex };
		empty.wait(tmpMutex, [&] { return _usedBlocks > 0 || _done; });

		if (_done)
		{
			Stop();
			if (_usedBlocks == 0)
			{
				return result;
			}
		}
		result = _buffer[--_usedBlocks];
		assert(_usedBlocks >= 0 && _usedBlocks < kCapacity);

		full.notify_one();
		return result;
	}

	bool CircularBuffer::HasBlock() const
	{
		return _usedBlocks > 0;
	}

	bool CircularBuffer::HasFreeBlock() const
	{
		return _usedBlocks < kCapacity;
	}

	void CircularBuffer::Stop()
	{
		_done = true;
		empty.notify_one();
	}
}