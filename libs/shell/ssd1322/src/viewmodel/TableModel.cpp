#include "TableModel.hpp"
#include <cstddef>

TableModel::TableModel() = default;

TableModel::~TableModel() = default;

std::size_t TableModel::getRowCount() const noexcept
{
    return mRows;
}

std::size_t TableModel::getColumnCount() const noexcept
{
    return mColumns;
}

void TableModel::setRowCount(std::size_t newRowCount) noexcept
{
    if (mRows == newRowCount) {
        return;
    }

    mRows = newRowCount;
    rowCountChanged.emit();
}

void TableModel::setColumnCont(std::size_t newColumnCount) noexcept
{
    if (mColumns == newColumnCount) {
        return;
    }

    mColumns = newColumnCount;
    columnCountChanged.emit();
}