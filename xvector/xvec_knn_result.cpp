#include "xvec_knn_result.h"

#include <cstring>

#include "xvector/detail/knn_result.hpp"

extern "C"
{
xvecStatus xvecReleaseKnnResult(xvecKnnResult result_)
{
    auto result = reinterpret_cast<xvec::detail::KnnResult*>(result_);
    result->release();
    return XVEC_SUCCESS;
}

xvecStatus xvecGetKnnResultK(xvecKnnResult result_, size_t* k)
{
    auto result = reinterpret_cast<xvec::detail::KnnResult*>(result_);
    *k = result->k();
    return XVEC_SUCCESS;
}

xvecStatus xvecGetKnnResultScores(xvecKnnResult result_, float** scores_)
{
    auto result = reinterpret_cast<xvec::detail::KnnResult*>(result_);
    *scores_ = reinterpret_cast<float*>(result->scores().get());
    return XVEC_SUCCESS;
}

xvecStatus xvecGetKnnResultIndices(xvecKnnResult result_, xvecIndex** indices_)
{
    auto result = reinterpret_cast<xvec::detail::KnnResult*>(result_);
    *indices_ = result->indices().get();
    return XVEC_SUCCESS;
}

xvecStatus xvecGetKnnResultVectorArrays(xvecKnnResult result, xvecVectorArray** vectorArrays_)
{
    auto result_ = reinterpret_cast<xvec::detail::KnnResult*>(result);
    *vectorArrays_ = result_->vectorArrays().get();
    return XVEC_SUCCESS;
}

}  // extern "C"
