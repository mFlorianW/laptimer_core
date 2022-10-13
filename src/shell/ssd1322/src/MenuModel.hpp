#ifndef __MENUMODEL__H__
#define __MENUMODEL__H__

#include "DummyListView.hpp"
#include "INavigationHandler.hpp"
#include "MenuEntryModel.hpp"
#include "MenuEntryView.hpp"
#include "NavigatableModel.hpp"
#include "NavigateDownCommand.hpp"
#include "NavigateUpCommand.hpp"
#include "ShowMainScreenCommand.hpp"
#include <array>
#include <kdbindings/signal.h>

class ScreenModel;
class MenuModel : public NavigatableModel, public INavigationHandler
{
public:
    MenuModel(ScreenModel &screenModel);

    View &getActiveView() const;

    void navigateDown() override;
    void navigateUp() override;

    KDBindings::Signal<> viewChanged;

private:
    void onMenuEntryModelViewChanged();
    void setupSessionMenuEntry();

private:
    ScreenModel &mScreenModel;

    // Commands
    ShowMainScreenCommand mShowMainScreenCommand;
    NavigateUpCommand mNavigateUpCommand;
    NavigateDownCommand mNavigateDownCommand;

    // Session Menu entry
    MenuEntryView mSessionEntryView;
    MenuEntryView mSessionOverview;
    MenuEntryView mSessionDelete;
    MenuEntryView mSessionDeleteAll;
    MenuEntryView mSessionExport;
    MenuEntryModel mSessionEntryModel;
    DummyListView mDummyListView;

    MenuEntryView mWifiSettings;
    MenuEntryModel mWifiEntry;

    MenuEntryView mBluetoothSettings;
    MenuEntryModel mBluetoothEntry;

    // MenuEntry Stack
    std::size_t mNavigateIndex = 0;
    std::array<MenuEntryModel *, 3> mMenuEntryStack{&mSessionEntryModel, &mWifiEntry, &mBluetoothEntry};
};

#endif //!__MENUMODEL__H__