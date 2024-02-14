#include "context.hpp"

#include "distance_query.hpp"
#include "filter.hpp"
#include "index_array.hpp"
#include "knn_query.hpp"
#include "vector_array.hpp"

namespace xvec
{
namespace sim
{

std::uint32_t Context::Register::register_(void* object)
{
    std::lock_guard<SpinLock> guard(lock);

    std::uint32_t id;

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

void Context::Register::unregister(std::uint32_t id)
{
    std::lock_guard<SpinLock> guard(lock);

    objects[id] = nullptr;
    freeIds.push_back(id);
}

Context::Context() noexcept
{
}

Context::~Context() noexcept
{
    for (auto knnQuery : knnQueryRegister_.objects)
    {
        if (knnQuery)
        {
            delete static_cast<Managed<KnnQuery>*>(knnQuery);
        }
    }

    for (auto knnResultRegister_ : knnResultRegister_.objects)
    {
        if (knnResultRegister_)
        {
            delete static_cast<Managed<KnnResult>*>(knnResultRegister_);
        }
    }

    for (auto distanceQuery : distanceQueryRegister_.objects)
    {
        if (distanceQuery)
        {
            delete static_cast<Managed<DistanceQuery>*>(distanceQuery);
        }
    }

    for (auto distanceResult : distanceResultRegister_.objects)
    {
        if (distanceResult)
        {
            delete static_cast<Managed<DistanceResult>*>(distanceResult);
        }
    }

    for (auto filter : filterRegister_.objects)
    {
        if (filter)
        {
            delete static_cast<Managed<Filter>*>(filter);
        }
    }

    for (auto indexArray : indexArrayRegister_.objects)
    {
        if (indexArray)
        {
            delete static_cast<Managed<IndexArray>*>(indexArray);
        }
    }

    for (auto vectorArray : vectorArrayRegister_.objects)
    {
        if (vectorArray)
        {
            delete static_cast<Managed<VectorArray>*>(vectorArray);
        }
    }

    for (auto deviceBuffer : deviceBufferRegister_.objects)
    {
        if (deviceBuffer)
        {
            delete static_cast<Managed<DeviceBuffer>*>(deviceBuffer);
        }
    }
}

}  // namespace detail
}  // namespace xvec
