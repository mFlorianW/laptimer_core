// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "PopupRequest.hpp"

std::string const& PopupRequest::getMainText() const noexcept
{
    return mMainText;
}

void PopupRequest::setMainText(std::string const& mainText) noexcept
{
    mMainText = mainText;
}

std::string const& PopupRequest::getSecondaryText() const noexcept
{
    return mSecondaryText;
}

void PopupRequest::setSecondaryText(std::string const& secondaryText) noexcept
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

std::chrono::seconds const& PopupRequest::getAutoClosingTimeout() const noexcept
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
