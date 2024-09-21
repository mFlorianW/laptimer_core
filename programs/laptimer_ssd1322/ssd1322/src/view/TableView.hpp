// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef TABLEVIEW_HPP
#define TABLEVIEW_HPP

#include "TableModel.hpp"
#include "View.hpp"
#include <array>
#include <cstddef>
#include <memory.h>
#include <vector>

/**
 * A table view shows data in row and column layout. A table view has 4 rows with 3 columns on one view.
 * The first row is always the header. The view can have more rows and columns than can be displayed.
 * The user can navigate the rows with the up and down commands and the columns with enter and escape.
 */
class TableView final : public View
{
public:
    /**
     * Constructs a TableView.
     * @param model The model with the data for the view.
     */
    TableView(TableModel& model);

    /**
     * Cleans all lvgl labels of the view.
     */
    ~TableView() override;

    /**
     * This shows the previous page when possible.
     */
    void handleButtonDown() override;

    /**
     * This shows the next page when possible.
     */
    void handleButtonUp() override;

    /**
     * Calls the close command when the page and side page on default position or navigates back when a paged to the
     * side.
     */
    void handleEscape() override;

    /**
     * Navigates to the next table page when the side pages are bigger then 1 is.
     */
    void handleEnter() override;

private:
    void onColumnChanged() noexcept;
    void onRowChanged() noexcept;
    void requestData() noexcept;
    void requestHeaderData() noexcept;
    void clearDataRows() noexcept;
    void clearHeaderRow() noexcept;

private:
    static constexpr std::size_t sColumns{3};
    static constexpr std::size_t sRows{4};
    static constexpr std::size_t sPageOffset{3};
    static constexpr std::size_t sColumnPageOffset{3};
    lv_style_t mFontStyle;
    std::array<std::array<lv_obj_t*, sColumns>, sRows> mLabels;
    TableModel& mModel;
    std::size_t mSidePages{0};
    std::size_t mActiveSidePage{0};
    std::size_t mActivePage{0};
    std::size_t mPages{0};
};

#endif // TABLEVIEW_HPP
