#include "BufferBlock.h"

#include <utility>

namespace Parallelity
{
	BufferBlock::BufferBlock(const char* src, size_t n) {
		size = n;
		std::copy_n(src, n, data.begin());
	}
}