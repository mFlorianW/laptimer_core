#include "MenuEntryModel.hpp"

MenuEntryModel::MenuEntryModel(MenuEntryView &menuEntryView)
    : NavigatableModel(0)
    , IOpenCloseHandler()
    , INavigationHandler()
    , mEntryView(menuEntryView)
    , mOpenCommand(*this)
    , mCloseCommand(*this)
    , mNavigateUpCommand(*this)
    , mNavigateDownCommand(*this)
{
    mEntryView.setOpenCommand(&mOpenCommand);

    mSubEntryView.setOpenCommand(&mOpenCommand);
    mSubEntryView.setCloseCommand(&mCloseCommand);
    mSubEntryView.setNavigateUpCommand(&mNavigateUpCommand);
    mSubEntryView.setNavigateDownCommand(&mNavigateDownCommand);

    mActiveView = &mEntryView;
}

View &MenuEntryModel::getView()
{
    return *mActiveView;
}

void MenuEntryModel::addSubMenuEntry(const std::string &entryMainText,
                                     View *settingsView,
                                     const std::string &entrySecondaryText)
{
    if (settingsView == nullptr)
    {
        return;
    }

    // clang-format off
    auto settingsEntry = SettingsEntry
    {
        .entryMainText = entryMainText,
        .entrySecondaryText = entrySecondaryText,
        .settingsView = settingsView
    };
    // clang-format on

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

    const auto entry = mSubViews[getIndex()];
    if (mActiveView == &mEntryView)
    {
        mSubEntryView.setEntryLabel(entry.entryMainText);
        mSubEntryView.setSecondaryLabel(entry.entrySecondaryText);
        mActiveView = &mSubEntryView;
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
    const auto entry = mSubViews[getIndex()];
    if (mActiveView == &mSubEntryView)
    {
        mActiveView = &mEntryView;
    }
    else if (mActiveView == entry.settingsView)
    {
        mSubEntryView.setEntryLabel(entry.entryMainText);
        mSubEntryView.setSecondaryLabel(entry.entrySecondaryText);
        mActiveView = &mSubEntryView;
    }

    viewChanged.emit();
}

void MenuEntryModel::navigateUp()
{
    printf("MenuEntryModel: Navigate UP called!\n");
    incrementIndex();
    const auto entry = mSubViews[getIndex()];
    mSubEntryView.setEntryLabel(entry.entryMainText);
    mSubEntryView.setSecondaryLabel(entry.entrySecondaryText);
    viewChanged.emit();
}

void MenuEntryModel::navigateDown()
{
    printf("MenuEntryModel: Navigate Down called!\n");
    decrementIndex();
    const auto entry = mSubViews[getIndex()];
    mSubEntryView.setEntryLabel(entry.entryMainText);
    mSubEntryView.setSecondaryLabel(entry.entrySecondaryText);
    viewChanged.emit();
}
