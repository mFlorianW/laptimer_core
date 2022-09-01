#include "MenuEntryModel.hpp"

MenuEntryModel::MenuEntryModel(MenuEntryView &entryView)
    : NavigatableModel(mSubViews.size())
    , IOpenCloseHandler()
    , INavigationHandler()
    , mEntryView(entryView)
    , mOpenCommand(*this)
    , mCloseCommand(*this)
    , mNavigateUpCommand(*this)
    , mNavigateDownCommand(*this)
{
    mEntryView.setOpenCommand(&mOpenCommand);
    mActiveView = &mEntryView;
}

View &MenuEntryModel::getView()
{
    return *mActiveView;
}

void MenuEntryModel::addSubMenuEntry(MenuEntryView *entryView, View *settingsView)
{
    if (entryView == nullptr || settingsView == nullptr)
    {
        return;
    }

    // clang-format off
    auto settingsEntry = SettingsEntry
    {
        .entryView = entryView, 
        .settingsView = settingsView
    };
    // clang-format on

    settingsEntry.entryView->setOpenCommand(&mOpenCommand);
    settingsEntry.entryView->setCloseCommand(&mCloseCommand);
    settingsEntry.entryView->setNavigateUpCommand(&mNavigateUpCommand);
    settingsEntry.entryView->setNavigateDownCommand(&mNavigateDownCommand);

    settingsEntry.settingsView->setCloseCommand(&mCloseCommand);

    mSubViews.push_back(settingsEntry);
    setSize(mSubViews.size());
}

void MenuEntryModel::open()
{
    printf("MenuEntryModel: Open called!\n");
    if (mSubViews.size() == 0)
    {
        return;
    }

    auto entry = mSubViews[getIndex()];
    if (mActiveView == &mEntryView)
    {
        mActiveView = entry.entryView;
    }
    else
    {
        mActiveView = entry.settingsView;
    }

    viewChanged.emit();
}

void MenuEntryModel::close()
{
    printf("MenuEntryModel: Close called!\n");
    auto entry = mSubViews[getIndex()];
    if (mActiveView == entry.entryView)
    {
        mActiveView = &mEntryView;
    }
    else if (mActiveView == entry.settingsView)
    {
        mActiveView = entry.entryView;
    }

    viewChanged.emit();
}

void MenuEntryModel::navigateUp()
{
    printf("MenuEntryModel: Navigate UP called!\n");
    incrementIndex();
    mActiveView = mSubViews[getIndex()].entryView;
    viewChanged.emit();
}

void MenuEntryModel::navigateDown()
{
    printf("MenuEntryModel: Navigate Down called!\n");
    decrementIndex();
    mActiveView = mSubViews[getIndex()].entryView;
    viewChanged.emit();
}
