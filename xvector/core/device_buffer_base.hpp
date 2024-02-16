#pragma once

#include "context_base.hpp"
#include "object.hpp"

namespace xvec
{
namespace core
{

class DeviceBufferBase;

class DeviceBufferBase : public Object
{
public:
    explicit DeviceBufferBase(ContextBase* context);

    DeviceBufferBase(ContextBase* context, std::size_t size, std::size_t offset = 0);

    DeviceBufferBase(const DeviceBufferBase& src) = delete;

    virtual ~DeviceBufferBase() noexcept = default;

    DeviceBufferBase& operator=(const DeviceBufferBase& src) = delete;

    virtual uint8_t* address() const noexcept = 0;

    std::size_t size() const noexcept
    {
        return size_;
    }

    std::size_t offset() const noexcept
    {
        return offset_;
    }

    void setOffset(std::size_t offset) noexcept
    {
        offset_ = offset;
    }

private:
    std::size_t size_;
    std::size_t offset_;
};

}  // namespace core
}  // namespace xvec
