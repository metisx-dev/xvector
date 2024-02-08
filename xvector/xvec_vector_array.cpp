#include "xvec_vector_array.h"

#include "xvector/detail/context.hpp"
#include "xvector/detail/vector_array.hpp"

extern "C"
{
xvecStatus xvecCreateVectorArray(xvecVectorArray* vectorArray_,
                                 xvecContext context_,
                                 size_t dimension)
{
    auto context = reinterpret_cast<xvec::detail::Context*>(context_);
    auto vectorArray = xvec::detail::VectorArray::create(context, XVEC_FLOAT32, dimension);
    if (vectorArray == nullptr)
        return XVEC_ERROR_OUT_OF_MEMORY;

    vectorArray->retain();
    *vectorArray_ = reinterpret_cast<xvecVectorArray>(vectorArray.get());
    return XVEC_SUCCESS;
}

xvecStatus xvecReleaseVectorArray(xvecVectorArray vectorArray_)
{
    auto vectorArray = reinterpret_cast<xvec::detail::VectorArray*>(vectorArray_);
    vectorArray->release();
    return XVEC_SUCCESS;
}

xvecStatus xvecGetVectorArrayDimension(xvecVectorArray vectorArray_, size_t* dim)
{
    auto vectorArray = reinterpret_cast<xvec::detail::VectorArray*>(vectorArray_);
    *dim = vectorArray->dimension();
    return XVEC_SUCCESS;
}

xvecStatus xvecSetVectorArrayVectors(xvecVectorArray vectorArray_, xvecBuffer vectors_, size_t size)
{
    auto vectorArray = reinterpret_cast<xvec::detail::VectorArray*>(vectorArray_);
    auto vectors = reinterpret_cast<xvec::detail::HostBuffer*>(vectors_);

    vectorArray->setVectors(vectors, size);

    return XVEC_SUCCESS;
}

xvecStatus xvecGetVectorArrayVectors(xvecVectorArray vectorArray_, xvecBuffer* vectors_)
{
    auto vectorArray = reinterpret_cast<xvec::detail::VectorArray*>(vectorArray_);
    auto vectors = vectorArray->vectors();
    if (vectors)
        vectors->retain();
    *vectors_ = reinterpret_cast<xvecBuffer>(vectors.get());
    return XVEC_SUCCESS;
}

xvecStatus xvecGetVectorArraySize(xvecVectorArray vectorArray_, size_t* size)
{
    auto vectorArray = reinterpret_cast<xvec::detail::VectorArray*>(vectorArray_);
    *size = vectorArray->size();
    return XVEC_SUCCESS;
}

xvecStatus xvecSetVectorArrayCustomData(xvecVectorArray vectorArray_, void* customData)
{
    auto vectorArray = reinterpret_cast<xvec::detail::VectorArray*>(vectorArray_);
    vectorArray->setCustomData(customData);
    return XVEC_SUCCESS;
}

xvecStatus xvecGetVectorArrayCustomData(xvecVectorArray vectorArray_, void** customData)
{
    auto vectorArray = reinterpret_cast<xvec::detail::VectorArray*>(vectorArray_);
    *customData = vectorArray->customData();
    return XVEC_SUCCESS;
}

}  // extern "C"
