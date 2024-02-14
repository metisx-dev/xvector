#pragma once

#include <memory>

#include "context.hpp"
#include "managed.hpp"

namespace xvec
{
namespace sim
{

class DeviceBuffer;

class DeviceBuffer : public Managed<DeviceBuffer>
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
    DeviceBuffer(const DeviceBuffer& src) = delete;
    DeviceBuffer& operator=(const DeviceBuffer& src) = delete;

    std::shared_ptr<uint8_t> base_;
    std::size_t size_;
    std::size_t offset_;
};

}  // namespace sim
}  // namespace xvec
