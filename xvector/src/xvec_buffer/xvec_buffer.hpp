#pragma once

#include "xvec_buffer_impl.hpp"

#include <stdint.h>

template <typename obj>
class xvecSharedPtr
{
public:
    xvecSharedPtr()
    {
        obj_ = new obj;
        addReference();
    }

    explicit xvecSharedPtr(const obj& objParam)
    {
        obj_ = new obj;
        *obj_ = objParam;
        addReference();
    }

    template <typename... Args>
    xvecSharedPtr(const Args&... args)
    {
        obj_ = new obj(args...);
        addReference();
    }

    ~xvecSharedPtr() noexcept
    {
        if (obj_ != nullptr)
        {
            release();
        }
    }

    xvecSharedPtr& operator=(const xvecSharedPtr& rhs)
    {
        if (this != &rhs)
        {
            if (obj_ != nullptr)
            {
                delete obj_;
            }

            obj_ = rhs.obj_;
            addReference();
        }
        return *this;
    }

    template <typename ptrType,
              typename ptrtype_v =
                  std::enable_if_t<std::is_pointer_v<ptrType> || std::is_null_pointer_v<ptrType>>>
    bool operator==(ptrType rhs)
    {
        return obj_ == rhs;
    }

    void* shareRawPtr()
    {
        addReference();
        return reinterpret_cast<void*>(this);
    }

    obj* shareDataPtr()
    {
        addReference();
        return obj_;
    }

    obj* get() const noexcept
    {
        return obj_;
    }

    obj* operator->() const noexcept
    {
        return obj_;
    }

    void release() noexcept
    {
        referenceCount_--;
        if (referenceCount_ == 0)
        {
            dealloc();
        }
    }

private:
    void addReference() noexcept
    {
        // mutex? atomic? for multi-threading
        referenceCount_++;
    }

    void dealloc() noexcept
    {
        delete obj_;
        obj_ = nullptr;
        delete this;
    }

private:
    obj* obj_ = nullptr;
    size_t referenceCount_ = 0;
};