
#include "knn_result_base.hpp"

namespace xvec
{
namespace detail
{
KnnResultBase::KnnResultBase(ContextBase* context,
                             xvecFloatType floatType,
                             const std::shared_ptr<uint8_t[]>& scores,
                             const std::shared_ptr<xvecIndex[]>& indices,
                             const std::shared_ptr<xvecVectorArray[]>& vectorArrays) noexcept
    : Object(ObjectType::KnnResult, context),
      floatType_(floatType),
      k_(0),
      scores_(scores),
      indices_(indices),
      vectorArrays_(vectorArrays)
{
}

}  // namespace detail
}  // namespace xvec
