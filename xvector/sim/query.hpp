#pragma once

#include <cstddef>

#include "core/object.hpp"

namespace xvec
{
namespace sim
{

void executeQuery(core::Object** queries, std::size_t count);

}  // namespace sim
}  // namespace xvec
