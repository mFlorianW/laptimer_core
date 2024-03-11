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
