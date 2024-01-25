#ifndef __XVECTOR_H__
#define __XVECTOR_H__

#include <stdint.h>

#include <cstdlib>

extern "C"
{
    #include "xvec_status.h"

    typedef enum xvecFloatType
    {
        XVEC_FLOAT32,
        XVEC_FLOAT16
    } xvecFloatType;

    typedef struct xvecBufferTag
    {
        void* p;
    } xvecBuffer;

    typedef struct xvecVectorArrayTag
    {
        void* p;
    } xvecVectorArray;

    typedef struct xvecIndirectArrayTag
    {
        void* p;
    } xvecIndirectArray;

    typedef struct xvecQueryTag
    {
        void* p;
    } xvecQuery;

    // Buffer Buffer Manipulation APIs
    xvecStatus xvecCreateBuffer(xvecBuffer* buffer, const size_t bytes);
    xvecStatus xvecReleaseBuffer(xvecBuffer buffer);
    xvecStatus xvecBufferGetPointer(xvecBuffer buffer, void** data);
    xvecStatus xvecBufferGetCapacity(xvecBuffer buffer, size_t* bytes);
    xvecStatus xvecBufferReserve(xvecBuffer buffer, const size_t bytes);

    // Vector Array Manipulation APIs
    xvecStatus xvecCreateVectorArray(xvecVectorArray* vectorArray,
                                     xvecFloatType type,
                                     const size_t dim);
    xvecStatus xvecReleaseVectorArray(xvecVectorArray vectorArray);
    xvecStatus xvecVectorArraySetBuffer(xvecVectorArray vectorArray,
                                        xvecBuffer data,
                                        const size_t size);
    xvecStatus xvecVectorArrayGetBuffer(xvecVectorArray vectorArray, xvecBuffer* data);
    xvecStatus xvecVectorArrayGetSize(xvecVectorArray vectorArray, size_t* size);
    xvecStatus xvecVectorArrayGetDimension(xvecVectorArray vectorArray, size_t* dim);

    // Indirect Array Manipulation APIs
    xvecStatus xvecCreateIndirectArray(xvecIndirectArray* indirectArray,
                                       xvecVectorArray vectorArray);
    xvecStatus xvecReleaseIndirectArray(xvecIndirectArray indirectArray);
    xvecStatus xvecSetIndirectArrayBuffer(xvecIndirectArray indirectArray,
                                          xvecBuffer data,
                                          size_t size);
    xvecStatus xvecGetIndirectArrayBuffer(xvecIndirectArray indirectArray, xvecBuffer* data);
    xvecStatus xvecGetIndirectArraySize(xvecIndirectArray indirectArray, size_t* size);

    // Indirect Array Manipulation APIs
    xvecStatus xvecCreateQuery(xvecQuery* query, xvecBuffer data, const size_t dim);
    xvecStatus xvecReleaseQuery(xvecQuery query);
    xvecStatus xvecSetQueryTopK(xvecQuery query, const size_t k);
    xvecStatus xvecSetQueryIndirect(xvecQuery query, xvecIndirectArray data, const size_t size);
    xvecStatus xvecSetQueryTarget(xvecQuery query, xvecVectorArray data);
    xvecStatus xvecGetQueryBuffer(xvecQuery query, xvecBuffer* data);
    xvecStatus xvecGetQueryDimension(xvecQuery query, size_t* dim);
    xvecStatus xvecGetQueryIndexes(xvecQuery query, xvecBuffer* indexes);
    xvecStatus xvecGetQueryScores(xvecQuery query, xvecBuffer* scores);

    // Cosine Similarity Calculation APIs
    xvecStatus xvecCalculateConsineSimilarity(xvecQuery* queries, const size_t queriesCount);
    xvecStatus xvecCalculateL2Distance(xvecQuery* queries, const size_t queriesCount);
}

#endif