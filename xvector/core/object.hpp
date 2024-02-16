#pragma once

#include "shared_ptr.hpp"

namespace xvec
{
namespace core
{

class ContextBase;

enum class ObjectType
{
    DeviceBuffer,
    VectorArray,
    IndexArray,
    Filter,
    KnnQuery,
    KnnResult,
    DistanceQuery,
    DistanceResult,
    Max_
};

class Object : public Shared
{
public:
    virtual ~Object() noexcept = 0;

    ContextBase* context() const noexcept
    {
        return context_;
    }

    std::size_t id() const noexcept
    {
        return id_;
    }

    ObjectType type() const noexcept
    {
        return type_;
    }

protected:
    Object(ObjectType type, ContextBase* context);

    Object(const Object& src) = delete;

    Object& operator=(const Object& src) = delete;

private:
    ObjectType type_;
    ContextBase* context_;
    std::size_t id_;
};

}  // namespace core
}  // namespace xvec
