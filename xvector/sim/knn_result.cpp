
#include "knn_result.hpp"

namespace xvec
{
namespace sim
{
KnnResult::KnnResult(Context* context,
                           xvecFloatType floatType,
                           const std::shared_ptr<uint8_t[]>& scores,
                           const std::shared_ptr<xvecIndex[]>& indices,
                           const std::shared_ptr<xvecVectorArray[]>& vectorArrays) noexcept
    : Managed<KnnResult>(context),
      floatType_(floatType),
      k_(0),
      scores_(scores),
      indices_(indices),
      vectorArrays_(vectorArrays)
{
}

}  // namespace sim
}  // namespace xvec
