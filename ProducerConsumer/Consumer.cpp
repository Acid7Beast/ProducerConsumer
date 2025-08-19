#include "Consumer.h"

namespace Parallelity
{
    Consumer::Consumer(Counter& counter) 
        : _counter{ counter }
    {
    }

    void Consumer::Run(CircularBuffer& buffer) {
        while (true) {
            BufferBlock readable = std::move(buffer.Read());
            if (readable.size == 0) {

                buffer.Write(std::move(readable));
                break;
            }

            for (size_t i = 0; i < readable.size; ++i) {
                _counter.Increment(readable.data[i]);
            }
        }
    }
}