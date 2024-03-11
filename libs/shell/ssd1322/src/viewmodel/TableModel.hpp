#ifndef __TABLEMODEL__H__
#define __TABLEMODEL__H__

#include <cstddef>
#include <kdbindings/signal.h>

/**
 * The TableModel is the data provider for the TableView. The TableModel is
 * queried by the TableView for displaying the data. The table model defines
 * the number of rows and columns.
 */
class TableModel
{
public:
    /**
     * Default empty desctructor
     */
    virtual ~TableModel();

    /**
     * Disable copy constructor.
     */
    TableModel(TableModel const& other) = delete;

    /**
     * Disable copy assignment.
     */
    TableModel& operator=(TableModel const& other) = delete;

    /**
     * Disable move constructor.
     */
    TableModel(TableModel&& other) = delete;

    /**
     * Disable move assignment.
     */
    TableModel& operator=(TableModel&& other) = delete;

    /**
     * Request the data for the given row and column.
     * @param row The row index.
     * @param column The column index.
     * @return std::string The string data for entry.
     */
    virtual std::string data(std::size_t row, std::size_t column) const noexcept = 0;

    /**
     * Request the header data for the given column.
     * @param column The column.
     * @return std::string The data for the header entry.
     */
    virtual std::string headerData(std::size_t column) const noexcept = 0;

    /**
     * Gives the number of rows,
     * @return std::size_t The number of of rows.
     */
    std::size_t getRowCount() const noexcept;

    /**
     * This signal is emitted when the row in the models changed. A row got added or removed.
     */
    KDBindings::Signal<> rowCountChanged;

    /**
     * Gives the number of columns.
     * @return std::size_t The number of columns.
     */
    std::size_t getColumnCount() const noexcept;

    /**
     * This signal is emitted when the columns changed in the model. A column got added or removed.
     */
    KDBindings::Signal<> columnCountChanged;

protected:
    TableModel();

    /**
     * Update the row count in the model.
     * @param newRowCount The new row count.
     */
    void setRowCount(std::size_t newRowCount) noexcept;

    /**
     * Update the column count in the model.
     * @param newColumnCount the new column count.
     */
    void setColumnCont(std::size_t newColumnCount) noexcept;

private:
    std::size_t mRows{0};
    std::size_t mColumns{0};
};

#endif //!__TABLEMODEL__H__