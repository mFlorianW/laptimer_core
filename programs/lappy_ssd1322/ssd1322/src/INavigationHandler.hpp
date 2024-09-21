// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

class INavigationHandler
{
public:
    virtual ~INavigationHandler() = default;

    // Delete copy constructor
    INavigationHandler(INavigationHandler const&) = delete;

    // Delete copy assignment operator
    INavigationHandler& operator=(INavigationHandler const&) = delete;

    // Delete move constructor
    INavigationHandler(INavigationHandler&&) = delete;

    // Delete move assignment operator
    INavigationHandler& operator=(INavigationHandler&&) = delete;

    /**
     * Handle down navigation
     */
    virtual void navigateDown() = 0;

    /**
     * Handle up navigation
     */
    virtual void navigateUp() = 0;

protected:
    INavigationHandler() = default;
};
