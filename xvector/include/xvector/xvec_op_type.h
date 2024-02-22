#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum xvecOpType
{
    XVEC_OP_DOT_PRODUCT,
    XVEC_OP_L2_DISTANCE,  // TODO: Not yet supported
    XVEC_OP_COSINE_SIMILARITY,  // TODO Not yet supported
} xvecOpType;

#ifdef __cplusplus
}
#endif
