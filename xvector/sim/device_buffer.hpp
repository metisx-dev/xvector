#pragma once

#include <memory>

#include "context.hpp"
#include "detail/device_buffer_base.hpp"

namespace xvec
{
namespace sim
{

class DeviceBuffer;

class DeviceBuffer : public detail::DeviceBufferBase
{
public:
    explicit DeviceBuffer(Context* context);

    DeviceBuffer(Context* context, std::size_t size, std::size_t offset = 0);

    DeviceBuffer(Context* context,
                 std::shared_ptr<uint8_t> base,
                 std::size_t size,
                 const std::size_t offset = 0) noexcept;

    ~DeviceBuffer() noexcept;

    std::shared_ptr<uint8_t> base() const noexcept
    {
        return base_;
    }

    virtual uint8_t* address() const noexcept override
    {
        return base_.get() + offset();
    }

    void setData(std::shared_ptr<uint8_t> base, std::size_t offset = 0) noexcept
    {
        base_ = base;
        setOffset(offset);
    }

private:
    DeviceBuffer(const DeviceBuffer& src) = delete;
    DeviceBuffer& operator=(const DeviceBuffer& src) = delete;

    std::shared_ptr<uint8_t> base_;
};

}  // namespace sim
}  // namespace xvec
