#include "xvec_buffer_impl.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <list>

namespace metisx
{
namespace pg_xvector
{

xvecBufferObject::xvecBufferObject()
{
}

xvecBufferObject::xvecBufferObject(xvecBufferObject& src)
{
    setBufferFrom(&src);
}

xvecBufferObject::~xvecBufferObject() noexcept
{
    clear();
}

void* xvecBufferObject::getRawPointer()
{
    return reinterpret_cast<void*>(data_.get());
}

xvecStatus xvecBufferObject::reserveMemory(const size_t& bytes)
{
    if (data_ == nullptr)
    {
        try
        {
            data_ = std::shared_ptr<char[]>(new char[bytes], std::default_delete<char[]>());
            size_ = bytes;
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return XVEC_STATUS_OUT_OF_MEMORY;
        }
    }
    else if (size_ == bytes)
    {
        return XVEC_STATUS_SUCCESS;
    }
    else if (size_ > bytes)
    {
        // warning
    }
    else
    {
        try
        {
            auto newData = std::shared_ptr<char[]>(new char[bytes], std::default_delete<char[]>());
            memcpy(newData.get(), data_.get(), size_);
            data_.reset();
            data_ = std::move(newData);
            size_ = bytes;
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return XVEC_STATUS_OUT_OF_MEMORY;
        }
    }

    return XVEC_STATUS_SUCCESS;
}

xvecStatus xvecBufferObject::clear() noexcept
{
    if (data_ != nullptr)
    {
        data_.reset();
    }
    return xvecStatus::XVEC_STATUS_SUCCESS;
}

size_t xvecBufferObject::getByteSize() const
{
    return size_;
}

std::shared_ptr<char[]> xvecBufferObject::getSharedPointer()
{
    return data_;
}

xvecStatus xvecBufferObject::setBufferFrom(xvecBufferObject* src)
{
    data_ = src->getSharedPointer();
    size_ = src->getByteSize();

    return XVEC_STATUS_SUCCESS;
}

xvecStatus xvecBufferObject::setMemory(bufferTemplate* buffer)
{
    auto src = dynamic_cast<xvecBufferObject*>(buffer);

    xvecStatus status = xvecStatus::XVEC_STATUS_SUCCESS;

    if (src == nullptr)
    {
        return XVEC_STATUS_INVALID_PTR;
    }

    if (data_ == nullptr)
    {
        clear();
    }
    else if (data_ == src->getSharedPointer())
    {
        return XVEC_STATUS_SUCCESS;
    }
    else
    {
        data_.reset();
    }

    return setBufferFrom(src);
}

xvecVectorArrayObject::xvecVectorArrayObject(const size_t& dim, const uint32_t& type)
    : dim_(dim),
      type_(type)
{
}

xvecStatus xvecVectorArrayObject::reserveMemory(const size_t& count)
{
    return xvecBufferObject::reserveMemory(getDim() * count * (1 << (2 - type_)));
    // return xvecBufferObject::reserveMemory(getDim() * count * (type_ == XVEC_FLOAT32 ? 4 : 2));
}

size_t xvecVectorArrayObject::getSize() const
{
    return (size_ / dim_) >> (2 - type_);
    // return size_ / (dim_ * (type_ == XVEC_FLOAT32 ? 4 : 2));
}

xvecStatus xvecIndirectArrayObject::reserveMemory(const size_t& count)
{
    return xvecBufferObject::reserveMemory(count << 2);
}

size_t xvecIndirectArrayObject::getSize() const
{
    return size_ >> 2;
    // return size_ / 4;
}

xvecVectorArrayObject* xvecIndirectArrayObject::getTargetVectorArrayPtr() const
{
    return targetVectorArray_;
};

xvecQueryObject::xvecQueryObject(xvecBufferObject* queryVector, const size_t& dim)
    : queryVector_(queryVector),
      dim_(dim)
{
}

xvecStatus xvecQueryObject::clear() noexcept
{
    if (queryVector_ != nullptr)
    {
        queryVector_.reset();
    }

    if (queryResultIndex != nullptr)
    {
        queryResultIndex.reset();
    }

    if (queryResultScore != nullptr)
    {
        queryResultScore.reset();
    }

    return XVEC_STATUS_SUCCESS;
}

xvecStatus xvecQueryObject::setTopK(const size_t& k)
{
    k_ = k;
    return XVEC_STATUS_SUCCESS;
}

xvecStatus xvecQueryObject::setIndirects(xvecIndirectArrayObject& indirects)
{
    targetIndirects_.push_back(&indirects);
    return XVEC_STATUS_SUCCESS;
}

xvecStatus xvecQueryObject::setQueryVector(xvecVectorArrayObject& queryVector)
{
    if (targetVectors_ != nullptr)
    {
        targetVectors_.reset();
    }

    targetVectors_ = std::make_shared<xvecVectorArrayObject>(queryVector);

    return XVEC_STATUS_SUCCESS;
}

xvecBufferObject* xvecQueryObject::getQueryVectorPointer() const
{
    return queryVector_.get();
}

xvecBufferObject* xvecQueryObject::getQueryResultIndexPointer() const
{
    return queryResultIndex.get();
}

xvecBufferObject* xvecQueryObject::getQueryResultScorePointer() const
{
    return queryResultScore.get();
}

size_t xvecQueryObject::getDim() const
{
    return dim_;
}

xvecStatus xvecQueryObject::calculateCosineSimilarity()
{
    if (queryResultIndex == nullptr)
    {
        queryResultIndex = std::shared_ptr<xvecBufferObject>(new xvecBufferObject());
        queryResultIndex->reserveMemory(k_ * sizeof(uint32_t));
    }
    if (queryResultScore == nullptr)
    {
        queryResultScore = std::shared_ptr<xvecBufferObject>(new xvecBufferObject());
        queryResultScore->reserveMemory(k_ * sizeof(float));
    }

    if (targetIndirects_.size() > 0)
    {
        return calculateCosineSimilarityWithIndirect();
    }
    else if (targetVectors_ != nullptr)
    {
        return calculateCosineSimilarityWithVector();
    }
    else
    {
        return XVEC_STATUS_INVALID_PTR;
    }
};

xvecStatus xvecQueryObject::calculateCosineSimilarityWithVector()
{
    // vector full scan mode
    size_t targetVectorCount = targetVectors_->getSize();

    std::list<std::pair<float, size_t>> dotList;

    for (size_t targetVector = 0; targetVector < targetVectors_->getSize(); targetVector++)
    {
        float dotRes = 0;
        float* queryVectorPtr = reinterpret_cast<float*>(queryVector_->getRawPointer());
        float* targetVectorPtr = reinterpret_cast<float*>(targetVectors_->getRawPointer());

        for (size_t idx = 0; idx < dim_; idx++)
        {
            dotRes += queryVectorPtr[idx] * targetVectorPtr[targetVector * dim_ + idx];
        }

        if (dotList.size() == 0)
        {
            dotList.push_back(std::make_pair(dotRes, targetVector));
        }
        else
        {
            if (dotList.size() == k_)
            {
                dotList.pop_back();
            }
            dotList.push_back(std::make_pair(dotRes, targetVector));
            dotList.sort(
                [](std::pair<float, size_t>& a, std::pair<float, size_t>& b)
                {
                    return a.first > b.first;
                });
        }
    }

    float* queryResultScorePtr = reinterpret_cast<float*>(queryResultScore->getRawPointer());
    uint32_t* queryResultIndexPtr = reinterpret_cast<uint32_t*>(queryResultIndex->getRawPointer());

    for (size_t idx = 0; idx < k_; idx++)
    {
        queryResultScorePtr[idx] = dotList.front().first;
        queryResultIndexPtr[idx] = dotList.front().second;
        dotList.pop_front();
    }

    return XVEC_STATUS_SUCCESS;
}

xvecStatus xvecQueryObject::calculateCosineSimilarityWithIndirect()
{
    // indirect table search method
    size_t indirectTableCount = targetIndirects_.size();

    std::list<std::pair<float, size_t>> dotList;

    for (size_t indirectTable = 0; indirectTable < indirectTableCount; indirectTable++)
    {
        for (size_t indirectIdx = 0; indirectIdx < targetIndirects_[indirectTable]->getSize();
             indirectIdx++)
        {
            size_t targetVectorIdx = reinterpret_cast<uint32_t*>(
                targetIndirects_[indirectTable]->getRawPointer())[indirectIdx];

            float dotRes = 0;
            float* queryVectorPtr = reinterpret_cast<float*>(queryVector_->getRawPointer());
            float* targetVectorPtr = reinterpret_cast<float*>(
                targetIndirects_[indirectTable]->getTargetVectorArrayPtr()->getRawPointer());

            for (size_t idx = 0; idx < dim_; idx++)
            {
                dotRes += queryVectorPtr[idx] * targetVectorPtr[targetVectorIdx * dim_ + idx];
            }

            if (dotList.size() == 0)
            {
                dotList.push_back(std::make_pair(dotRes, targetVectorIdx));
            }
            else
            {
                if (dotList.size() == k_)
                {
                    dotList.pop_back();
                }
                dotList.push_back(std::make_pair(dotRes, targetVectorIdx));
                dotList.sort(
                    [](std::pair<float, size_t>& a, std::pair<float, size_t>& b)
                    {
                        return a.first > b.first;
                    });
            }
        }
    }

    float* queryResultScorePtr = reinterpret_cast<float*>(queryResultScore->getRawPointer());
    uint32_t* queryResultIndexPtr = reinterpret_cast<uint32_t*>(queryResultIndex->getRawPointer());

    for (size_t idx = 0; idx < k_; idx++)
    {
        queryResultScorePtr[idx] = dotList.front().first;
        queryResultIndexPtr[idx] = dotList.front().second;
        dotList.pop_front();
    }

    return XVEC_STATUS_SUCCESS;
}

}  // namespace pg_xvector
}  // namespace metisx