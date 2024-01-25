#include "xvector.h"

#include <gtest/gtest.h>

#include <algorithm>

class MuXvectorTester : public ::testing::Test
{
protected:
    MuXvectorTester()
    {
    }

    virtual ~MuXvectorTester()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

protected:
};

TEST_F(MuXvectorTester, CREATE_BUFFER)
{
    constexpr size_t dim = 1536;
    constexpr size_t tableSize = 100000;

    xvecBuffer vectorEmbeddingBuffer;
    vectorEmbeddingBuffer.p = nullptr;

    xvecCreateBuffer(&vectorEmbeddingBuffer, dim * tableSize * sizeof(float));

    float* vectorEmbeddingBufferPtr = nullptr;
    xvecBufferGetPointer(vectorEmbeddingBuffer, (void**)&vectorEmbeddingBufferPtr);

    for (uint64_t N = 0; N < tableSize; N++)
    {
        for (uint64_t D = 0; D < dim; D++)
        {
            vectorEmbeddingBufferPtr[N * dim + D] = D * 0.01 + N * 0.0001;
        }
    }

    float* vectorEmbeddingBufferPtr2 = nullptr;
    xvecBufferGetPointer(vectorEmbeddingBuffer, (void**)&vectorEmbeddingBufferPtr2);

    EXPECT_EQ(vectorEmbeddingBufferPtr[8000 * dim + 40],
              vectorEmbeddingBufferPtr2[8000 * dim + 40]);
    printf("res %f \n", vectorEmbeddingBufferPtr[8000 * dim + 40]);
    xvecReleaseBuffer(vectorEmbeddingBuffer);
}

TEST_F(MuXvectorTester, CALC_COSINE_SIMILARITY_FULL_SCAN)
{
    constexpr size_t dim = 10;
    constexpr size_t tableSize = 20;
    constexpr size_t k = 10;
    std::vector<float> ansSrc;
    std::vector<float> ans(tableSize);

    xvecBuffer vectorEmbeddingBuffer;
    xvecCreateBuffer(&vectorEmbeddingBuffer, dim * tableSize * sizeof(float));

    float* vectorEmbeddingBufferPtr = nullptr;

    xvecBufferGetPointer(vectorEmbeddingBuffer, (void**)&vectorEmbeddingBufferPtr);

    for (uint64_t N = 0; N < tableSize; N++)
    {
        for (int64_t D = 0; D < dim; D++)
        {
            vectorEmbeddingBufferPtr[N * dim + D] = D * 0.01 + N * 0.0001;
            ansSrc.push_back(D * 0.01 + N * 0.0001);
        }
    }

    xvecVectorArray vectorEmbeddingArray;
    xvecCreateVectorArray(&vectorEmbeddingArray, XVEC_FLOAT32, dim);
    xvecVectorArraySetBuffer(vectorEmbeddingArray, vectorEmbeddingBuffer, tableSize);

    xvecBuffer queryBuffer;
    xvecCreateBuffer(&queryBuffer, dim * sizeof(float));
    float* queryBufferPtr = nullptr;
    xvecBufferGetPointer(queryBuffer, (void**)&queryBufferPtr);
    for (uint64_t D = 0; D < dim; D++)
    {
        queryBufferPtr[D] = (32 * 0.1);
    }

    for (uint64_t table = 0; table < tableSize; table++)
    {
        ans[table] = 0;
        for (uint64_t D = 0; D < dim; D++)
        {
            ans[table] += (queryBufferPtr[D] * ansSrc[table * dim + D]);
        }
    }
    std::sort(ans.begin(), ans.end(), std::greater<float>());

    xvecQuery query;
    xvecCreateQuery(&query, queryBuffer, dim);
    xvecSetQueryTopK(query, k);
    xvecSetQueryTarget(query, vectorEmbeddingArray);

    xvecCalculateConsineSimilarity(&query, 1);

    xvecBuffer resultIndexBuffer;
    xvecBuffer resultScoreBuffer;

    xvecGetQueryIndexes(query, &resultIndexBuffer);
    xvecGetQueryScores(query, &resultScoreBuffer);

    uint32_t* resultIndexBufferPtr = nullptr;
    float* resultScoreBufferPtr = nullptr;

    xvecBufferGetPointer(resultIndexBuffer, (void**)&resultIndexBufferPtr);
    xvecBufferGetPointer(resultScoreBuffer, (void**)&resultScoreBufferPtr);

    printf("query result \n");
    for (size_t idx = 0; idx < k; idx++)
    {
        printf("rank: %ld, index: %d, score: %f, score answer: %f \n",
               idx,
               resultIndexBufferPtr[idx],
               resultScoreBufferPtr[idx],
               ans[idx]);
    }
    printf("print done\n");

    xvecReleaseBuffer(resultIndexBuffer);
    xvecReleaseBuffer(resultScoreBuffer);

    xvecReleaseQuery(query);
    xvecReleaseVectorArray(vectorEmbeddingArray);
    xvecReleaseBuffer(vectorEmbeddingBuffer);
}

