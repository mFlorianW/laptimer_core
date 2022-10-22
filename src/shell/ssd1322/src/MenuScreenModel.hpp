#ifndef __MENUSCREENMODEL__H__
#define __MENUSCREENMODEL__H__

#include "INavigationHandler.hpp"
#include "MenuEntryList.hpp"
#include "MenuEntryView.hpp"
#include "NavigatableModel.hpp"
#include "NavigateDownCommand.hpp"
#include "NavigateUpCommand.hpp"
#include "SessionView.hpp"
#include "SessionViewModel.hpp"
#include "ShowMainScreenCommand.hpp"
#include <ISessionDatabase.hpp>
#include <array>
#include <kdbindings/signal.h>

class ScreenModel;
class MenuScreenModel : public NavigatableModel, public INavigationHandler
{
public:
    MenuScreenModel(ScreenModel &screenModel, LaptimerCore::Session::ISessionDatabase &sessionDb);

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
    MenuEntryList mSessionEntryModel;
    SessionViewModel mSessionViewModel;
    SessionView mSessionView;

    MenuEntryView mWifiSettings;
    //    MenuEntryModel mWifiEntry;

    MenuEntryView mBluetoothSettings;
    //    MenuEntryModel mBluetoothEntry;

    // MenuEntry Stack
    std::size_t mNavigateIndex = 0;
    std::array<MenuEntryList *, 3> mMenuEntryStack{&mSessionEntryModel};
};

#endif //!__MENUSCREENMODEL__H__
