#include "xvec_query.h"

#include <cstring>

#include "xvector/detail/cpu/cpu_query.hpp"

extern "C"
{
xvecStatus xvecExecuteQuery(void* queries_, size_t count)
{
    auto queries = reinterpret_cast<xvec::detail::CpuQuery**>(queries_);
    xvec::detail::executeQuery(queries, count);
    return XVEC_SUCCESS;
}

}  // extern "C"
