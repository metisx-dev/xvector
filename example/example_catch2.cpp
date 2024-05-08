#include <stdio.h>
#include <string.h>
#include <xvector/xvector.h>

#include "catch2/catch_all.hpp"

extern "C" int readVectors(const char* filename, float* vectors, size_t dimension, size_t vectorCount);

#define EXIT_ON_ERROR(status) exit_on_error((status), __FILE__, __LINE__)

static void exit_on_error(const xvecStatus status, const char* const file, const int line)
{
    if (status != XVEC_SUCCESS)
    {
        fprintf(stderr, "xvector error = %04d from file <%s>, line %d.\n", (status), file, line);
        exit(status);
    }
}

int testFunction()
{
    extern float queryVector0[];
    extern float queryVector1[];
    extern float queryVector2[];
    extern float queryVector3[];

    const size_t dimension = 3072;
    size_t vectorCount = 100000;
    xvecContext context;

    EXIT_ON_ERROR(xvecCreateContext(&context, NULL));

    // VectorArray Example

    xvecVectorArray vectorArray;
    EXIT_ON_ERROR(xvecCreateVectorArray(&vectorArray, context, dimension));

    EXIT_ON_ERROR(xvecSetVectorArrayCustomData(vectorArray, (void*)"EMBEDDING"));

    //float vectors[dimension * vectorCount];
    std::vector<float> vectors(dimension * vectorCount);

    if (readVectors("resources/100-3072.npy", vectors.data(), dimension, vectorCount) != 0)
    //if (readVectors("resources/100000-3072-a.npy", vectors.data(), dimension, vectorCount) != 0)
    {
       return 1;
    }
    vectorCount = 100000;
    
    xvecBuffer vectorBuf;
    EXIT_ON_ERROR(xvecCreateBuffer(&vectorBuf, context, vectorCount * dimension * sizeof(float)));

    EXIT_ON_ERROR(xvecCopyHostToBuffer(vectorBuf, vectors.data(), 0, vectorCount * dimension * sizeof(float)));

    uintptr_t* metadata = (uintptr_t*)malloc(vectorCount * sizeof(uintptr_t));

    for (size_t i = 0; i < vectorCount; i++)
    {
        metadata[i] = 0xAB000000ull | i;
    }

    EXIT_ON_ERROR(xvecSetVectorArrayBuffer(vectorArray, vectorBuf, metadata, vectorCount));

    delete vectors;
    xvecReleaseBuffer(vectorBuf);

    if (1)
    {
        printf("Basic Distance Calculation with Vector Array\n");

        const size_t targetCount = 1;

        xvecDistanceQuery query;
        EXIT_ON_ERROR(xvecCreateDistanceQuery(&query, context, XVEC_OP_DOT_PRODUCT, queryVector0, dimension));

        EXIT_ON_ERROR(xvecSetDistanceQueryTargets(query, XVEC_TARGET_VECTOR_ARRAY, &vectorArray, targetCount));

        EXIT_ON_ERROR(xvecExecuteQueries(&query, 1));

        for (size_t i = 0; i < targetCount; i++)
        {
            xvecDistanceResult result;
            EXIT_ON_ERROR(xvecGetDistanceQueryResult(query, i, &result));

            float* distances;
            EXIT_ON_ERROR(xvecGetDistanceResultValues(result, &distances));

            size_t length;
            EXIT_ON_ERROR(xvecGetDistanceResultLength(result, &length));

            const char* customData;
            EXIT_ON_ERROR(xvecGetVectorArrayCustomData(vectorArray, (void**)&customData));

            for (size_t j = 0; j < length; j++)
            {                  
                printf("[%zu] %s, %f\n", j, customData, distances[j]);
            }

            printf("\n");
            xvecReleaseDistanceResult(result);
        }

        xvecReleaseDistanceQuery(query);
    }

    if (0)
    {
        printf("Basic k-NN Search with Vector Array\n");

        const size_t targetCount = 1;
        const size_t k = 10;

        xvecKnnQuery query;
        EXIT_ON_ERROR(xvecCreateKnnQuery(&query, context, XVEC_OP_DOT_PRODUCT, queryVector0, dimension, k));

        EXIT_ON_ERROR(xvecSetKnnQueryTargets(query, XVEC_TARGET_VECTOR_ARRAY, &vectorArray, 1));

        EXIT_ON_ERROR(xvecExecuteQueries(&query, 1));

        xvecKnnResult result;
        EXIT_ON_ERROR(xvecGetKnnQueryResult(query, &result));

        xvecReleaseKnnQuery(query);

        float* scores;
        EXIT_ON_ERROR(xvecGetKnnResultScores(result, &scores));

        xvecIndex* indices;
        EXIT_ON_ERROR(xvecGetKnnResultIndices(result, &indices));

        xvecVectorArray* vectorArrays;
        EXIT_ON_ERROR(xvecGetKnnResultVectorArrays(result, &vectorArrays));

        uintptr_t* resultMetadata;
        EXIT_ON_ERROR(xvecGetKnnResultMetadata(result, &resultMetadata));

        printf("Metadata: %p\n", resultMetadata);

        const char* customData;
        EXIT_ON_ERROR(xvecGetVectorArrayCustomData(vectorArrays[0], (void**)&customData));

        for (size_t i = 0; i < k; i++)
        {
            printf("[%zu] %s, %d, %f, 0x%08X(%u)\n",
                   i,
                   customData,
                   indices[i],
                   scores[i],
                   (uint32_t)resultMetadata[i],
                   (uint32_t)(resultMetadata[i] & 0xFF000000));
        }
        printf("\n");

        xvecReleaseKnnResult(result);
    }

    if (0)
    {
        printf("Extended k-NN Search Example with 4 Queries and Target Vector Array\n");

        constexpr uint64_t queryCount = 4;
        const size_t targetCount = 1;
        const size_t k = 10;

        xvecKnnQuery* queries = new xvecKnnQuery[queryCount];
        EXIT_ON_ERROR(xvecCreateKnnQuery(&queries[0], context, XVEC_OP_DOT_PRODUCT, queryVector0, dimension, k));
        EXIT_ON_ERROR(xvecCreateKnnQuery(&queries[1], context, XVEC_OP_DOT_PRODUCT, queryVector1, dimension, k));
        EXIT_ON_ERROR(xvecCreateKnnQuery(&queries[2], context, XVEC_OP_DOT_PRODUCT, queryVector2, dimension, k));
        EXIT_ON_ERROR(xvecCreateKnnQuery(&queries[3], context, XVEC_OP_DOT_PRODUCT, queryVector3, dimension, k));

        for (uint64_t query = 0; query < queryCount; query++)
        {
            EXIT_ON_ERROR(xvecSetKnnQueryTargets(queries[query], XVEC_TARGET_VECTOR_ARRAY, &vectorArray, 1));
        }

        EXIT_ON_ERROR(xvecExecuteQueries(queries, queryCount));

        for (uint64_t query = 0; query < queryCount; query++)
        {
            xvecKnnResult result;
            EXIT_ON_ERROR(xvecGetKnnQueryResult(queries[query], &result));     

            xvecReleaseKnnQuery(queries[query]);

            float* scores;
            EXIT_ON_ERROR(xvecGetKnnResultScores(result, &scores));

            xvecIndex* indices;
            EXIT_ON_ERROR(xvecGetKnnResultIndices(result, &indices));

            xvecVectorArray* vectorArrays;
            EXIT_ON_ERROR(xvecGetKnnResultVectorArrays(result, &vectorArrays));

            uintptr_t* resultMetadata;
            EXIT_ON_ERROR(xvecGetKnnResultMetadata(result, &resultMetadata));

            printf("Metadata: %p\n", resultMetadata);

            const char* customData;
            EXIT_ON_ERROR(xvecGetVectorArrayCustomData(vectorArrays[0], (void**)&customData));

            for (size_t i = 0; i < k; i++)
            {
                printf("[%zu] %s, %d, %f, 0x%08X(%u)\n",
                    i,
                    customData,
                    indices[i],
                    scores[i],
                    (uint32_t)resultMetadata[i],
                    (uint32_t)(resultMetadata[i] & 0xFF000000));
            }
            printf("\n");

            xvecReleaseKnnResult(result); 
        }        
    }

    if (0)
    {
        printf("Basic Distance Calculation with Vector Array and Filter\n");

        const size_t targetCount = 1;
        xvecDistanceQuery query;
        EXIT_ON_ERROR(xvecCreateDistanceQuery(&query, context, XVEC_OP_DOT_PRODUCT, queryVector0, dimension));

        EXIT_ON_ERROR(xvecSetDistanceQueryTargets(query, XVEC_TARGET_VECTOR_ARRAY, &vectorArray, 1));

        size_t filterSize = (vectorCount + 7) / 8;

        xvecBuffer bitmapBuf;
        EXIT_ON_ERROR(xvecCreateBuffer(&bitmapBuf, context, filterSize));

        uint8_t bitmap[filterSize];
        memset(bitmap, 0, filterSize);

        // Only even indices are calculated
        size_t validCount = 0;
        for (size_t i = 0; i < vectorCount; i += 2)
        {
            bitmap[i / 8] |= 1 << (i % 8);
            ++validCount;
        }

        EXIT_ON_ERROR(xvecCopyHostToBuffer(bitmapBuf, bitmap, 0, filterSize));

        xvecFilter filter;
        EXIT_ON_ERROR(xvecCreateFilter(&filter, context));

        EXIT_ON_ERROR(xvecSetFilterBuffer(filter, bitmapBuf, validCount));

        xvecReleaseBuffer(bitmapBuf);

        EXIT_ON_ERROR(xvecSetDistanceQueryFilters(query, &filter, 1));

        xvecReleaseFilter(filter);

        EXIT_ON_ERROR(xvecExecuteQueries(&query, 1));

        for (size_t i = 0; i < targetCount; i++)
        {
            xvecDistanceResult result;
            EXIT_ON_ERROR(xvecGetDistanceQueryResult(query, i, &result));

            float* distances;
            EXIT_ON_ERROR(xvecGetDistanceResultValues(result, &distances));

            size_t length;
            EXIT_ON_ERROR(xvecGetDistanceResultLength(result, &length));

            const char* customData;
            EXIT_ON_ERROR(xvecGetVectorArrayCustomData(vectorArray, (void**)&customData));

            for (size_t j = 0; j < length; j++)
            {
                printf("[%zu] %s, %f\n", j, customData, distances[j]);
            }

            printf("\n");
            xvecReleaseDistanceResult(result);
        }

        xvecReleaseDistanceQuery(query);
    }

    if (0)
    {
        printf("Basic k-NN Search with Vector Array and Filter\n");

        const size_t k = 10;
        xvecKnnQuery query;
        EXIT_ON_ERROR(xvecCreateKnnQuery(&query, context, XVEC_OP_DOT_PRODUCT, queryVector0, dimension, k));

        EXIT_ON_ERROR(xvecSetKnnQueryTargets(query, XVEC_TARGET_VECTOR_ARRAY, &vectorArray, 1));

        size_t filterSize = (vectorCount + 7) / 8;

        xvecBuffer bitmapBuf;
        EXIT_ON_ERROR(xvecCreateBuffer(&bitmapBuf, context, filterSize));

        uint8_t bitmap[filterSize];
        memset(bitmap, 0, filterSize);

        // Only even indices are calculated
        size_t validCount = 0;
        for (size_t i = 0; i < vectorCount; i += 2)
        {
            bitmap[i / 8] |= 1 << (i % 8);
            ++validCount;
        }

        EXIT_ON_ERROR(xvecCopyHostToBuffer(bitmapBuf, bitmap, 0, filterSize));

        xvecFilter filter;
        EXIT_ON_ERROR(xvecCreateFilter(&filter, context));

        EXIT_ON_ERROR(xvecSetFilterBuffer(filter, bitmapBuf, validCount));

        xvecReleaseBuffer(bitmapBuf);

        EXIT_ON_ERROR(xvecSetKnnQueryFilters(query, &filter, 1));

        xvecReleaseFilter(filter);

        EXIT_ON_ERROR(xvecExecuteQueries(&query, 1));

        xvecKnnResult result;
        EXIT_ON_ERROR(xvecGetKnnQueryResult(query, &result));

        xvecReleaseKnnQuery(query);

        float* scores;
        EXIT_ON_ERROR(xvecGetKnnResultScores(result, &scores));

        xvecIndex* indices;
        EXIT_ON_ERROR(xvecGetKnnResultIndices(result, &indices));

        xvecVectorArray* vectorArrays;
        EXIT_ON_ERROR(xvecGetKnnResultVectorArrays(result, &vectorArrays));

        uintptr_t* resultMetadata;
        EXIT_ON_ERROR(xvecGetKnnResultMetadata(result, &resultMetadata));

        const char* customData;
        EXIT_ON_ERROR(xvecGetVectorArrayCustomData(vectorArrays[0], (void**)&customData));

        for (size_t i = 0; i < k; i++)
        {
            printf("[%zu] %s, %d, %f, 0x%08X(%u)\n",
                   i,
                   customData,
                   indices[i],
                   scores[i],
                   (uint32_t)resultMetadata[i],
                   (uint32_t)(resultMetadata[i] & 0xFF000000));
        }
        printf("\n");

        xvecReleaseKnnResult(result);
    }

    // Index Array Example

    xvecIndexArray indexArrays[4];

    for (int i = 0; i < 4; i++)
    {
        EXIT_ON_ERROR(xvecCreateIndexArray(&indexArrays[i], vectorArray));

        xvecBuffer indexBuf;
        EXIT_ON_ERROR(xvecCreateBuffer(&indexBuf, context, 25 * sizeof(xvecIndex)));

        xvecIndex indices[25];
        for (int j = 0; j < 25; ++j)
        {
            indices[j] = j * 4 + i;
        }

        EXIT_ON_ERROR(xvecCopyHostToBuffer(indexBuf, indices, 0, sizeof(indices)));

        EXIT_ON_ERROR(xvecSetIndexArrayBuffer(indexArrays[i], indexBuf, sizeof(indices) / sizeof(xvecIndex)));

        xvecReleaseBuffer(indexBuf);
    }

    if (0)
    {
        printf("Basic Distance Calculation with Index Array\n");

        xvecDistanceQuery query;
        EXIT_ON_ERROR(xvecCreateDistanceQuery(&query, context, XVEC_OP_DOT_PRODUCT, queryVector0, dimension));

        xvecIndexArray targets[] = {indexArrays[1], indexArrays[3]};
        const size_t targetCount = sizeof(targets) / sizeof(targets[0]);
        EXIT_ON_ERROR(xvecSetDistanceQueryTargets(query, XVEC_TARGET_INDEX_ARRAY, targets, targetCount));

        EXIT_ON_ERROR(xvecExecuteQueries(&query, 1));

        for (size_t i = 0; i < targetCount; i++)
        {
            xvecDistanceResult result;
            EXIT_ON_ERROR(xvecGetDistanceQueryResult(query, i, &result));

            float* distances;
            EXIT_ON_ERROR(xvecGetDistanceResultValues(result, &distances));

            size_t length;
            EXIT_ON_ERROR(xvecGetDistanceResultLength(result, &length));

            const char* customData;
            EXIT_ON_ERROR(xvecGetVectorArrayCustomData(vectorArray, (void**)&customData));

            for (size_t j = 0; j < length; j++)
            {
                printf("[%zu] %s, %f\n", j, customData, distances[j]);
            }

            printf("\n");
            xvecReleaseDistanceResult(result);
        }

        xvecReleaseDistanceQuery(query);
    }

    if (0)
    {
        printf("Basic k-NN Search with Index Array\n");

        const size_t k = 10;

        xvecKnnQuery queries[2];
        const size_t queryCount = sizeof(queries) / sizeof(queries[0]);

        for (size_t q = 0; q < queryCount; q++)
        {
            EXIT_ON_ERROR(xvecCreateKnnQuery(&queries[q], context, XVEC_OP_DOT_PRODUCT, queryVector0, dimension, k));

            if (q % 2 == 0)
            {
                xvecIndexArray targets[] = {indexArrays[1], indexArrays[2]};
                EXIT_ON_ERROR(xvecSetKnnQueryTargets(
                    queries[q], XVEC_TARGET_INDEX_ARRAY, targets, sizeof(targets) / sizeof(targets[0])));
            }
            else
            {
                xvecIndexArray targets[] = {indexArrays[2], indexArrays[3]};
                EXIT_ON_ERROR(xvecSetKnnQueryTargets(
                    queries[q], XVEC_TARGET_INDEX_ARRAY, targets, sizeof(targets) / sizeof(targets[0])));
            }
        }

        EXIT_ON_ERROR(xvecExecuteQueries(queries, queryCount));

        for (size_t q = 0; q < queryCount; q++)
        {
            xvecKnnResult result;
            EXIT_ON_ERROR(xvecGetKnnQueryResult(queries[q], &result));

            xvecReleaseKnnQuery(queries[q]);

            float* scores;
            EXIT_ON_ERROR(xvecGetKnnResultScores(result, &scores));

            xvecIndex* indices;
            EXIT_ON_ERROR(xvecGetKnnResultIndices(result, &indices));

            xvecVectorArray* vectorArrays;
            EXIT_ON_ERROR(xvecGetKnnResultVectorArrays(result, &vectorArrays));

            uintptr_t* resultMetadata;
            EXIT_ON_ERROR(xvecGetKnnResultMetadata(result, &resultMetadata));

            const char* customData;
            EXIT_ON_ERROR(xvecGetVectorArrayCustomData(vectorArrays[0], (void**)&customData));

            for (size_t i = 0; i < k; i++)
            {
                printf("[%zu] %s, %d, %f, 0x%08X(%u)\n",
                       i,
                       customData,
                       indices[i],
                       scores[i],
                       (uint32_t)resultMetadata[i],
                       (uint32_t)(resultMetadata[i] & 0xFF000000));
            }
            printf("\n");

            xvecReleaseKnnResult(result);
        }
    }

    xvecFilter filters[2];
    const size_t filterCount = sizeof(filters) / sizeof(filters[0]);

    for (int i = 0; i < 2; i++)
    {
        size_t filterSize = (25 + 7) / 8;

        xvecBuffer bitmapBuf;

        EXIT_ON_ERROR(xvecCreateBuffer(&bitmapBuf, context, filterSize));

        uint8_t bitmap[filterSize];
        memset(bitmap, 0, filterSize);

        size_t validCount = 0;
        if (i == 0)
        {
            for (size_t j = 0; j < 13; ++j)
            {
                bitmap[j / 8] |= 1 << (j % 8);
                ++validCount;
            }
        }
        else
        {
            for (size_t j = 13; j < 25; ++j)
            {
                bitmap[j / 8] |= 1 << (j % 8);
                ++validCount;
            }
        }

        EXIT_ON_ERROR(xvecCopyHostToBuffer(bitmapBuf, bitmap, 0, filterSize));

        EXIT_ON_ERROR(xvecCreateFilter(&filters[i], context));

        EXIT_ON_ERROR(xvecSetFilterBuffer(filters[i], bitmapBuf, validCount));

        EXIT_ON_ERROR(xvecReleaseBuffer(bitmapBuf));
    }

    if (0)
    {
        printf("Basic Distance Calculation with Index Array and Filter\n");

        xvecDistanceQuery query;
        EXIT_ON_ERROR(xvecCreateDistanceQuery(&query, context, XVEC_OP_DOT_PRODUCT, queryVector0, dimension));

        xvecIndexArray targets[] = {indexArrays[1], indexArrays[3]};
        const size_t targetCount = sizeof(targets) / sizeof(targets[0]);

        EXIT_ON_ERROR(xvecSetDistanceQueryTargets(query, XVEC_TARGET_INDEX_ARRAY, targets, targetCount));

        EXIT_ON_ERROR(xvecSetDistanceQueryFilters(query, filters, filterCount));

        EXIT_ON_ERROR(xvecExecuteQueries(&query, 1));

        for (size_t i = 0; i < targetCount; i++)
        {
            xvecDistanceResult result;
            EXIT_ON_ERROR(xvecGetDistanceQueryResult(query, i, &result));

            float* distances;
            EXIT_ON_ERROR(xvecGetDistanceResultValues(result, &distances));

            size_t length;
            EXIT_ON_ERROR(xvecGetDistanceResultLength(result, &length));

            const char* customData;
            EXIT_ON_ERROR(xvecGetVectorArrayCustomData(vectorArray, (void**)&customData));

            for (size_t j = 0; j < length; j++)
            {
                printf("[%zu] %s, %f\n", j, customData, distances[j]);
            }

            printf("\n");
            xvecReleaseDistanceResult(result);
        }

        xvecReleaseDistanceQuery(query);
    }

    if (0)
    {
        printf("Basic k-NN Search with Index Array and Filter\n");

        const size_t k = 10;
        xvecKnnQuery query;
        EXIT_ON_ERROR(xvecCreateKnnQuery(&query, context, XVEC_OP_DOT_PRODUCT, queryVector0, dimension, k));

        xvecIndexArray targets[] = {indexArrays[1], indexArrays[3]};
        const size_t targetCount = sizeof(targets) / sizeof(targets[0]);

        EXIT_ON_ERROR(xvecSetKnnQueryTargets(query, XVEC_TARGET_INDEX_ARRAY, targets, targetCount));

        EXIT_ON_ERROR(xvecSetKnnQueryFilters(query, filters, filterCount));

        EXIT_ON_ERROR(xvecExecuteQueries(&query, 1));

        xvecKnnResult result;
        EXIT_ON_ERROR(xvecGetKnnQueryResult(query, &result));

        xvecReleaseKnnQuery(query);

        float* scores;
        EXIT_ON_ERROR(xvecGetKnnResultScores(result, &scores));

        xvecIndex* indices;
        EXIT_ON_ERROR(xvecGetKnnResultIndices(result, &indices));

        xvecVectorArray* vectorArrays;
        EXIT_ON_ERROR(xvecGetKnnResultVectorArrays(result, &vectorArrays));

        uintptr_t* resultMetadata;
        EXIT_ON_ERROR(xvecGetKnnResultMetadata(result, &resultMetadata));

        const char* customData;
        EXIT_ON_ERROR(xvecGetVectorArrayCustomData(vectorArrays[0], (void**)&customData));

        for (size_t i = 0; i < k; i++)
        {
            printf("[%zu] %s, %d, %f, 0x%08X(%u)\n",
                   i,
                   customData,
                   indices[i],
                   scores[i],
                   (uint32_t)resultMetadata[i],
                   (uint32_t)(resultMetadata[i] & 0xFF000000));
        }
        printf("\n");

        xvecReleaseKnnResult(result);
    }

    free(metadata);

    xvecReleaseVectorArray(vectorArray);
    xvecDestroyContext(context);

    return 0;
}

TEST_CASE("test on xvector C API")
{
    testFunction();
}
