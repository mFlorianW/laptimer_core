#ifndef IMENUENTRY_HPP
#define IMENUENTRY_HPP

#include <kdbindings/signal.h>

class View;

/**
 * The Interface for a menu entry. Every menu entry must be able to return a reference for the view.
 */
class IMenuEntry
{
public:
    /**
     * Virtual default constructor.
     */
    virtual ~IMenuEntry() = default;

    /**
     * Returns the view for the menu entry.
     * @return A View refernce to display the menu entry.
     */
    virtual View *getMenuEntryView() const noexcept = 0;

    /**
     * This signal is emitted when the entry shall be closed and the upper entry shall be displayed.
     */
    KDBindings::Signal<> closeEntry;

    /**
     * This signal shall be emitted by a menu entry when the view changes.
     */
    KDBindings::Signal<> viewChanged;

protected:
    IMenuEntry() = default;
};

#endif // IMENUENTRY_HPP
