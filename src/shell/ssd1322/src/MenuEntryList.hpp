#ifndef __MENUENTRYMODEL__H__
#define __MENUENTRYMODEL__H__
#include "CloseCommand.hpp"
#include "IMenuEntry.hpp"
#include "INavigationHandler.hpp"
#include "IOpenCloseHandler.hpp"
#include "NavigatableModel.hpp"
#include "NavigateDownCommand.hpp"
#include "NavigateUpCommand.hpp"
#include <kdbindings/signal.h>

/**
 * The MenuEntryList is a list of menu entries that can be navigated in the menu. The entries in the list can be a leaf
 * of the menu tree or any kind of IMenuEntry.
 */
class MenuEntryList final : public IMenuEntry, public NavigatableModel, INavigationHandler, IOpenCloseHandler
{
public:
    MenuEntryList();

    /**
     * @copydoc IMenuEntry::getMenuEntryView
     */
    View *getMenuEntryView() const noexcept override;

    /**
     * @copydoc IMenuEntry::getMenuEntryView
     */
    void addMenuEntry(IMenuEntry *entry) noexcept;

    /**
     * @copydoc INavigationHandler::navigateUp()
     */
    void navigateUp() override;

    /**
     * @copydoc INavigationHandler::navigateDown()
     */
    void navigateDown() override;

    /**
     * @copydoc IOpenCloseHandler::open
     */
    void open() override;

    /**
     * @copydoc IOpenCloseHandler::open
     */
    void close() override;

private:
    void handleSubMenuUpdate();

private:
    View *mActiveView{nullptr};
    std::vector<IMenuEntry *> mMenuEntries;
    NavigateUpCommand mUpCommand;
    NavigateDownCommand mDownCommand;
    CloseCommand mEscapeCommand;
};

#endif //!__MENUENTRYMODEL__H__
