#include "object.hpp"

#include "context_base.hpp"

namespace xvec
{
namespace detail
{
Object::Object(ObjectType type, ContextBase* context)
    : type_(type),
      context_(context)
{
    id_ = context->register_(type, this);
}

Object::~Object() noexcept
{
    context_->unregister(type_, id_);
}

}  // namespace detail
}  // namespace xvec
