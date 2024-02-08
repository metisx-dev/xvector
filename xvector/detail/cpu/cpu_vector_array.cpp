#include "cpu_vector_array.hpp"

#include <cstring>

#include "cpu_context.hpp"
#include "xvector/detail/cpu/half_float/half_float.hpp"
#include "xvector/xvec_index.h"

namespace xvec
{
namespace detail
{

namespace
{
SharedPtr<CpuHostBuffer> createValidityBitmap(CpuContext* context, std::size_t size, std::size_t validCount)
{
    auto bufferSize = (size + 7) / 8;
    auto validityBitmap = CpuHostBuffer::create(context, bufferSize);

    std::size_t validBytes = validCount / 8;
    std::memset(validityBitmap->data(), -1, validBytes);

    if (validCount % 8 != 0)
    {
        validityBitmap->data()[validBytes++] = (1 << (validCount % 8)) - 1;
    }

    if (validBytes != bufferSize)
    {
        memset(validityBitmap->data() + validBytes, 0, bufferSize - validBytes);
    }

    return validityBitmap;
}

SharedPtr<CpuHostBuffer> expandValidityBitmap(CpuContext* context,
                                              std::size_t size,
                                              SharedPtr<CpuHostBuffer> oldValidityBitmap)
{
    auto bufferSize = (size + 7) / 8;
    if (bufferSize > oldValidityBitmap->size())
    {
        auto validityBitmap = CpuHostBuffer::create(context, bufferSize);

        memcpy(validityBitmap->data(), oldValidityBitmap->data(), oldValidityBitmap->size());
        memset(validityBitmap->data() + oldValidityBitmap->size(), 0, bufferSize - oldValidityBitmap->size());
        return validityBitmap;
    }

    return oldValidityBitmap;
}

SharedPtr<CpuHostBuffer> expandBuffer(CpuContext* context, SharedPtr<CpuHostBuffer> oldBuffer, std::size_t newSize)
{
    auto newBuffer = CpuHostBuffer::create(context, newSize);
    memcpy(newBuffer->data(), oldBuffer->data(), oldBuffer->size());
    return newBuffer;
}
}  // namespace

CpuVectorArray::CpuVectorArray(CpuContext* context, xvecFloatType floatType, std::size_t dimension)
    : Managed<CpuVectorArray>(context),
      floatType_(floatType),
      dimension_(dimension)
{
}

void CpuVectorArray::setVectors(SharedPtr<CpuHostBuffer> vectors, std::size_t size)
{
    vectors_ = vectors;
    size_ = size;
}

void CpuVectorArray::setValidityBitmap(SharedPtr<CpuHostBuffer> validityBitmap, std::size_t validCount)
{
    validityBitmap_ = validityBitmap;
    validCount_ = validCount;

    if (validCount_ == 0)
    {
        if (validityBitmap_ != nullptr)
        {
            for (std::size_t i = 0; i < size_; ++i)
            {
                if (valid(i))
                {
                    validCount_++;
                }
            }
        }
        else
        {
            validCount_ = size_;
        }
    }
}

SharedPtr<CpuHostBuffer> CpuVectorArray::vector(std::size_t index)
{
    std::size_t floatSize = floatType() == XVEC_FLOAT32 ? sizeof(float) : sizeof(half);
    auto vector = CpuHostBuffer::create(context(), dimension() * floatSize);

    uint8_t* dst = vector->data();
    uint8_t* src = vectors_->data() + index * dimension() * floatSize;

    std::memcpy(dst, src, this->dimension() * floatSize);

    return vector;
}

bool CpuVectorArray::valid(std::size_t position) const
{
    if (position >= this->size())
    {
        throw std::out_of_range("Index out of range");
    }

    if (validityBitmap_ == nullptr)
    {
        return true;
    }

    const uint8_t* bitmap = validityBitmap_->data();
    return bitmap[position / 8] & (1 << (position % 8));
}

void CpuVectorArray::updateVectors(SharedPtr<CpuHostBuffer> positions,
                                   SharedPtr<CpuHostBuffer> vectors,
                                   std::size_t size)
{
    const xvecIndex* positionsData = reinterpret_cast<const xvecIndex*>(positions->data());

    for (std::size_t i = 0; i < size; ++i)
    {
        const xvecIndex position = positionsData[i];
        if (this->size() <= position)
        {
            throw std::out_of_range("Index out of range");
        }
    }

    const auto floatSize = floatType() == XVEC_FLOAT32 ? sizeof(float) : sizeof(half);
    const auto dimension = this->dimension();
    const uint8_t* vectorsData = vectors->data();

    for (std::size_t i = 0; i < size; ++i)
    {
        const xvecIndex position = positionsData[i];
        uint8_t* dst = vectors_->data() + position * dimension * floatSize;
        const uint8_t* src = vectorsData + i * dimension * floatSize;

        std::memcpy(dst, src, this->dimension() * floatSize);
    }
}

SharedPtr<CpuHostBuffer> CpuVectorArray::insertVectors(SharedPtr<CpuHostBuffer> vectors, std::size_t size)
{
    std::size_t floatSize = floatType() == XVEC_FLOAT32 ? sizeof(float) : sizeof(half);
    auto positions = CpuHostBuffer::create(context(), dimension() * floatSize);

    if (validityBitmap_ == nullptr)
    {
        auto oldBufferSize = this->size() * dimension() * floatSize;
        auto bufferExpansionSize = size * dimension() * floatSize;
        auto newBufferSize = oldBufferSize + bufferExpansionSize;

        if (vectors_->size() < newBufferSize)
        {
            vectors_ = expandBuffer(context(), vectors_, newBufferSize);
        }

        std::memcpy(vectors_->data() + oldBufferSize, vectors->data(), bufferExpansionSize);

        validCount_ += size;
        size_ += size;

        return positions;
    }
    else
    {
        if ((this->size() - this->validCount()) < size)
        {
            auto expansion = size - (this->size() - this->validCount());

            auto oldBufferSize = this->size() * dimension() * floatSize;
            auto bufferExpansionSize = expansion * dimension() * floatSize;
            auto newBufferSize = oldBufferSize + bufferExpansionSize;

            vectors_ = expandBuffer(context(), vectors_, newBufferSize);
            validityBitmap_ = expandValidityBitmap(context(), this->size(), validityBitmap_);
            this->size_ += expansion;
        }

        uint8_t* bitmap = validityBitmap_->data();
        for (std::size_t i = 0; i < size; ++i)
        {
            while (valid(freePosition_))
            {
                freePosition_ = (freePosition_ + 1) % this->size();
            }

            uint8_t* dst = vectors_->data() + freePosition_ * dimension() * floatSize;
            uint8_t* src = vectors->data() + i * dimension() * floatSize;

            std::memcpy(dst, src, this->dimension() * floatSize);

            bitmap[freePosition_ / 8] |= 1 << (freePosition_ % 8);
            validCount_++;
            freePosition_ = (freePosition_ + 1) % this->size();
        }
    }

    return positions;
}

void CpuVectorArray::deleteVectors(SharedPtr<CpuHostBuffer> positions, std::size_t size)
{
    if (size == 0)
        return;

    const xvecIndex* positionsData = reinterpret_cast<const xvecIndex*>(positions->data());

    for (std::size_t i = 0; i < size; ++i)
    {
        const xvecIndex position = positionsData[i];
        if (this->size() <= position)
        {
            throw std::out_of_range("Index out of range");
        }

        if (!this->valid(position))
        {
            throw std::invalid_argument("Invalid position");
        }
    }

    if (this->valid(this->freePosition_))
    {
        this->freePosition_ = positionsData[0];
    }

    if (validityBitmap_ == nullptr)
    {
        validityBitmap_ = createValidityBitmap(context(), this->size(), this->validCount());
    }

    uint8_t* bitmap = validityBitmap_->data();

    for (std::size_t i = 0; i < size; ++i)
    {
        const xvecIndex position = positionsData[i];
        bitmap[position / 8] &= ~(1 << (position % 8));
    }

    validCount_ -= size;
}

}  // namespace detail
}  // namespace xvec
