#include "PopupRequest.hpp"

const std::string &PopupRequest::getMainText() const noexcept
{
    return mMainText;
}

void PopupRequest::setMainText(const std::string &mainText) noexcept
{
    mMainText = mainText;
}

const std::string &PopupRequest::getSecondaryText() const noexcept
{
    return mSecondaryText;
}

void PopupRequest::setSecondaryText(const std::string &secondaryText) noexcept
{
    mSecondaryText = secondaryText;
}

void PopupRequest::setAutoClosing(bool autoClosing) noexcept
{
    mAutoClosing = true;
}

void PopupRequest::setAutoClosingTimeout(std::chrono::seconds timeout) noexcept
{
    mAutoClosingTimeout = timeout;
}

bool PopupRequest::isAutoClosing() const noexcept
{
    return mAutoClosing;
}

const std::chrono::seconds &PopupRequest::getAutoClosingTimeout() const noexcept
{
    return mAutoClosingTimeout;
}

Type PopupRequest::getPopupType() const noexcept
{
    return mPopupType;
}

void PopupRequest::setPopupType(Type newPopupType) noexcept
{
    mPopupType = newPopupType;
}
