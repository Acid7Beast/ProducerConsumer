#include "Consumer.h"

namespace Parallelity
{
	Consumer::Consumer(Counter& counter)
		: _counter{ counter }
	{
	}

	void Consumer::operator<<(CircularBuffer& buffer)
	{
		BufferBlock readable = std::move(buffer.Read());
		if (readable.size == 0) return;

		for (size_t i = 0; i < readable.size; ++i) {
			const unsigned char readed = readable.data[i];
			_counter.Increment(static_cast<uint8_t>(readed));
		}
	}
}