#pragma once

#include "CircularBuffer.h"
#include "BufferBlock.h"

#include <fstream>
#include <atomic>
#include <string>

namespace Parallelity
{
    class Producer {
    public:
        Producer(const std::string& fileName);

    public:
        void Run(CircularBuffer& buffer);

    private:
        std::ifstream _mReader;
    };
}