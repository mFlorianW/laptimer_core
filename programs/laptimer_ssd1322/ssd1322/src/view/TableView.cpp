// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "TableView.hpp"
#include "TableModel.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <lv_font.h>
#include <lv_label.h>
#include <lv_obj.h>

TableView::TableView(TableModel& model)
    : View{}
    , mModel{model}
{
    // Setup View Container
    lv_obj_set_size(mScreenContent, 228, 64);
    lv_obj_set_pos(mScreenContent, 0, 0);

    lv_style_init(&mFontStyle);
    lv_style_set_text_font(&mFontStyle, LV_STATE_DEFAULT, &lv_font_montserrat_12);
    for (std::size_t i = 0; i < sRows; ++i) {
        for (std::size_t j = 0; j < sColumns; ++j) {
            mLabels[i][j] = lv_label_create(mScreenContent, nullptr);
            lv_label_set_long_mode(mLabels[i][j], LV_LABEL_LONG_DOT);
            lv_obj_set_size(mLabels[i][j], 76, 16);
            lv_obj_set_pos(mLabels[i][j], j * lv_obj_get_width(mLabels[i][j]), i * lv_obj_get_height(mLabels[i][j]));
            lv_obj_add_style(mLabels[i][j], LV_LABEL_PART_MAIN, &mFontStyle);
            lv_label_set_text(mLabels[i][j], "");
            lv_label_set_align(mLabels[i][j], LV_LABEL_ALIGN_CENTER);
        }
    }

    mModel.rowCountChanged.connect(&TableView::onRowChanged, this);
    mModel.columnCountChanged.connect(&TableView::onColumnChanged, this);

    // Load initial data
    onRowChanged();
    onColumnChanged();
}

TableView::~TableView()
{
    for (std::size_t i = 0; i < sRows; ++i) {
        for (std::size_t j = 0; j < sColumns; ++j) {
            lv_obj_del(mLabels[i].at(j));
        }
    }
}

void TableView::handleButtonDown()
{
    if ((mActivePage + 1) >= mPages) {
        return;
    }

    ++mActivePage;
    requestData();
}

void TableView::handleButtonUp()
{
    if (mActivePage == 0) {
        return;
    }

    --mActivePage;
    requestData();
}

void TableView::handleEscape()
{
    if (mActiveSidePage == 0 && mEscapeCommand != nullptr) {
        mEscapeCommand->execute();
    }

    // For the case when no close command is set.
    if (mActiveSidePage == 0) {
        return;
    }

    --mActiveSidePage;
    requestData();
    requestHeaderData();
}

void TableView::handleEnter()
{
    if ((mActiveSidePage + 1) >= mSidePages) {
        return;
    }

    ++mActiveSidePage;
    requestHeaderData();
    requestData();
}

void TableView::onColumnChanged() noexcept
{
    mSidePages = std::ceil(static_cast<float>(mModel.getColumnCount()) / static_cast<float>(sColumnPageOffset));
    mActiveSidePage = 0;
    mActivePage = 0;
    requestHeaderData();
    requestData();
}

void TableView::onRowChanged() noexcept
{
    mActiveSidePage = 0;
    mActivePage = 0;
    mPages = std::ceil(static_cast<float>(mModel.getRowCount()) / static_cast<float>(sPageOffset));
    requestData();
}

void TableView::requestData() noexcept
{
    // First clear the current page.
    clearDataRows();

    std::size_t rowIndex = mActivePage * sPageOffset;
    constexpr std::size_t skipHeaderBar = 1;
    // Request new Data
    for (std::size_t i = 0; rowIndex < mModel.getRowCount() && i + skipHeaderBar < sRows; ++i, ++rowIndex) {
        std::size_t columnIndex = mActiveSidePage * sColumnPageOffset;
        for (std::size_t j = 0; columnIndex < mModel.getColumnCount() && j < sColumns; ++j, ++columnIndex) {
            lv_label_set_text(mLabels[i + skipHeaderBar][j], mModel.data(rowIndex, columnIndex).c_str());
        }
    }
}

void TableView::requestHeaderData() noexcept
{
    // Clear header row.
    clearHeaderRow();

    std::size_t columnIndex = mActiveSidePage * sColumnPageOffset;
    for (std::size_t i = 0; i < mModel.getColumnCount() && i < sColumns; ++i, ++columnIndex) {
        lv_label_set_text(mLabels[0][i], mModel.headerData(columnIndex).c_str());
    }
}

void TableView::clearDataRows() noexcept
{
    constexpr std::size_t skipHeaderBar = 1;
    for (std::size_t i = 0; i + skipHeaderBar < sRows; ++i) {
        for (std::size_t j = 0; j < mModel.getColumnCount() && j < sColumns; ++j) {
            lv_label_set_text(mLabels[i + skipHeaderBar][j], "");
        }
    }
}

void TableView::clearHeaderRow() noexcept
{
    for (std::size_t i = 0; i < sColumns; ++i) {
        lv_label_set_text(mLabels[0][i], "");
    }
}