#include "Producer.h"

namespace Parallelity
{
    Producer::Producer(const std::string& fileName)
    : _mReader{ fileName, std::ios::binary } 
    {
    }

    void Producer::Run(CircularBuffer& buffer) {
        if (!_mReader.is_open()) {
            _mReader.close();
            return;
        }

        while (!_mReader.eof()) {
            BufferBlock block;
            _mReader.read(reinterpret_cast<char*>(block.data.data()), kBlockSize);
            block.size = static_cast<size_t>(_mReader.gcount());

            if (block.size > 0) {
                buffer.Write(std::move(block));
            }
            else {
                break;
            }
        }
        _mReader.close();

        BufferBlock sentinel_block;
        sentinel_block.size = 0;
        buffer.Write(std::move(sentinel_block));
    }
}