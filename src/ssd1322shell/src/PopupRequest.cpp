#include "PopupRequest.hpp"

const std::string &PopupRequest::getMainText() const
{
    return mMainText;
}

void PopupRequest::setMainText(const std::string &mainText)
{
    mMainText = mainText;
}

const std::string &PopupRequest::getSecondaryText() const
{
    return mSecondaryText;
}

void PopupRequest::setSecondaryText(const std::string &secondaryText)
{
    mSecondaryText = secondaryText;
}