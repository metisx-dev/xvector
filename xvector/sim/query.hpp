#pragma once

#include <cstddef>

namespace xvec
{
namespace sim
{

class Query
{
public:
    enum Type
    {
        Knn,
        Distance
    };

    Type queryType() const noexcept
    {
        return queryType_;
    }

protected:
    explicit Query(Type queryType) noexcept
        : queryType_(queryType)
    {
    }

    virtual ~Query() noexcept = default;

    Type queryType_;
};

void executeQuery(Query** queries, std::size_t count);

}  // namespace sim
}  // namespace xvec
