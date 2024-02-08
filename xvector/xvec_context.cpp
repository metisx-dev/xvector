#include "xvec_context.h"

#include "xvector/detail/context.hpp"

extern "C"
{
xvecStatus xvecCreateContext(xvecContext *context_)
{
    auto context = new xvec::detail::Context();
    *context_ = reinterpret_cast<xvecContext>(context);
    return XVEC_SUCCESS;
}

xvecStatus xvecDestroyContext(xvecContext context_)
{
    auto context = reinterpret_cast<xvec::detail::Context *>(context_);
    delete context;
    return XVEC_SUCCESS;
}
}  // extern "C"
