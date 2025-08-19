// ProducerConsumer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include <fstream>
#include <functional>
#include <future>
#include <format>
#include <cassert>
#include <barrier>

#include "CircularBuffer.h"
#include "BufferBlock.h"
#include "Counter.h"
#include "Producer.h"
#include "Consumer.h"

int main()
{   
    Parallelity::CircularBuffer buffer;
    Parallelity::Counter counter;
    Parallelity::Producer producerTask{ "test.bin" };

    std::memset(&counter.frequency, 0, sizeof(counter.frequency));

    auto reader = std::async(std::launch::async, [&buffer, &producerTask]()
        {
            while (producerTask.Reading())
            {
                producerTask >> buffer;
            }

            buffer.Stop();
        });

    std::vector<std::future<void>> countWorkers(std::thread::hardware_concurrency() - 1);
    for (auto& worker : countWorkers)
    {
        worker = std::async(std::launch::async, [&buffer, &counter, &producerTask]()
            {
                Parallelity::Consumer consumer{ counter };

                while (producerTask.Reading() || buffer.HasBlock())
                {
                    if (buffer.HasBlock())
                        consumer << buffer;
                }
            });
    }

    reader.wait();
    for (auto& worker : countWorkers)
    {
        worker.wait();
    }

    for (size_t i = 0; i < 256; ++i)
    {
        std::cout << std::format("Char {} times: {}.\n", static_cast<char>(i), counter.frequency[i]);
    }
}