#pragma once

#include "context.hpp"
#include "shared_ptr.hpp"

namespace xvec
{
namespace sim
{

template <typename Derived>
class Managed : public Shared
{
public:
    using Id = Context::ObjectId;

    virtual ~Managed() noexcept;

    Context* context() const noexcept
    {
        return context_;
    }

    Id id() const noexcept
    {
        return id_;
    }

protected:
    explicit Managed(Context* context);

    Managed(const Managed& src) = delete;
    Managed& operator=(const Managed& src) = delete;

private:
    Context* context_;
    Id id_;
};

template <typename Derived>
Managed<Derived>::Managed(Context* context)
    : context_(context)
{
    auto& reg = context->register_<Derived>();
    id_ = reg.register_(this);
}

template <typename Derived>
Managed<Derived>::~Managed() noexcept
{
    auto& reg = context_->register_<Derived>();
    reg.unregister(id_);
}

}  // namespace detail
}  // namespace xvec
