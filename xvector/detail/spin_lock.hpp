#pragma once

#include <atomic>

class SpinLock
{
public:
    void lock()
    {
        while (lock_.test_and_set(std::memory_order_acquire))  // acquire lock
        {
            // Since C++20, it is possible to update atomic_flag's
            // value only when there is a chance to acquire the lock.
            // See also: https://stackoverflow.com/questions/62318642
#if defined(__cpp_lib_atomic_flag_test)
            while (lock_.test(std::memory_order_relaxed))  // test lock
#endif
                ;  // spin
        }
    }

    bool try_lock()
    {
        return !lock_.test_and_set(std::memory_order_acquire);
    }

    void unlock()
    {
        lock_.clear(std::memory_order_release);  // release lock
    }

private:
    std::atomic_flag lock_ = ATOMIC_FLAG_INIT;
};
