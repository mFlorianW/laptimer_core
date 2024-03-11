#include "MenuEntryList.hpp"
#include "View.hpp"

MenuEntryList::MenuEntryList()
    : NavigatableModel(0)
    , mUpCommand{*this}
    , mDownCommand{*this}
    , mEscapeCommand{*this}
{
}

void MenuEntryList::addMenuEntry(IMenuEntry* menuEntry) noexcept
{
    if (menuEntry == nullptr) {
        return;
    }

    // Set commands for the entry view. The commands are for the navigation in the menu.
    menuEntry->getMenuEntryView()->setNavigateUpCommand(&mUpCommand);
    menuEntry->getMenuEntryView()->setNavigateDownCommand(&mDownCommand);
    menuEntry->getMenuEntryView()->setCloseCommand(&mEscapeCommand);

    // Connect to the signals of the menu entry. This handles the sub menu entries.
    menuEntry->viewChanged.connect([=]() {
        handleSubMenuUpdate();
    });
    menuEntry->closeEntry.connect([=]() {
        handleSubMenuUpdate();
    });

    mMenuEntries.push_back(menuEntry);
    setSize(mMenuEntries.size());
}

void MenuEntryList::navigateUp()
{
    decrementIndex();
    mActiveView = mMenuEntries[getIndex()]->getMenuEntryView();
    viewChanged.emit();
}

void MenuEntryList::navigateDown()
{
    incrementIndex();
    mActiveView = mMenuEntries[getIndex()]->getMenuEntryView();
    viewChanged.emit();
}

void MenuEntryList::open()
{
}

void MenuEntryList::close()
{
    closeEntry.emit();
}

void MenuEntryList::handleSubMenuUpdate()
{
    mActiveView = mMenuEntries[getIndex()]->getMenuEntryView();
    viewChanged.emit();
}

View* MenuEntryList::getMenuEntryView() const noexcept
{
    assert(mMenuEntries.empty() == false);
    return mMenuEntries[getIndex()]->getMenuEntryView();
}
