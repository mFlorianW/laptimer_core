#include "Path.hpp"
#include <algorithm>
#include <string>
#include <vector>

namespace LaptimerCore::Rest
{
class SharedPath : public Common::SharedData
{
public:
    std::string mPath;
    std::vector<std::size_t> mPositions{};

    friend bool operator==(const SharedPath &lhs, const SharedPath &rhs)
    {
        return (lhs.mPositions == rhs.mPositions) && (lhs.mPath == rhs.mPath);
    }
};

Path::Path() noexcept
    : mData{new(std::nothrow) SharedPath{}}
{
}

Path::Path(std::string path) noexcept
    : mData{new(std::nothrow) SharedPath{}}
{
    mData->mPath = std::move(path);
    mData->mPositions.reserve(getDepth());
    for (auto i = std::size_t{0}; i < mData->mPath.size(); ++i)
    {
        if (mData->mPath.at(i) == '/')
        {
            mData->mPositions.emplace_back(i);
        }
    }
}

Path::~Path() noexcept = default;

Path::Path(const Path &other) = default;
Path &Path::operator=(const Path &other) = default;

Path::Path(Path &&other)
    : mData{std::move(other.mData)}
{
    other.mData = nullptr;
}

Path &Path::operator=(Path &&other)
{
    Path moved{std::move(other)};
    std::swap(mData, moved.mData);
    return *this;
}

std::string_view Path::getPath() const noexcept
{
    return mData->mPath;
}

std::size_t Path::getDepth() const noexcept
{
    if (mData->mPath.empty())
    {
        return 0;
    }

    const auto count = std::count(mData->mPath.cbegin(), mData->mPath.cend(), '/');
    return count;
}

std::optional<std::string_view> Path::getEntry(std::size_t index) const noexcept
{
    if (mData->mPath.empty() || index > mData->mPositions.size())
    {
        return std::nullopt;
    }

    constexpr auto pathDelimiterSize = std::size_t{1};
    const auto entryBegin = mData->mPositions.at(index) + pathDelimiterSize;
    const auto entryEnd = index + 1 >= mData->mPositions.size() ? mData->mPath.size() : mData->mPositions.at(index + 1);
    const auto entry = std::string_view{mData->mPath.data() + entryBegin, entryEnd - entryBegin};
    return entry;
}

bool operator==(const Path &lhs, const Path &rhs)
{
    return lhs.mData == rhs.mData || *lhs.mData == *rhs.mData;
}

bool operator!=(const Path &lhs, const Path &rhs)
{
    return !(lhs == rhs);
}

} // namespace LaptimerCore::Rest
