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
    const std::string filename = "test.bin";

    std::future<void> producerWorker = std::async(
        std::launch::async,
        &Parallelity::Producer::Run,
        Parallelity::Producer(filename),
        std::ref(buffer)
    );

    std::vector<std::future<void>> countWorkers(std::thread::hardware_concurrency() - 1);
    for (auto& worker : countWorkers) {
        worker = std::async(
            std::launch::async,
            &Parallelity::Consumer::Run,
            Parallelity::Consumer(counter),
            std::ref(buffer)
        );
    }

    producerWorker.get();

    for (auto& worker : countWorkers) {
        worker.get();
	}

    for (size_t i = 0; i < 256; ++i)
    {
        std::cout << std::format("Char {} times: {}.\n", static_cast<char>(i), counter.frequency[i]);
    }

    return 0;
}