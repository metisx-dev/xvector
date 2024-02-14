#include "xvector/xvec_buffer.h"

#include <cstring>

#include "device_buffer.hpp"

extern "C"
{
xvecBuffer XVEC_NULL_BUFFER = {0};

xvecStatus xvecCreateBuffer(xvecBuffer *buffer_, xvecContext context_, size_t size)
{
    try
    {
        auto context = reinterpret_cast<xvec::sim::Context *>(context_);
        auto buffer = new xvec::sim::DeviceBuffer(context, size);
        *buffer_ = reinterpret_cast<xvecBuffer>(buffer);
    }
    catch (std::bad_alloc &e)
    {
        return XVEC_ERROR_OUT_OF_MEMORY;
    }
    catch (...)
    {
        return XVEC_ERROR_UNKNOWN;
    }

    return XVEC_SUCCESS;
}

xvecStatus xvecReleaseBuffer(xvecBuffer buffer_)
{
    if (buffer_ == 0)
        return XVEC_SUCCESS;

    auto buffer = reinterpret_cast<xvec::sim::DeviceBuffer *>(buffer_);
    buffer->release();
    return XVEC_SUCCESS;
}

xvecStatus xvecGetBufferContext(xvecBuffer buffer_, xvecContext *context_)
{
    auto buffer = reinterpret_cast<xvec::sim::DeviceBuffer *>(buffer_);
    auto context = buffer->context();
    *context_ = reinterpret_cast<xvecContext>(context);
    return XVEC_SUCCESS;
}

xvecStatus xvecGetBufferAddress(xvecBuffer buffer_, void **address)
{
    auto buffer = reinterpret_cast<xvec::sim::DeviceBuffer *>(buffer_);
    *address = buffer->data();
    return XVEC_SUCCESS;
}

xvecStatus xvecCopyToBuffer(xvecBuffer dst, const void *src, size_t dstOffset, size_t sizeInBytes)
{
    auto buffer = reinterpret_cast<xvec::sim::DeviceBuffer *>(dst);
    std::memcpy(buffer->data() + dstOffset, src, sizeInBytes);
    return XVEC_SUCCESS;
}

xvecStatus xvecCopyFromBuffer(void *dst, xvecBuffer src, size_t srcOffset, size_t sizeInBytes)
{
    auto buffer = reinterpret_cast<xvec::sim::DeviceBuffer *>(src);
    std::memcpy(dst, buffer->data() + srcOffset, sizeInBytes);
    return XVEC_SUCCESS;
}

xvecStatus xvecGetBufferSize(xvecBuffer buffer_, size_t *size)
{
    auto buffer = reinterpret_cast<xvec::sim::DeviceBuffer *>(buffer_);
    *size = buffer->size();
    return XVEC_SUCCESS;
}

}  // extern "C"
