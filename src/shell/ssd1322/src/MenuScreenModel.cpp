#include "MenuScreenModel.hpp"
#include "../include/ScreenModel.hpp"

MenuScreenModel::MenuScreenModel(ScreenModel &screenModel, LaptimerCore::Session::ISessionDatabase &sessionDb)
    : NavigatableModel(0)
    , INavigationHandler()
    , mScreenModel(screenModel)
    , mShowMainScreenCommand(mScreenModel)
    , mNavigateUpCommand(*this)
    , mNavigateDownCommand(*this)
    , mSessionEntryModel(mSessionEntryView)
{
    setupSessionMenuEntry();
}

View &MenuScreenModel::getActiveView() const
{
    auto index = getIndex();
    if (index > mMenuEntryStack.size())
    {
        return mMenuEntryStack[0]->getView();
    }

    return mMenuEntryStack[index]->getView();
}

void MenuScreenModel::navigateDown()
{
    decrementIndex();
    viewChanged.emit();
}

void MenuScreenModel::navigateUp()
{
    incrementIndex();
    viewChanged.emit();
}

void MenuScreenModel::onMenuEntryModelViewChanged()
{
    viewChanged.emit();
}

void MenuScreenModel::setupSessionMenuEntry()
{
    // Setup Session Settings entry
    mSessionEntryView.setCloseCommand(&mShowMainScreenCommand);
    mSessionEntryView.setEntryLabel("Session");
    mSessionEntryView.setSecondaryLabel("Settings");
    mSessionEntryView.setNavigateUpCommand(&mNavigateUpCommand);
    mSessionEntryView.setNavigateDownCommand(&mNavigateDownCommand);
    mSessionEntryModel.viewChanged.connect(&MenuScreenModel::onMenuEntryModelViewChanged, this);

    // Setup entry sub view
    mSessionEntryModel.addSubMenuEntry("Session", &mDummyListView, "Overview");
    mSessionEntryModel.addSubMenuEntry("Session", &mDummyListView, "DeleteAll");
}
