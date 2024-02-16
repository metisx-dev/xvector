#include "context_base.hpp"

namespace xvec
{
namespace core
{

std::size_t ContextBase::Register::register_(Object* object)
{
    std::lock_guard<SpinLock> guard(lock);

    std::size_t id;

    if (freeIds.empty())
    {
        id = objects.size();
        objects.push_back(object);
    }
    else
    {
        id = freeIds.back();
        freeIds.pop_back();
        objects[id] = object;
    }

    return id;
}

void ContextBase::Register::unregister(std::size_t id)
{
    std::lock_guard<SpinLock> guard(lock);

    objects[id] = nullptr;
    freeIds.push_back(id);
}

Object* ContextBase::Register::object(std::size_t id)
{
    return objects[id];
}

ContextBase::ContextBase() noexcept
{
}

ContextBase::~ContextBase() noexcept
{
    for (auto knnQuery : registers_[static_cast<std::size_t>(ObjectType::KnnQuery)].objects)
    {
        if (knnQuery)
        {
            delete knnQuery;
        }
    }

    for (auto knnResultRegister_ : registers_[static_cast<std::size_t>(ObjectType::KnnResult)].objects)
    {
        if (knnResultRegister_)
        {
            delete knnResultRegister_;
        }
    }

    for (auto distanceQuery : registers_[static_cast<std::size_t>(ObjectType::DistanceQuery)].objects)
    {
        if (distanceQuery)
        {
            delete distanceQuery;
        }
    }

    for (auto distanceResult : registers_[static_cast<std::size_t>(ObjectType::DistanceResult)].objects)
    {
        if (distanceResult)
        {
            delete distanceResult;
        }
    }

    for (auto filter : registers_[static_cast<std::size_t>(ObjectType::Filter)].objects)
    {
        if (filter)
        {
            delete filter;
        }
    }

    for (auto indexArray : registers_[static_cast<std::size_t>(ObjectType::IndexArray)].objects)
    {
        if (indexArray)
        {
            delete indexArray;
        }
    }

    for (auto vectorArray : registers_[static_cast<std::size_t>(ObjectType::VectorArray)].objects)
    {
        if (vectorArray)
        {
            delete vectorArray;
        }
    }

    for (auto deviceBuffer : registers_[static_cast<std::size_t>(ObjectType::DeviceBuffer)].objects)
    {
        if (deviceBuffer)
        {
            delete deviceBuffer;
        }
    }
}

}  // namespace core
}  // namespace xvec
