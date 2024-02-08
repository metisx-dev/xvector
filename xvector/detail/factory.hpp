#pragma once

#include "shared_ptr.hpp"

namespace xvec
{
namespace detail
{

template <typename Derived>
class Factory
{
public:
    template <typename... Args>
    static SharedPtr<Derived> create(Args&&... args);
};

template <typename Derived>
template <typename... Args>
SharedPtr<Derived> xvec::detail::Factory<Derived>::create(Args&&... args)
{
    Derived* obj = new Derived(std::forward<Args>(args)...);
    return SharedPtr<Derived>::weak(obj);
}

}  // namespace detail
}  // namespace xvec
