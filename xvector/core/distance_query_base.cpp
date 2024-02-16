#include "distance_query_base.hpp"

#include "xvector/xvec_distance_query.h"

namespace xvec
{
namespace core
{

DistanceQueryBase::DistanceQueryBase(ContextBase* context,
                                     xvecDistanceType type,
                                     const std::shared_ptr<uint8_t[]>& vector,
                                     xvecFloatType floatType,
                                     std::size_t dimension)
    : Object(ObjectType::DistanceQuery, context),
      type_(type),
      floatType_(floatType),
      dimension_(dimension),
      vector_(vector),
      result_()
{
}

}  // namespace core
}  // namespace xvec
