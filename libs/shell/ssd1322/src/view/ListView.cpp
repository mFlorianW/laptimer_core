// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ListView.hpp"

ListView::ListView()
    : View()
{
}

ListView::~ListView() = default;

void ListView::NavigateDown()
{
    if (mActiveRow == 0) {
        return;
    }

    mActiveRow--;
    displayData(mActiveRow);
}

void ListView::NavigateUp()
{
    if (mActiveRow == mRowCount - 1) {
        return;
    }

    mActiveRow++;
    displayData(mActiveRow);
}
