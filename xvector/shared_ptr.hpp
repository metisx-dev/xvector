#pragma once

#include <atomic>
//#include <type_traits>
#include <utility>

namespace xvec
{
// template <typename Derived, typename Base>
class Shared;

template <typename T>
class SharedPtr
{
public:
    // static_assert(std::is_base_of_v<Shared<std::remove_cv_t<T>>, std::remove_cv_t<T>>);

    template <typename U>
    static SharedPtr weak(U* ptr)
    {
        SharedPtr ret;
        ret.ptr_ = ptr;
        return ret;
    }

    SharedPtr()
        : ptr_(nullptr)
    {
    }

    SharedPtr(const SharedPtr& rhs)
        : ptr_(rhs.get())
    {
        if (ptr_)
            ptr_->retain();
    }

    SharedPtr(SharedPtr&& rhs)
        : ptr_(rhs.ptr_)
    {
        rhs.ptr_ = nullptr;
    }

    template <typename U>
    SharedPtr(const SharedPtr<U>& rhs)
        : ptr_(rhs.get())
    {
        if (ptr_)
            ptr_->retain();
    }

    template <typename U>
    SharedPtr(SharedPtr<U>&& rhs)
        : ptr_(rhs.ptr_)
    {
        rhs.ptr_ = nullptr;
    }

    SharedPtr(std::nullptr_t)
        : ptr_(nullptr)
    {
    }

    template <typename U>
    SharedPtr(U* ptr)
        : ptr_(ptr)
    {
        if (ptr_)
            ptr_->retain();
    }

    ~SharedPtr()
    {
        if (ptr_)
            ptr_->release();
    }

    SharedPtr& operator=(const SharedPtr& rhs)
    {
        *this = rhs.ptr_;

        return *this;
    }

    SharedPtr& operator=(SharedPtr&& rhs)
    {
        if (ptr_ != rhs.ptr_)
        {
            if (ptr_)
                ptr_->release();
            ptr_ = rhs.ptr_;
            rhs.ptr_ = nullptr;
        }
        return *this;
    }

    SharedPtr& operator=(std::nullptr_t)
    {
        if (ptr_)
            ptr_->release();

        ptr_ = nullptr;

        return *this;
    }

    SharedPtr& operator=(T* rhs)
    {
        if (ptr_ != rhs)
        {
            if (rhs)
                rhs->retain();

            if (ptr_)
                ptr_->release();

            ptr_ = rhs;
        }

        return *this;
    }

    T* operator[](std::size_t index) const
    {
        return ptr_[index];
    }

    T* operator->() const
    {
        return ptr_;
    }

    operator bool() const
    {
        return ptr_ != nullptr;
    }

    bool operator!() const
    {
        return ptr_ == nullptr;
    }

    T* get() const
    {
        return ptr_;
    }

private:
    T* ptr_;
};

template <typename T, typename... Args>
inline SharedPtr<T> makeShared(Args&&... args)
{
    T* obj = new T(std::forward<Args>(args)...);
    return SharedPtr<T>::weak(obj);
}

template <typename T>
inline bool operator==(const SharedPtr<T>& lhs, const SharedPtr<T>& rhs)
{
    return lhs.get() == rhs.get();
}

template <typename T, typename U>
inline bool operator==(const SharedPtr<T>& lhs, U* rhs)
{
    return lhs.get() == rhs;
}

template <typename T, typename U>
inline bool operator==(U* lhs, const SharedPtr<T>& rhs)
{
    return lhs == rhs.get();
}

template <typename T>
inline bool operator==(std::nullptr_t, const SharedPtr<T>& rhs)
{
    return nullptr == rhs.get();
}

template <typename T>
inline bool operator==(const SharedPtr<T>& rhs, std::nullptr_t)
{
    return rhs.get() == nullptr;
}

template <typename T, typename U>
inline bool operator!=(const SharedPtr<T>& lhs, U&& rhs)
{
    return !(lhs == std::forward<U>(rhs));
}

template <typename T, typename U>
inline bool operator!=(U&& lhs, const SharedPtr<T>& rhs)
{
    return !(std::forward<U>(lhs) == rhs);
}

class DummyBase
{
};

class Shared
{
public:
    void retain() const
    {
        ++counter_;
    }

    void release() const
    {
        --counter_;

        if (counter_ == 0)
        {
            const_cast<Shared*>(this)->destruct();
        }
    }

    virtual void destruct() const
    {
        delete this;
    }

    virtual ~Shared() = default;

    // template <typename... Args>
    // static Derived* create(Args&&... args)
    //{
    //     return new Derived(std::forward<Args>(args)...);
    // }

private:
    mutable std::atomic_size_t counter_ = 1;
};

}  // namespace xvec
