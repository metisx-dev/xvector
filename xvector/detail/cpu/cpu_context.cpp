#include "cpu_context.hpp"

#include <mutex>

#include "xvector/detail/cpu/cpu_device_buffer.hpp"
#include "xvector/detail/cpu/cpu_distance_query.hpp"
#include "xvector/detail/cpu/cpu_index_array.hpp"
#include "xvector/detail/cpu/cpu_knn_query.hpp"
#include "xvector/detail/cpu/cpu_vector_array.hpp"

namespace xvec
{
namespace detail
{

std::uint32_t CpuContext::Register::register_(void* object)
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

void CpuContext::Register::unregister(std::uint32_t id)
{
    std::lock_guard<SpinLock> guard(lock);

    objects[id] = nullptr;
    freeIds.push_back(id);
}

CpuContext::CpuContext() noexcept
{
}

CpuContext::~CpuContext() noexcept
{
    for (auto knnQuery : knnQueryRegister_.objects)
    {
        if (knnQuery)
        {
            delete static_cast<Managed<CpuKnnQuery>*>(knnQuery);
        }
    }

    for (auto knnResultRegister_ : knnResultRegister_.objects)
    {
        if (knnResultRegister_)
        {
            delete static_cast<Managed<CpuKnnResult>*>(knnResultRegister_);
        }
    }

    for (auto distanceQuery : distanceQueryRegister_.objects)
    {
        if (distanceQuery)
        {
            delete static_cast<Managed<CpuDistanceQuery>*>(distanceQuery);
        }
    }

    for (auto distanceResult : distanceResultRegister_.objects)
    {
        if (distanceResult)
        {
            delete static_cast<Managed<CpuDistanceResult>*>(distanceResult);
        }
    }

    for (auto indexArray : indexArrayRegister_.objects)
    {
        if (indexArray)
        {
            delete static_cast<Managed<CpuIndexArray>*>(indexArray);
        }
    }

    for (auto vectorArray : vectorArrayRegister_.objects)
    {
        if (vectorArray)
        {
            delete static_cast<Managed<CpuVectorArray>*>(vectorArray);
        }
    }

    for (auto deviceBuffer : deviceBufferRegister_.objects)
    {
        if (deviceBuffer)
        {
            delete static_cast<Managed<CpuDeviceBuffer>*>(deviceBuffer);
        }
    }

    for (auto hostBuffer : hostBufferRegister_.objects)
    {
        if (hostBuffer)
        {
            delete static_cast<Managed<CpuHostBuffer>*>(hostBuffer);
        }
    }
}

}  // namespace detail
}  // namespace xvec
