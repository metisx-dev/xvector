#include "xvec_buffer.h"

#include <cstring>

#include "xvector/detail/buffer.hpp"
#include "xvector/xvector.h"

extern "C"
{
xvecBuffer XVEC_NULL_BUFFER = {0};

xvecStatus xvecCreateBuffer(xvecBuffer *buffer_, xvecContext context_, size_t size)
{
    auto context = reinterpret_cast<xvec::detail::Context *>(context_);
    auto buffer = xvec::detail::HostBuffer::create(context, size);
    if (buffer == nullptr)
        return XVEC_ERROR_OUT_OF_MEMORY;

    buffer->retain();
    *buffer_ = reinterpret_cast<xvecBuffer>(buffer.get());
    return XVEC_SUCCESS;
}

#if 0
xvecStatus xvecCreateExternalBuffer(xvecBuffer *buffer_,
                                    xvecContext context_,
                                    void *pointer,
                                    size_t size,
                                    void (*deleter)(void *))
{
    auto context = reinterpret_cast<xvec::detail::Context *>(context_);

    std::shared_ptr<uint8_t> base(reinterpret_cast<uint8_t *>(pointer), [deleter](uint8_t *p) {
        if (deleter != nullptr)
            deleter(p);
    });

    auto buffer = xvec::detail::HostBuffer::create(context, base, size);
    if (buffer == nullptr)
        return XVEC_ERROR_OUT_OF_MEMORY;

    buffer->retain();
    *buffer_ = reinterpret_cast<xvecBuffer>(buffer.get());
    return XVEC_SUCCESS;
}
#endif

xvecStatus xvecRetainBuffer(xvecBuffer buffer_)
{
    auto buffer = reinterpret_cast<xvec::detail::HostBuffer *>(buffer_);
    buffer->retain();
    return XVEC_SUCCESS;
}

xvecStatus xvecReleaseBuffer(xvecBuffer buffer_)
{
    if (buffer_ == 0)
        return XVEC_SUCCESS;

    auto buffer = reinterpret_cast<xvec::detail::HostBuffer *>(buffer_);
    buffer->release();
    return XVEC_SUCCESS;
}

xvecStatus xvecGetBufferContext(xvecBuffer buffer_, xvecContext *context_)
{
    auto buffer = reinterpret_cast<xvec::detail::HostBuffer *>(buffer_);
    auto context = buffer->context();
    *context_ = reinterpret_cast<xvecContext>(context);
    return XVEC_SUCCESS;
}

xvecStatus xvecGetBufferAddress(xvecBuffer buffer_, void **address)
{
    auto buffer = reinterpret_cast<xvec::detail::HostBuffer *>(buffer_);
    *address = buffer->data();
    return XVEC_SUCCESS;
}

xvecStatus xvecCopyToBuffer(xvecBuffer dst, const void *src, size_t dstOffset, size_t sizeInBytes)
{
    auto buffer = reinterpret_cast<xvec::detail::HostBuffer *>(dst);
    std::memcpy(buffer->data() + dstOffset, src, sizeInBytes);
    return XVEC_SUCCESS;
}

xvecStatus xvecCopyFromBuffer(void *dst, xvecBuffer src, size_t srcOffset, size_t sizeInBytes)
{
    auto buffer = reinterpret_cast<xvec::detail::HostBuffer *>(src);
    std::memcpy(dst, buffer->data() + srcOffset, sizeInBytes);
    return XVEC_SUCCESS;
}

xvecStatus xvecGetBufferSize(xvecBuffer buffer_, size_t *size)
{
    auto buffer = reinterpret_cast<xvec::detail::HostBuffer *>(buffer_);
    *size = buffer->size();
    return XVEC_SUCCESS;
}

}  // extern "C"
