#include "Producer.h"

namespace Parallelity
{
    Producer::Producer(const std::string& fileName)
        : _reader{ fileName, std::ios::binary }
        , _hasMoreData{ true }
    {
    }

    void Producer::operator>>(CircularBuffer& buffer)
    {
        if (!_hasMoreData) return;
        if (!_reader.is_open()) {
            _reader.close();
            _hasMoreData = false;
            return;
        }

        BufferBlock block;
        _reader.read(block.data.data(), kBlockSize);
        block.size = static_cast<size_t>(_reader.gcount());
        if (block.size > 0) {
            buffer.Write(std::move(block));
        }
        if (_reader.eof() || block.size == 0) {
            _reader.close();
            _hasMoreData = false;
        }
    }

    bool Producer::Reading() const
    {
        return _hasMoreData;
    }
}