#pragma once

#include <cassert>
#include "Counter.h"
#include "CircularBuffer.h"
#include "BufferBlock.h"
#include "Producer.h"
#include "Consumer.h"

namespace Parallelity
{
    class Consumer
    {
    public:
        Consumer(Counter& counter);

        void operator<<(CircularBuffer& buffer);

    private:
        Counter& _counter;
    };
}