TEST_F(MuXvectorTester, CALC_COSINE_SIMILARITY_INDIRECT)
{
    constexpr size_t dim = 10;
    constexpr size_t tableSize = 20;
    constexpr size_t indirectTableCount = 2;
    constexpr size_t indirectSize = 6;
    constexpr size_t k = 10;
    std::vector<float> ansSrc;
    std::vector<float> ans;

    xvecBuffer vectorEmbeddingBuffer;
    xvecCreateBuffer(&vectorEmbeddingBuffer, dim * tableSize * sizeof(float));

    float* vectorEmbeddingBufferPtr = nullptr;

    xvecBufferGetPointer(vectorEmbeddingBuffer, (void**)&vectorEmbeddingBufferPtr);

    for (uint64_t N = 0; N < tableSize; N++)
    {
        for (int64_t D = 0; D < dim; D++)
        {
            vectorEmbeddingBufferPtr[N * dim + D] = D * 0.01 + N * 0.0001;
            ansSrc.push_back(D * 0.01 + N * 0.0001);
        }
    }

    xvecVectorArray vectorEmbeddingArray;
    xvecCreateVectorArray(&vectorEmbeddingArray, XVEC_FLOAT32, dim);
    xvecVectorArraySetBuffer(vectorEmbeddingArray, vectorEmbeddingBuffer, tableSize);

    xvecBuffer indirectTable1;
    xvecCreateBuffer(&indirectTable1, indirectSize * sizeof(uint32_t));
    uint32_t* indirectArrayPtr1 = nullptr;
    xvecBufferGetPointer(indirectTable1, (void**)&indirectArrayPtr1);

    indirectArrayPtr1[0] = 1;
    indirectArrayPtr1[1] = 3;
    indirectArrayPtr1[2] = 5;
    indirectArrayPtr1[3] = 7;
    indirectArrayPtr1[4] = 9;
    indirectArrayPtr1[5] = 11;

    xvecIndirectArray indirectArray1;
    xvecCreateIndirectArray(&indirectArray1, vectorEmbeddingArray);
    xvecSetIndirectArrayBuffer(indirectArray1, indirectTable1, indirectSize);

    xvecBuffer indirectTable2;
    xvecCreateBuffer(&indirectTable2, indirectSize * sizeof(uint32_t));
    uint32_t* indirectArrayPtr2 = nullptr;
    xvecBufferGetPointer(indirectTable2, (void**)&indirectArrayPtr2);

    indirectArrayPtr2[0] = 12;
    indirectArrayPtr2[1] = 13;
    indirectArrayPtr2[2] = 14;
    indirectArrayPtr2[3] = 15;
    indirectArrayPtr2[4] = 16;
    indirectArrayPtr2[5] = 17;

    xvecIndirectArray indirectArray2;
    xvecCreateIndirectArray(&indirectArray2, vectorEmbeddingArray);
    xvecSetIndirectArrayBuffer(indirectArray2, indirectTable2, indirectSize);

    xvecBuffer queryBuffer;
    xvecCreateBuffer(&queryBuffer, dim * sizeof(float));
    float* queryBufferPtr = nullptr;
    xvecBufferGetPointer(queryBuffer, (void**)&queryBufferPtr);
    for (uint64_t D = 0; D < dim; D++)
    {
        queryBufferPtr[D] = (32 * 0.1);
    }

    for (uint64_t indirectIdx = 0; indirectIdx < indirectSize; indirectIdx++)
    {
        uint32_t targetVector = indirectArrayPtr1[indirectIdx];
        float dotRes = 0;
        for (uint64_t D = 0; D < dim; D++)
        {
            dotRes += (queryBufferPtr[D] * ansSrc[targetVector * dim + D]);
        }
        ans.push_back(dotRes);
    }
    for (uint64_t indirectIdx = 0; indirectIdx < indirectSize; indirectIdx++)
    {
        uint32_t targetVector = indirectArrayPtr2[indirectIdx];
        float dotRes = 0;
        for (uint64_t D = 0; D < dim; D++)
        {
            dotRes += (queryBufferPtr[D] * ansSrc[targetVector * dim + D]);
        }
        ans.push_back(dotRes);
    }

    std::sort(ans.begin(), ans.end(), std::greater<float>());

    xvecQuery query;
    xvecCreateQuery(&query, queryBuffer, dim);
    xvecSetQueryTopK(query, k);
    xvecSetQueryIndirect(query, indirectArray1, indirectTableCount);
    xvecSetQueryIndirect(query, indirectArray2, indirectTableCount);

    xvecCalculateConsineSimilarity(&query, 1);

    xvecBuffer resultIndexBuffer;
    xvecBuffer resultScoreBuffer;

    xvecGetQueryIndexes(query, &resultIndexBuffer);
    xvecGetQueryScores(query, &resultScoreBuffer);

    uint32_t* resultIndexBufferPtr = nullptr;
    float* resultScoreBufferPtr = nullptr;

    xvecBufferGetPointer(resultIndexBuffer, (void**)&resultIndexBufferPtr);
    xvecBufferGetPointer(resultScoreBuffer, (void**)&resultScoreBufferPtr);

    printf("query result \n");
    for (size_t idx = 0; idx < k; idx++)
    {
        printf("rank: %ld, index: %d, score: %f, score answer: %f \n",
               idx,
               resultIndexBufferPtr[idx],
               resultScoreBufferPtr[idx],
               ans[idx]);
    }
    printf("print done\n");

    xvecReleaseBuffer(resultIndexBuffer);
    xvecReleaseBuffer(resultScoreBuffer);

    xvecReleaseQuery(query);
    xvecReleaseVectorArray(vectorEmbeddingArray);
    xvecReleaseBuffer(vectorEmbeddingBuffer);
}