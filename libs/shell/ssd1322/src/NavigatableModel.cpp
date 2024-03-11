#include "NavigatableModel.hpp"

NavigatableModel::NavigatableModel(std::size_t size)
    : mSize(size)
{
}

std::size_t NavigatableModel::getSize() const noexcept
{
    return mSize;
}

void NavigatableModel::setSize(std::size_t size)
{
    mSize = size;
}

std::size_t NavigatableModel::getIndex() const
{
    return mIndex;
}

void NavigatableModel::incrementIndex()
{
    if ((mIndex + 1) >= mSize) {
        mIndex = 0;
    } else {
        ++mIndex;
    }
}

void NavigatableModel::decrementIndex()
{
    if (mIndex == 0) {
        mIndex = mSize - 1;
    } else {
        --mIndex;
    }
}
