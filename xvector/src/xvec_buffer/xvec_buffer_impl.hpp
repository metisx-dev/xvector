#pragma once

#include <stdint.h>

#include <memory>
#include <vector>

#include "xvec_buffer_template.hpp"

namespace metisx
{
namespace pg_xvector
{

class xvecBufferObject : public bufferTemplate
{
public:
    xvecBufferObject();
    xvecBufferObject(xvecBufferObject& src);
    ~xvecBufferObject() noexcept;

    virtual void* getRawPointer() override final;
    virtual xvecStatus reserveMemory(const size_t& bytes) override;
    virtual xvecStatus clear() noexcept override final;
    virtual size_t getByteSize() const override final;
    virtual xvecStatus setMemory(bufferTemplate* buffer) override final;

protected:
    std::shared_ptr<char[]> getSharedPointer();
    xvecStatus setSharedPointer(std::shared_ptr<char[]>&);
    xvecStatus setBufferFrom(xvecBufferObject* src);

protected:
    std::shared_ptr<char[]> data_;
};

class xvecVectorArrayObject : public xvecBufferObject
{
public:
    xvecVectorArrayObject(const size_t& dim, const uint32_t& type);

    virtual xvecStatus reserveMemory(const size_t& count) override final;
    size_t getSize() const;

    void setDim(const size_t& dim)
    {
        dim_ = dim;
    }

    void setType(const uint32_t& type)
    {
        type_ = type;
    }

    uint32_t getDim() const
    {
        return dim_;
    }

protected:
    uint32_t type_;
    uint32_t dim_ = 0;
};

class xvecIndirectArrayObject : public xvecBufferObject
{
public:
    xvecIndirectArrayObject(xvecVectorArrayObject* targetVectorArray)
        : targetVectorArray_(targetVectorArray)
    {
    }

    virtual xvecStatus reserveMemory(const size_t& bytes) override final;
    size_t getSize() const;
    xvecVectorArrayObject* getTargetVectorArrayPtr() const;

protected:
    xvecVectorArrayObject* targetVectorArray_ = nullptr;
};

class xvecQueryObject
{
public:
    xvecQueryObject(xvecBufferObject* queryVector, const size_t& dim);
    ~xvecQueryObject() noexcept {

    };
    xvecStatus clear() noexcept;
    xvecStatus setTopK(const size_t& k);
    xvecStatus setIndirects(xvecIndirectArrayObject& indirects);
    xvecStatus setQueryVector(xvecVectorArrayObject& queryVector);
    xvecBufferObject* getQueryVectorPointer() const;
    xvecBufferObject* getQueryResultIndexPointer() const;
    xvecBufferObject* getQueryResultScorePointer() const;

    xvecStatus calculateCosineSimilarity();

    size_t getDim() const;

private:
    xvecStatus calculateCosineSimilarityWithIndirect();

    xvecStatus calculateCosineSimilarityWithVector();

private:
    std::shared_ptr<xvecBufferObject> queryVector_ = nullptr;
    std::shared_ptr<xvecVectorArrayObject> targetVectors_ = nullptr;
    std::vector<xvecIndirectArrayObject*> targetIndirects_;

    std::shared_ptr<xvecBufferObject> queryResultIndex = nullptr;
    std::shared_ptr<xvecBufferObject> queryResultScore = nullptr;

    size_t k_ = 0;
    size_t dim_ = 0;
};

}  // namespace pg_xvector
}  // namespace metisx