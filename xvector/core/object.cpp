#include "object.hpp"

#include "context_base.hpp"

namespace xvec
{
namespace core
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

}  // namespace core
}  // namespace xvec
