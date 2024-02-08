#include <stdio.h>
#include <string.h>
#include <xvector/xvector.h>

int readVectors(const char* filename, float* vectors, size_t dimension, size_t vectorCount);

#define EXIT_ON_ERROR(status) exit_on_error((status), __FILE__, __LINE__)

static void exit_on_error(const xvecStatus status, const char* const file, const int line)
{
    if (status != XVEC_SUCCESS)
    {
        fprintf(stderr, "xvector error = %04d from file <%s>, line %d.\n", (status), file, line);
        exit(status);
    }
}

int main()
{
    extern float queryVector[];

    const size_t dimension = 3072;
    const size_t vectorCount = 100;
    xvecContext context;

    EXIT_ON_ERROR(xvecCreateContext(&context));

    // VectorArray Example

    xvecVectorArray vectorArray;
    EXIT_ON_ERROR(xvecCreateVectorArray(&vectorArray, context, dimension));

    EXIT_ON_ERROR(xvecSetVectorArrayCustomData(vectorArray, (void*)"EMBEDDING"));

    float vectors[dimension * vectorCount];
    if (readVectors("resources/100-3072.npy", vectors, dimension, vectorCount) != 0)
    {
        return 1;
    }

    xvecBuffer vectorBuf;
    EXIT_ON_ERROR(xvecCreateBuffer(&vectorBuf, context, vectorCount * dimension * sizeof(float)));

    EXIT_ON_ERROR(xvecCopyToBuffer(vectorBuf, vectors, 0, vectorCount * dimension * sizeof(float)));

    EXIT_ON_ERROR(xvecSetVectorArrayVectors(vectorArray, vectorBuf, vectorCount));

    xvecReleaseBuffer(vectorBuf);

    {
        printf("Basic k-NN Search with Vector Array\n");

        const size_t k = 10;
        xvecKnnQuery query;
        EXIT_ON_ERROR(xvecCreateKnnQuery(&query, context, XVEC_KNN_DOT_PRODUCT, queryVector, dimension, k));

        EXIT_ON_ERROR(xvecSetKnnQueryTargets(query, XVEC_KNN_TARGET_VECTOR_ARRAY, &vectorArray, 1));

        EXIT_ON_ERROR(xvecExecuteQuery(&query, 1));

        xvecKnnResult result;
        EXIT_ON_ERROR(xvecGetKnnQueryResult(query, &result));

        xvecReleaseKnnQuery(query);

        float* scores;
        EXIT_ON_ERROR(xvecGetKnnResultScores(result, &scores));

        xvecIndex* indices;
        EXIT_ON_ERROR(xvecGetKnnResultIndices(result, &indices));

        xvecVectorArray* vectorArrays;
        EXIT_ON_ERROR(xvecGetKnnResultVectorArrays(result, &vectorArrays));

        const char* customData;
        EXIT_ON_ERROR(xvecGetVectorArrayCustomData(vectorArrays[0], (void**)&customData));

        for (size_t i = 0; i < k; i++)
        {
            printf("%s, %d, %f\n", customData, indices[i], scores[i]);
        }
        printf("\n");

        xvecReleaseKnnResult(result);
    }

    {
        printf("Basic k-NN Search with Vector Array and Filter\n");

        const size_t k = 10;
        xvecKnnQuery query;
        EXIT_ON_ERROR(xvecCreateKnnQuery(&query, context, XVEC_KNN_DOT_PRODUCT, queryVector, dimension, k));

        EXIT_ON_ERROR(xvecSetKnnQueryTargets(query, XVEC_KNN_TARGET_VECTOR_ARRAY, &vectorArray, 1));

        size_t filterSize = (vectorCount + 7) / 8;

        xvecBuffer filterBuf;
        EXIT_ON_ERROR(xvecCreateBuffer(&filterBuf, context, filterSize));

        uint8_t filter[filterSize];
        memset(filter, 0, filterSize);

        // Only even indices are calculated
        for (size_t i = 0; i < vectorCount; i += 2)
        {
            filter[i / 8] |= 1 << (i % 8);
        }

        EXIT_ON_ERROR(xvecCopyToBuffer(filterBuf, filter, 0, filterSize));

        EXIT_ON_ERROR(xvecSetKnnQueryFilters(query, &filterBuf, 1));

        xvecReleaseBuffer(filterBuf);

        EXIT_ON_ERROR(xvecExecuteQuery(&query, 1));

        xvecKnnResult result;
        EXIT_ON_ERROR(xvecGetKnnQueryResult(query, &result));

        xvecReleaseKnnQuery(query);

        float* scores;
        EXIT_ON_ERROR(xvecGetKnnResultScores(result, &scores));

        xvecIndex* indices;
        EXIT_ON_ERROR(xvecGetKnnResultIndices(result, &indices));

        xvecVectorArray* vectorArrays;
        EXIT_ON_ERROR(xvecGetKnnResultVectorArrays(result, &vectorArrays));

        const char* customData;
        EXIT_ON_ERROR(xvecGetVectorArrayCustomData(vectorArrays[0], (void**)&customData));

        for (size_t i = 0; i < k; i++)
        {
            printf("%s, %d, %f\n", customData, indices[i], scores[i]);
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

        EXIT_ON_ERROR(xvecCopyToBuffer(indexBuf, indices, 0, sizeof(indices)));

        EXIT_ON_ERROR(xvecSetIndexArrayIndices(indexArrays[i], indexBuf, sizeof(indices) / sizeof(xvecIndex)));

        xvecReleaseBuffer(indexBuf);
    }

    {
        printf("Basic k-NN Search with Index Array\n");

        const size_t k = 10;
        xvecKnnQuery query;
        EXIT_ON_ERROR(xvecCreateKnnQuery(&query, context, XVEC_KNN_DOT_PRODUCT, queryVector, dimension, k));

        xvecIndexArray targets[] = {indexArrays[1], indexArrays[3]};
        EXIT_ON_ERROR(
            xvecSetKnnQueryTargets(query, XVEC_KNN_TARGET_INDEX_ARRAY, targets, sizeof(targets) / sizeof(targets[0])));

        EXIT_ON_ERROR(xvecExecuteQuery(&query, 1));

        xvecKnnResult result;
        EXIT_ON_ERROR(xvecGetKnnQueryResult(query, &result));

        xvecReleaseKnnQuery(query);

        float* scores;
        EXIT_ON_ERROR(xvecGetKnnResultScores(result, &scores));

        xvecIndex* indices;
        EXIT_ON_ERROR(xvecGetKnnResultIndices(result, &indices));

        xvecVectorArray* vectorArrays;
        EXIT_ON_ERROR(xvecGetKnnResultVectorArrays(result, &vectorArrays));

        const char* customData;
        EXIT_ON_ERROR(xvecGetVectorArrayCustomData(vectorArrays[0], (void**)&customData));

        for (size_t i = 0; i < k; i++)
        {
            printf("%s, %d, %f\n", customData, indices[i], scores[i]);
        }
        printf("\n");

        xvecReleaseKnnResult(result);
    }

    xvecBuffer filters[2];

    for (int i = 0; i < 2; i++)
    {
        size_t filterSize = (25 + 7) / 8;

        EXIT_ON_ERROR(xvecCreateBuffer(&filters[i], context, filterSize));

        uint8_t filter[filterSize];
        memset(filter, 0, filterSize);

        if (i == 0)
        {
            for (size_t j = 0; j < 13; ++j)
                filter[j / 8] |= 1 << (j % 8);
        }
        else
        {
            for (size_t j = 13; j < 25; ++j)
                filter[j / 8] |= 1 << (j % 8);
        }

        EXIT_ON_ERROR(xvecCopyToBuffer(filters[i], filter, 0, filterSize));
    }

    {
        printf("Basic k-NN Search with Index Array and Filter\n");

        const size_t k = 10;
        xvecKnnQuery query;
        EXIT_ON_ERROR(xvecCreateKnnQuery(&query, context, XVEC_KNN_DOT_PRODUCT, queryVector, dimension, k));

        xvecIndexArray targets[] = {indexArrays[1], indexArrays[3]};
        EXIT_ON_ERROR(
            xvecSetKnnQueryTargets(query, XVEC_KNN_TARGET_INDEX_ARRAY, targets, sizeof(targets) / sizeof(targets[0])));

        EXIT_ON_ERROR(xvecSetKnnQueryFilters(query, filters, sizeof(filters) / sizeof(filters[0])));

        EXIT_ON_ERROR(xvecExecuteQuery(&query, 1));

        xvecKnnResult result;
        EXIT_ON_ERROR(xvecGetKnnQueryResult(query, &result));

        xvecReleaseKnnQuery(query);

        float* scores;
        EXIT_ON_ERROR(xvecGetKnnResultScores(result, &scores));

        xvecIndex* indices;
        EXIT_ON_ERROR(xvecGetKnnResultIndices(result, &indices));

        xvecVectorArray* vectorArrays;
        EXIT_ON_ERROR(xvecGetKnnResultVectorArrays(result, &vectorArrays));

        const char* customData;
        EXIT_ON_ERROR(xvecGetVectorArrayCustomData(vectorArrays[0], (void**)&customData));

        for (size_t i = 0; i < k; i++)
        {
            printf("%s, %d, %f\n", customData, indices[i], scores[i]);
        }
        printf("\n");

        xvecReleaseKnnResult(result);
    }

    xvecReleaseVectorArray(vectorArray);
    xvecDestroyContext(context);

    return 0;
}
