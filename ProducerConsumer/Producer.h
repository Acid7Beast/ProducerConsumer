#pragma once

#include "CircularBuffer.h"
#include "BufferBlock.h"

#include <fstream>
#include <atomic>
#include <string>

namespace Parallelity
{
	class Producer
	{
	public:
		Producer(const std::string& fileName);

		void operator>>(CircularBuffer& buffer);
		bool Reading() const;

	private:
		std::ifstream _reader;
		std::atomic<bool> _hasMoreData = true;
	};
}