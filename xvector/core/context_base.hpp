#pragma once

#include <cstdint>
#include <vector>

#include "object.hpp"
#include "shared_ptr.hpp"
#include "spin_lock.hpp"

namespace xvec
{
namespace core
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

class ContextBase
{
public:
    ContextBase() noexcept;

    ContextBase(const ContextBase& src) = delete;

    virtual ~ContextBase() noexcept;

    ContextBase& operator=(const ContextBase& src) = delete;

    // xvecBufferId register_(DeviceBuffer* buffer) noexcept;
    // void unregister(xvecBufferId id) noexcept;

    struct Register
    {
        std::size_t register_(Object* object);
        void unregister(std::size_t id);

        Object* object(std::size_t id);

        std::vector<Object*> objects;
        std::vector<std::uint32_t> freeIds;
        SpinLock lock;
    };

    Object* object(ObjectType type, std::size_t id) noexcept
    {
        return registers_[static_cast<std::size_t>(type)].object(id);
    }

    std::size_t register_(ObjectType type, Object* object)
    {
        return registers_[static_cast<std::size_t>(type)].register_(object);
    }

    void unregister(ObjectType type, std::size_t id)
    {
        registers_[static_cast<std::size_t>(type)].unregister(id);
    }

private:
    Register registers_[static_cast<std::size_t>(ObjectType::Max_)];
};

#if 0
template <>
inline ContextBase::Register& ContextBase::register_<VectorArray>() noexcept
{
    return vectorArrayRegister_;
}

template <>
inline ContextBase::Register& ContextBase::register_<IndexArray>() noexcept
{
    return indexArrayRegister_;
}

template <>
inline ContextBase::Register& ContextBase::register_<Filter>() noexcept
{
    return filterRegister_;
}

template <>
inline ContextBase::Register& ContextBase::register_<KnnQuery>() noexcept
{
    return knnQueryRegister_;
}

template <>
inline ContextBase::Register& ContextBase::register_<KnnResult>() noexcept
{
    return knnResultRegister_;
}

template <>
inline ContextBase::Register& ContextBase::register_<DistanceQuery>() noexcept
{
    return distanceQueryRegister_;
}

template <>
inline ContextBase::Register& ContextBase::register_<DistanceResult>() noexcept
{
    return distanceResultRegister_;
}
#endif

}  // namespace core
}  // namespace xvec
