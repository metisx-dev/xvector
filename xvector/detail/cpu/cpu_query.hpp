#pragma once

#include <cstddef>

#include "xvector/detail/buffer.hpp"
#include "xvector/detail/cpu/cpu_knn_result.hpp"
#include "xvector/detail/managed.hpp"
#include "xvector/xvec_knn_query.h"

namespace xvec
{
namespace detail
{

class CpuQuery
{
public:
    enum Type
    {
        Knn,
        Distance
    };

    Type queryType() const noexcept
    {
        return queryType_;
    }

protected:
    CpuQuery(Type queryType) noexcept
        : queryType_(queryType)
    {
    }

    virtual ~CpuQuery() noexcept = default;

    Type queryType_;
};

void executeQuery(xvec::detail::CpuQuery** queries, std::size_t count);

}  // namespace detail
}  // namespace xvec
