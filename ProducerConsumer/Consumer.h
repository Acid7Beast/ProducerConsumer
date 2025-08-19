#pragma once

#include <cassert>
#include "Counter.h"
#include "CircularBuffer.h"
#include "BufferBlock.h"
#include "Producer.h"
#include "Consumer.h"

namespace Parallelity
{
    class Consumer {
    public:
        Consumer(Counter& counter);

    public:
        void Run(CircularBuffer& buffer);

    private:
        Counter& _counter;
    };
}