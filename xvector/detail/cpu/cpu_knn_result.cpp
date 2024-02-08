
#include "cpu_knn_result.hpp"

namespace xvec
{
namespace detail
{
CpuKnnResult::CpuKnnResult(Context* context,
                           xvecFloatType floatType,
                 const std::shared_ptr<uint8_t[]>& scores,
                 const std::shared_ptr<xvecIndex[]>& indices,
                 const std::shared_ptr<xvecVectorArray[]>& vectorArrays) noexcept
    : Managed<CpuKnnResult>(context),
      floatType_(floatType),
      k_(0),
      scores_(scores),
      indices_(indices),
      vectorArrays_(vectorArrays)
{
}

}  // namespace detail
}  // namespace xvec
