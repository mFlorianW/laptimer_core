#ifndef MENUENTRY_HPP
#define MENUENTRY_HPP

#include "CloseCommand.hpp"
#include "IMenuEntry.hpp"
#include "IOpenCloseHandler.hpp"
#include "OpenCommand.hpp"

/**
 * A menu entry is a entry in the menu hierachie it has a view and can have one child menu entry. This is automatic
 * opended, when the user presses the enter button and when the user presses the escape button the menu entry emits the
 * close entry command changes from the submenu entry back to the entry view.
 */
class MenuEntry : public IMenuEntry, public IOpenCloseHandler
{
public:
    MenuEntry();

    /**
     * @copydoc IMenuEntry::getMenuEntryView
     */
    View *getMenuEntryView() const noexcept override;

    /**
     * Sets the entry for the menu.
     * @param view The new view for the menu.
     */
    void setMenuEntryView(View *view) noexcept;

    /**
     * Adds the single sub menu entry.
     * @param entry The submenu entry.
     */
    void addMenuEntry(IMenuEntry *entry) noexcept;

    /**
     * @copydoc IOpenCloseHandler::open
     */
    void open() override;

    /**
     * @copydoc IOpenCloseHandler::close
     */
    void close() override;

protected:
    View *mEntryView{nullptr};
    View *mActiveView{nullptr};
    IMenuEntry *mMenuEntry{nullptr};
    OpenCommand mEnterCommand;
    CloseCommand mEscapeCommand;
};

#endif // MENUENTRY_HPP
