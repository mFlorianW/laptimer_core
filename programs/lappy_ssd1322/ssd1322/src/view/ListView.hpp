// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "View.hpp"

/**
 * The list view display same data in form in list with one view.
 */
class ListView : public View
{
public:
    ~ListView() override;

    // Delete copy constructor
    ListView(ListView const&) = delete;

    // Delete copy assignment operator
    ListView& operator=(ListView const&) = delete;

    // Delete move constructor
    ListView(ListView&&) = delete;

    // Delete move assignment operator
    ListView& operator=(ListView&&) = delete;

    /**
     * Is called when the user navigates down.
     */
    void NavigateDown();

    /**
     * Is called when the user navigates up.
     */
    void NavigateUp();

protected:
    /**
     *
     */
    ListView();

    /**
     * The number of elements in the list.
     * @return std::size_t  The number of elements in the list.
     */
    virtual std::size_t getRows() const = 0;

    /**
     * Is called when the view displays a specific row.
     * @param row The row that shall be displayed.
     */
    virtual void displayData(std::size_t row) = 0;

private:
    std::size_t mRowCount{0};
    std::size_t mActiveRow{0};
};
