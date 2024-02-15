#include "xvector/xvec_query.h"

#include <cstring>

#include "query.hpp"

extern "C"
{
xvecStatus xvecExecuteQuery(void* queries_, size_t count)
{
    auto queries = reinterpret_cast<xvec::detail::Object**>(queries_);
    xvec::sim::executeQuery(queries, count);
    return XVEC_SUCCESS;
}

}  // extern "C"
