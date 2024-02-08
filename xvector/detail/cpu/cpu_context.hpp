#pragma once

#include <cstdint>
#include <vector>

#include "xvector/detail/shared_ptr.hpp"
#include "xvector/detail/spin_lock.hpp"

namespace xvec
{
namespace detail
{
template <typename Derived>
class Managed;

class CpuDeviceBuffer;
class CpuVectorArray;
class CpuIndexArray;
class CpuKnnQuery;
class CpuKnnResult;
class CpuDistanceQuery;
class CpuDistanceResult;
class CpuHostBuffer;

class CpuContext
{
public:
    using ObjectId = std::uint32_t;

    CpuContext() noexcept;

    ~CpuContext() noexcept;

    CpuContext(const CpuContext& src) = delete;
    CpuContext& operator=(const CpuContext& src) = delete;

    // xvecBufferId register_(CpuHostBuffer* buffer) noexcept;
    // void unregister(xvecBufferId id) noexcept;

    struct Register
    {
        ObjectId register_(void* object);
        void unregister(ObjectId id);

        template <typename T>
        SharedPtr<T> object(ObjectId id)
        {
            return static_cast<T*>(objects[id]);
        }

        std::vector<void*> objects;
        std::vector<ObjectId> freeIds;
        SpinLock lock;
    };

    template <typename T>
    Register& register_() noexcept;

    template <typename T>
    SharedPtr<T> object(ObjectId id) noexcept
    {
        return register_<T>().template object<T>(id);
    }

private:
    Register hostBufferRegister_;
    Register deviceBufferRegister_;
    Register vectorArrayRegister_;
    Register indexArrayRegister_;
    Register knnQueryRegister_;
    Register knnResultRegister_;
    Register distanceQueryRegister_;
    Register distanceResultRegister_;
};

template <>
inline CpuContext::Register& CpuContext::register_<CpuHostBuffer>() noexcept
{
    return hostBufferRegister_;
}

template <>
inline CpuContext::Register& CpuContext::register_<CpuDeviceBuffer>() noexcept
{
    return deviceBufferRegister_;
}

template <>
inline CpuContext::Register& CpuContext::register_<CpuVectorArray>() noexcept
{
    return vectorArrayRegister_;
}

template <>
inline CpuContext::Register& CpuContext::register_<CpuIndexArray>() noexcept
{
    return indexArrayRegister_;
}

template <>
inline CpuContext::Register& CpuContext::register_<CpuKnnQuery>() noexcept
{
    return knnQueryRegister_;
}

template <>
inline CpuContext::Register& CpuContext::register_<CpuKnnResult>() noexcept
{
    return knnResultRegister_;
}

template <>
inline CpuContext::Register& CpuContext::register_<CpuDistanceQuery>() noexcept
{
    return distanceQueryRegister_;
}

template <>
inline CpuContext::Register& CpuContext::register_<CpuDistanceResult>() noexcept
{
    return distanceResultRegister_;
}

using Context = CpuContext;

}  // namespace detail
}  // namespace xvec
