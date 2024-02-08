#pragma once

#include <memory>

#include "xvector/detail/context.hpp"
#include "xvector/detail/factory.hpp"
#include "xvector/detail/managed.hpp"

namespace xvec
{
namespace detail
{

class CpuHostBuffer;
class CpuDeviceBuffer;

class CpuHostBuffer : public Factory<CpuHostBuffer>, public Managed<CpuHostBuffer>
{
    friend CpuDeviceBuffer;
    friend Factory<CpuHostBuffer>;

public:
    ~CpuHostBuffer() noexcept;

    std::shared_ptr<uint8_t> base() const noexcept
    {
        return base_;
    }

    uint8_t* data() const noexcept
    {
        return base_.get() + offset_;
    }

    std::size_t size() const noexcept
    {
        return size_;
    }

    std::size_t offset() const noexcept
    {
        return offset_;
    }

    void setData(std::shared_ptr<uint8_t> base, std::size_t offset = 0) noexcept
    {
        base_ = base;
        offset_ = offset;
    }

private:
    explicit CpuHostBuffer(Context* context);

    CpuHostBuffer(Context* context, std::size_t size, std::size_t offset = 0);

    CpuHostBuffer(Context* context,
                  std::shared_ptr<uint8_t> base,
                  std::size_t size,
                  const std::size_t offset = 0) noexcept;

    CpuHostBuffer(const CpuHostBuffer& src) = delete;
    CpuHostBuffer& operator=(const CpuHostBuffer& src) = delete;

    std::shared_ptr<uint8_t> base_;
    std::size_t size_;
    std::size_t offset_;
};

#ifndef XVEC_MU_SUPPORT
using HostBuffer = CpuHostBuffer;
#endif

}  // namespace detail
}  // namespace xvec
