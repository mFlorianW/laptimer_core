#include "NavigatableModel.hpp"

NavigatableModel::NavigatableModel(std::size_t size)
    : mSize(size)
{
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
    auto tempIndex = ++mIndex;
    if (tempIndex >= mSize)
    {
        tempIndex = 0;
    }
    mIndex = tempIndex;
}

void NavigatableModel::decrementIndex()
{
    std::size_t tempIndex;
    if (mIndex == 0)
    {
        tempIndex = mSize - 1;
    }
    else
    {
        tempIndex = --mIndex;
    }
    mIndex = tempIndex;
}