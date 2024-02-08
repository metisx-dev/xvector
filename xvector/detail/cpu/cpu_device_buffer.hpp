#pragma once

#include <memory>

#include "xvector/detail/context.hpp"
#include "xvector/detail/factory.hpp"
#include "xvector/detail/managed.hpp"

namespace xvec
{
namespace detail
{

class CpuDeviceBuffer;

class CpuDeviceBuffer : public Factory<CpuDeviceBuffer>, public Managed<CpuDeviceBuffer>
{
    friend Factory<CpuDeviceBuffer>;

public:
    ~CpuDeviceBuffer() noexcept;

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
    explicit CpuDeviceBuffer(Context* context);

    CpuDeviceBuffer(Context* context, std::size_t size, std::size_t offset = 0);

    CpuDeviceBuffer(Context* context,
                  std::shared_ptr<uint8_t> base,
                  std::size_t size,
                  const std::size_t offset = 0) noexcept;

    CpuDeviceBuffer(const CpuDeviceBuffer& src) = delete;
    CpuDeviceBuffer& operator=(const CpuDeviceBuffer& src) = delete;

    std::shared_ptr<uint8_t> base_;
    std::size_t size_;
    std::size_t offset_;
};

#ifndef XVEC_MU_SUPPORT
using HostBuffer = CpuDeviceBuffer;
#endif

}  // namespace detail
}  // namespace xvec
