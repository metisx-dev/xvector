#include "xvector/xvec_context.h"

#include "context.hpp"

extern "C"
{
xvecStatus xvecCreateContext(xvecContext *context_)
{
    try
    {
        auto context = new xvec::sim::Context();
        *context_ = reinterpret_cast<xvecContext>(context);
    }
    catch (std::bad_alloc &e)
    {
        return XVEC_ERROR_OUT_OF_MEMORY;
    }
    catch (...)
    {
        return XVEC_ERROR_UNKNOWN;
    }
    
    return XVEC_SUCCESS;
}

xvecStatus xvecDestroyContext(xvecContext context_)
{
    auto context = reinterpret_cast<xvec::sim::Context *>(context_);
    delete context;
    return XVEC_SUCCESS;
}
}  // extern "C"
