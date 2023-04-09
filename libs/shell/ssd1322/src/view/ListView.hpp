#ifndef __SETTINGSLISTVIEW__H__
#define __SETTINGSLISTVIEW__H__

#include "View.hpp"

/**
 * The list view display same data in form in list with one view.
 */
class ListView : public View
{
public:
    virtual ~ListView();

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

#endif //!__SETTINGSLISTVIEW__H__