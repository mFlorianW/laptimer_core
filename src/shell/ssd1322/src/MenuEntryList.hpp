#ifndef __MENUENTRYMODEL__H__
#define __MENUENTRYMODEL__H__

#include "CloseCommand.hpp"
#include "IMenuEntry.hpp"
#include "INavigationHandler.hpp"
#include "IOpenCloseHandler.hpp"
#include "MenuEntryView.hpp"
#include "NavigatableModel.hpp"
#include "NavigateDownCommand.hpp"
#include "NavigateUpCommand.hpp"
#include "OpenCommand.hpp"
#include <kdbindings/signal.h>

/**
 * The MenuEntryList is a list of menu entries that can be navigated in the menu. The entries in the list can be a leaf
 * of the menu tree or any kind of IMenuEntry.
 */
class MenuEntryList : public IMenuEntry, public NavigatableModel, public IOpenCloseHandler, public INavigationHandler
{
public:
    MenuEntryList(MenuEntryView &menuEntryView);

    /**
     * @copydoc IMenuEntry::getMenuEntryView.
     */
    View &getMenuEntryView() override;
    View &getView();

    /**
     * Add as new menu entry to the list.
     * @param menuEntry The entry that shall be added.
     */
    void addMenuEntry(IMenuEntry *menuEntry);
    void addSubMenuEntry(const std::string &entryMainText,
                         View *settingsView,
                         const std::string &entrySecondaryText = "");

    void open() override;
    void close() override;
    void navigateDown() override;
    void navigateUp() override;

private:
    struct SettingsEntry
    {
        std::string entryMainText;
        std::string entrySecondaryText;
        View *settingsView;
    };

    // Menu views
    MenuEntryView &mEntryView;
    MenuEntryView mSubEntryView;
    View *mActiveView{nullptr};
    std::vector<SettingsEntry> mSubViews;
    std::vector<IMenuEntry *> mMenuEntries;

    // Commands
    OpenCommand mOpenCommand;
    CloseCommand mCloseCommand;
    NavigateUpCommand mNavigateUpCommand;
    NavigateDownCommand mNavigateDownCommand;

    // IMenuEntry interface
public:
};

#endif //!__MENUENTRYMODEL__H__
