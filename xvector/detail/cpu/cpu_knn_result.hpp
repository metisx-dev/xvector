#pragma once

#include <cstddef>
#include <memory>

#include "xvector/detail/factory.hpp"
#include "xvector/detail/managed.hpp"
#include "xvector/xvec_float_type.h"
#include "xvector/xvec_index.h"
#include "xvector/xvec_vector_array.h"

namespace xvec
{
namespace detail
{
class CpuKnnResult : public Factory<CpuKnnResult>, public Managed<CpuKnnResult>
{
    friend Factory<CpuKnnResult>;

public:
    xvecFloatType floatType() const noexcept
    {
        return floatType_;
    }

    std::size_t k() const noexcept
    {
        return k_;
    }

    void setK(std::size_t k) noexcept
    {
        k_ = k;
    }

    const std::shared_ptr<uint8_t[]>& scores() const noexcept
    {
        return scores_;
    }

    const std::shared_ptr<xvecIndex[]>& indices() const noexcept
    {
        return indices_;
    }

    const std::shared_ptr<xvecVectorArray[]>& vectorArrays() const noexcept
    {
        return vectorArrays_;
    }

private:
    CpuKnnResult(Context* context,
                 xvecFloatType floatType,
                 const std::shared_ptr<uint8_t[]>& scores,
                 const std::shared_ptr<xvecIndex[]>& indices,
                 const std::shared_ptr<xvecVectorArray[]>& vectorArrays) noexcept;

    CpuKnnResult(const CpuKnnResult& src) = delete;
    CpuKnnResult& operator=(const CpuKnnResult& src) = delete;

    xvecFloatType floatType_;
    std::size_t k_;
    std::shared_ptr<uint8_t[]> scores_;
    std::shared_ptr<xvecIndex[]> indices_;
    std::shared_ptr<xvecVectorArray[]> vectorArrays_;
};

#ifndef XVEC_MU_SUPPORT
using KnnResult = CpuKnnResult;
#endif

}  // namespace detail
}  // namespace xvec
