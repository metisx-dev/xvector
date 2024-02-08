#include "xvec_index_array.h"

#include "xvector/detail/context.hpp"
#include "xvector/detail/index_array.hpp"
#include "xvector/detail/vector_array.hpp"

extern "C"
{
xvecStatus xvecCreateIndexArray(xvecIndexArray* indexArray_, xvecVectorArray target_)
{
    auto target = reinterpret_cast<xvec::detail::VectorArray*>(target_);
    auto indexArray = xvec::detail::IndexArray::create(target);
    if (indexArray == nullptr)
        return XVEC_ERROR_OUT_OF_MEMORY;

    indexArray->retain();
    *indexArray_ = reinterpret_cast<xvecIndexArray>(indexArray.get());
    return XVEC_SUCCESS;
}

xvecStatus xvecReleaseIndexArray(xvecIndexArray indexArray_)
{
    auto indexArray = reinterpret_cast<xvec::detail::IndexArray*>(indexArray_);
    indexArray->release();
    return XVEC_SUCCESS;
}

xvecStatus xvecGetIndexArrayTarget(xvecIndexArray indexArray_, xvecVectorArray* target_)
{
    auto indexArray = reinterpret_cast<xvec::detail::IndexArray*>(indexArray_);
    auto target = indexArray->target();
    target->retain();
    *target_ = reinterpret_cast<xvecVectorArray>(target.get());
    return XVEC_SUCCESS;
}

xvecStatus xvecSetIndexArrayIndices(xvecIndexArray indexArray_, xvecBuffer targetIndices_, size_t size)
{
    auto indexArray = reinterpret_cast<xvec::detail::IndexArray*>(indexArray_);
    auto targetIndices = reinterpret_cast<xvec::detail::HostBuffer*>(targetIndices_);
    // auto validityBitmap = reinterpret_cast<xvec::detail::HostBuffer*>(validityBitmap_);
    indexArray->setIndices(targetIndices, size);
    return XVEC_SUCCESS;
}

xvecStatus xvecGetIndexArrayIndices(xvecIndexArray indexArray_, xvecBuffer* targetIndices_)
{
    auto indexArray = reinterpret_cast<xvec::detail::IndexArray*>(indexArray_);

    auto targetIndices = indexArray->indices();
    if (targetIndices)
        targetIndices->retain();
    *targetIndices_ = reinterpret_cast<xvecBuffer>(targetIndices.get());
    return XVEC_SUCCESS;
}

xvecStatus xvecGetIndexArraySize(xvecIndexArray indexArray, size_t* size)
{
    auto arr = reinterpret_cast<xvec::detail::IndexArray*>(indexArray);
    *size = arr->size();
    return XVEC_SUCCESS;
}

xvecStatus xvecSetIndexArrayCustomData(xvecIndexArray indexArray_, uintptr_t customData)
{
    auto indexArray = reinterpret_cast<xvec::detail::IndexArray*>(indexArray_);
    indexArray->setCustomData(customData);
    return XVEC_SUCCESS;
}

xvecStatus xvecGetIndexArrayCustomData(xvecIndexArray indexArray_, uintptr_t* customData)
{
    auto indexArray = reinterpret_cast<xvec::detail::IndexArray*>(indexArray_);
    *customData = indexArray->customData();
    return XVEC_SUCCESS;
}

}  // extern "C"
