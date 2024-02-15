#pragma once

#include <cstddef>
#include <memory>

#include "object.hpp"
#include "xvector/xvec_float_type.h"
#include "xvector/xvec_index.h"
#include "xvector/xvec_vector_array.h"

namespace xvec
{
namespace detail
{
class KnnResultBase : public Object
{
public:
    KnnResultBase(ContextBase* context,
                  xvecFloatType floatType,
                  const std::shared_ptr<uint8_t[]>& scores,
                  const std::shared_ptr<xvecIndex[]>& indices,
                  const std::shared_ptr<xvecVectorArray[]>& vectorArrays) noexcept;

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
    KnnResultBase(const KnnResultBase& src) = delete;
    KnnResultBase& operator=(const KnnResultBase& src) = delete;

    xvecFloatType floatType_;
    std::size_t k_;
    std::shared_ptr<uint8_t[]> scores_;
    std::shared_ptr<xvecIndex[]> indices_;
    std::shared_ptr<xvecVectorArray[]> vectorArrays_;
};

}  // namespace detail
}  // namespace xvec
