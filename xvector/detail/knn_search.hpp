#pragma once
#if 0

#include <map>

#include "xvector/detail/knn_result.hpp"
#include "xvector/detail/shared_ptr.hpp"

namespace xvec
{
namespace detail
{
class KnnQuery;
class VectorArray;

class KnnSearch : public Shared<KnnSearch>
{
public:
    KnnSearch(const KnnSearch& src) = delete;
    KnnSearch& operator=(const KnnSearch& src) = delete;

    virtual ~KnnSearch() noexcept = default;

    KnnQuery* query() const noexcept
    {
        return query_;
    }

    virtual void init() noexcept;

    const KnnResult* result() const noexcept
    {
        return result_.get();
    }

    virtual void beginSearch() noexcept;

protected:
    KnnSearch(KnnQuery* query) noexcept;

private:
    KnnQuery* query_;
    SharedPtr<KnnResult> result_;
    std::map<const VectorArray*, std::size_t> vectorArrayToIndex_;
};
}  // namespace detail
}  // namespace xvec
#endif
