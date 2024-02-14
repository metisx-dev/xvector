#pragma once

#include <cstdint>
#include <vector>

#include "shared_ptr.hpp"
#include "spin_lock.hpp"

namespace xvec
{
namespace sim
{
template <typename Derived>
class Managed;

class VectorArray;
class IndexArray;
class Filter;
class KnnQuery;
class KnnResult;
class DistanceQuery;
class DistanceResult;
class DeviceBuffer;

class Context
{
public:
    using ObjectId = std::uint32_t;

    Context() noexcept;

    ~Context() noexcept;

    Context(const Context& src) = delete;
    Context& operator=(const Context& src) = delete;

    // xvecBufferId register_(DeviceBuffer* buffer) noexcept;
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
    Register deviceBufferRegister_;
    Register vectorArrayRegister_;
    Register indexArrayRegister_;
    Register filterRegister_;
    Register knnQueryRegister_;
    Register knnResultRegister_;
    Register distanceQueryRegister_;
    Register distanceResultRegister_;
};

template <>
inline Context::Register& Context::register_<DeviceBuffer>() noexcept
{
    return deviceBufferRegister_;
}

template <>
inline Context::Register& Context::register_<VectorArray>() noexcept
{
    return vectorArrayRegister_;
}

template <>
inline Context::Register& Context::register_<IndexArray>() noexcept
{
    return indexArrayRegister_;
}

template <>
inline Context::Register& Context::register_<Filter>() noexcept
{
    return filterRegister_;
}

template <>
inline Context::Register& Context::register_<KnnQuery>() noexcept
{
    return knnQueryRegister_;
}

template <>
inline Context::Register& Context::register_<KnnResult>() noexcept
{
    return knnResultRegister_;
}

template <>
inline Context::Register& Context::register_<DistanceQuery>() noexcept
{
    return distanceQueryRegister_;
}

template <>
inline Context::Register& Context::register_<DistanceResult>() noexcept
{
    return distanceResultRegister_;
}

}  // namespace sim
}  // namespace xvec
