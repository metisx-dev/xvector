#pragma once

#include <stdint.h>
#include <stdlib.h>

#include <type_traits>

#include "xvec_status.h"

namespace metisx
{
namespace pg_xvector
{

typedef enum xvecFloatType
{
    XVEC_FLOAT32,
    XVEC_FLOAT16
} xvecFloatType;

class bufferTemplate
{
public:
    virtual void* getRawPointer() = 0;
    virtual xvecStatus reserveMemory(const size_t& bytes) = 0;
    virtual xvecStatus setMemory(bufferTemplate* buffer) = 0;
    virtual xvecStatus clear() noexcept = 0;
    virtual size_t getByteSize() const = 0;

protected:
protected:
    size_t size_ = 0;
};

}  // namespace pg_xvector
}  // namespace metisx
