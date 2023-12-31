#pragma once

#include <IO/ReadBuffer.h>
#include <IO/CompressedReadBufferWrapper.h>
#include <IO/CompressionMethod.h>

#include <limits>
#include <zlib.h>


namespace DB
{

namespace ErrorCodes
{
}

/// Reads compressed data from ReadBuffer in_ and performs decompression using zlib library.
/// This buffer is able to seamlessly decompress multiple concatenated zlib streams.
class ZlibInflatingReadBuffer : public CompressedReadBufferWrapper
{
public:
    ZlibInflatingReadBuffer(
            std::unique_ptr<ReadBuffer> in_,
            CompressionMethod compression_method,
            size_t buf_size = DBMS_DEFAULT_BUFFER_SIZE,
            char * existing_memory = nullptr,
            size_t alignment = 0);

    ~ZlibInflatingReadBuffer() override;

private:
    bool nextImpl() override;

    z_stream zstr;
    bool eof_flag;

    /// Limit size of buffer because zlib uses
    /// UInt32 for sizes of internal buffers.
    using BufferSizeType =  decltype(zstr.avail_in);
    static constexpr auto max_buffer_size = std::numeric_limits<BufferSizeType>::max();
};

}
