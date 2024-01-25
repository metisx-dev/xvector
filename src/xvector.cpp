#include "xvector.hpp"

#include <cstring>
#include <iostream>

#include "xvec_buffer/xvec_buffer.hpp"

extern "C"
{
    xvecStatus xvecCreateBuffer(xvecBuffer* buffer, const size_t bytes)
    {
        xvecStatus status = xvecStatus::XVEC_STATUS_SUCCESS;

        xvecSharedPtr<metisx::pg_xvector::xvecBufferObject>* temp =
            new xvecSharedPtr<metisx::pg_xvector::xvecBufferObject>();

        status = (*temp)->reserveMemory(bytes);

        buffer->p = temp->shareRawPtr();

        return status;
    };

    xvecStatus xvecReleaseBuffer(xvecBuffer buffer)
    {
        auto& xvecBuffer =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecBufferObject>*>(buffer.p);
        xvecBuffer.release();

        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecBufferGetPointer(xvecBuffer buffer, void** data)
    {
        auto& xvecBuffer =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecBufferObject>*>(buffer.p);

        if (xvecBuffer == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        *data = xvecBuffer->getRawPointer();
        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecBufferGetCapacity(xvecBuffer buffer, size_t* bytes)
    {
        auto& xvecBuffer =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecBufferObject>*>(buffer.p);

        if (xvecBuffer == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        *bytes = xvecBuffer->getByteSize();
        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecBufferReserve(xvecBuffer buffer, const size_t bytes)
    {
        auto& xvecBuffer =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecBufferObject>*>(buffer.p);

        if (xvecBuffer == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        return xvecBuffer->reserveMemory(bytes);
    };

    xvecStatus xvecCreateVectorArray(xvecVectorArray* vectorArray,
                                     xvecFloatType type,
                                     const size_t dim)
    {
        xvecStatus status = xvecStatus::XVEC_STATUS_SUCCESS;

        xvecSharedPtr<metisx::pg_xvector::xvecVectorArrayObject>* temp =
            new xvecSharedPtr<metisx::pg_xvector::xvecVectorArrayObject>(dim, type);

        vectorArray->p = temp->shareRawPtr();

        return status;
    };

    xvecStatus xvecReleaseVectorArray(xvecVectorArray vectorArray)
    {
        auto& xvecVector =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecVectorArrayObject>*>(
                vectorArray.p);

        xvecVector.release();
        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecVectorArraySetBuffer(xvecVectorArray vectorArray,
                                        xvecBuffer data,
                                        [[maybe_unused]] const size_t size)
    {
        auto& allocatedHeap =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecBufferObject>*>(data.p);

        if (allocatedHeap == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        auto& xvecVector =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecVectorArrayObject>*>(
                vectorArray.p);

        if (xvecVector == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        if (xvecVector->getSize() != 0)
        {
            xvecVector->clear();
        }

        return xvecVector->setMemory(allocatedHeap.shareDataPtr());
    };

    xvecStatus xvecVectorArrayGetBuffer(xvecVectorArray vectorArray, xvecBuffer* data)
    {
        auto& xvecVector =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecVectorArrayObject>*>(
                vectorArray.p);

        if (xvecVector == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        data->p = xvecVector->getRawPointer();

        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecVectorArrayGetSize(xvecVectorArray vectorArray, size_t* size)
    {
        auto& xvecVector =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecVectorArrayObject>*>(
                vectorArray.p);

        if (xvecVector == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        *size = xvecVector->getSize();

        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecVectorArrayGetDimension(xvecVectorArray vectorArray, size_t* dim)
    {
        auto& xvecVector =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecVectorArrayObject>*>(
                vectorArray.p);

        if (xvecVector == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        *dim = xvecVector->getDim();

        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecCreateIndirectArray(xvecIndirectArray* indirectArray,
                                       xvecVectorArray vectorArray)
    {
        xvecStatus status = xvecStatus::XVEC_STATUS_SUCCESS;

        auto& xvecVector =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecVectorArrayObject>*>(
                vectorArray.p);

        xvecSharedPtr<metisx::pg_xvector::xvecIndirectArrayObject>* temp =
            new xvecSharedPtr<metisx::pg_xvector::xvecIndirectArrayObject>(
                xvecVector.shareDataPtr());

        indirectArray->p = temp->shareRawPtr();

        return status;
    };

    xvecStatus xvecReleaseIndirectArray(xvecIndirectArray indirectArray)
    {
        auto& indirectArrayObject =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecIndirectArrayObject>*>(
                indirectArray.p);

        indirectArrayObject->clear();
        indirectArrayObject.release();
        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecSetIndirectArrayBuffer(xvecIndirectArray indirectArray,
                                          xvecBuffer data,
                                          [[maybe_unused]] size_t size)
    {
        auto& indirectArrayObject =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecIndirectArrayObject>*>(
                indirectArray.p);

        auto& buffer =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecBufferObject>*>(data.p);

        if (indirectArrayObject == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        if (buffer == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        if (indirectArrayObject->getSize() != 0)
        {
            indirectArrayObject->clear();
        }

        return indirectArrayObject->setMemory(buffer.shareDataPtr());
    };

    xvecStatus xvecGetIndirectArrayBuffer(xvecIndirectArray indirectArray, xvecBuffer* data)
    {
        auto& indirectArrayObject =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecIndirectArrayObject>*>(
                indirectArray.p);

        if (indirectArrayObject == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        data->p = indirectArrayObject->getRawPointer();

        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecGetIndirectArraySize(xvecIndirectArray indirectArray, size_t* size)
    {
        auto& indirectArrayObject =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecIndirectArrayObject>*>(
                indirectArray.p);

        if (indirectArrayObject == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        *size = indirectArrayObject->getSize();

        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecCreateQuery(xvecQuery* query, xvecBuffer data, const size_t dim)
    {
        xvecStatus status = xvecStatus::XVEC_STATUS_SUCCESS;

        auto& bufferHandler =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecBufferObject>*>(data.p);

        xvecSharedPtr<metisx::pg_xvector::xvecQueryObject>* temp =
            new xvecSharedPtr<metisx::pg_xvector::xvecQueryObject>(bufferHandler.shareDataPtr(),
                                                                   dim);

        query->p = temp->shareRawPtr();

        return status;
    };

    xvecStatus xvecReleaseQuery(xvecQuery query)
    {
        auto& queryHandler =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecQueryObject>*>(query.p);

        queryHandler->clear();
        queryHandler.release();
        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecSetQueryTopK(xvecQuery query, const size_t k)
    {
        auto& queryHandler =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecQueryObject>*>(query.p);

        if (queryHandler == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        return queryHandler->setTopK(k);
    };

    xvecStatus xvecSetQueryIndirect(xvecQuery query, xvecIndirectArray data, [[maybe_unused]] const size_t size)
    {
        // Indirect / Vector selection
        auto& queryHandler =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecQueryObject>*>(query.p);

        if (queryHandler == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        auto& indirectArrayHandler =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecIndirectArrayObject>*>(data.p);

        if (indirectArrayHandler == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        return queryHandler->setIndirects(*indirectArrayHandler.shareDataPtr());
    };

    xvecStatus xvecSetQueryTarget(xvecQuery query, xvecVectorArray data)
    {
        auto& queryHandler =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecQueryObject>*>(query.p);

        if (queryHandler == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        auto& vectorArrayHandler =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecVectorArrayObject>*>(data.p);

        if (vectorArrayHandler == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        return queryHandler->setQueryVector(*vectorArrayHandler.shareDataPtr());
    };

    xvecStatus xvecGetQueryBuffer(xvecQuery query, xvecBuffer* data)
    {
        auto& queryHandler =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecQueryObject>*>(query.p);

        if (queryHandler == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        data->p = queryHandler->getQueryVectorPointer();
        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecGetQueryDimension(xvecQuery query, size_t* dim)
    {
        auto& queryHandler =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecQueryObject>*>(query.p);

        if (queryHandler == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        *dim = queryHandler->getDim();

        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecGetQueryIndexes(xvecQuery query, xvecBuffer* indexes)
    {
        auto& queryHandler =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecQueryObject>*>(query.p);

        if (queryHandler == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        xvecSharedPtr<metisx::pg_xvector::xvecBufferObject>* temp =
            new xvecSharedPtr<metisx::pg_xvector::xvecBufferObject>(
                *queryHandler->getQueryResultIndexPointer());

        indexes->p = temp->shareRawPtr();

        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecGetQueryScores(xvecQuery query, xvecBuffer* scores)
    {
        auto& queryHandler =
            *reinterpret_cast<xvecSharedPtr<metisx::pg_xvector::xvecQueryObject>*>(query.p);

        if (queryHandler == nullptr)
        {
            return XVEC_STATUS_INVALID_PTR;
        }

        xvecSharedPtr<metisx::pg_xvector::xvecBufferObject>* temp =
            new xvecSharedPtr<metisx::pg_xvector::xvecBufferObject>(
                *queryHandler->getQueryResultScorePointer());

        scores->p = temp->shareRawPtr();

        return XVEC_STATUS_SUCCESS;
    };

    xvecStatus xvecCalculateConsineSimilarity(xvecQuery* queries, const size_t queriesCount)
    {
        xvecStatus status = XVEC_STATUS_SUCCESS;

        for (size_t query = 0; query < queriesCount; query++)
        {
            auto& queryHandler =
                *reinterpret_cast<std::shared_ptr<metisx::pg_xvector::xvecQueryObject>*>(
                    queries[query].p);

            status = queryHandler->calculateCosineSimilarity();

            if (status != XVEC_STATUS_SUCCESS)
            {
                return status;
            }
        }

        return status;
    };

    xvecStatus xvecCalculateL2Distance([[maybe_unused]] xvecQuery* queries, [[maybe_unused]] const size_t queriesCount)
    {
        return XVEC_STATUS_SUCCESS;
    };
}