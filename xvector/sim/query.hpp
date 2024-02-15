#pragma once

#include <cstddef>

#include "detail/object.hpp"

namespace xvec
{
namespace sim
{

void executeQuery(detail::Object** queries, std::size_t count);

}  // namespace sim
}  // namespace xvec
