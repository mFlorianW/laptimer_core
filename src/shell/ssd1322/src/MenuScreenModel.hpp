#ifndef __MENUSCREENMODEL__H__
#define __MENUSCREENMODEL__H__

#include "MenuEntry.hpp"
#include "MenuEntryList.hpp"
#include "MenuEntryView.hpp"
#include "SessionView.hpp"
#include "SessionViewModel.hpp"
#include <ISessionDatabase.hpp>
#include <array>
#include <kdbindings/signal.h>

class ScreenModel;
class MenuScreenModel
{
public:
    MenuScreenModel(ScreenModel &screenModel, LaptimerCore::Storage::ISessionDatabase &sessionDb);

    /**
     * Gives the view that shall be displayed.
     * @return A reference to the view, that shall be displayed.
     */
    View &getActiveView() const;

    /**
     * This signal is emitted when the menu has new view that shall be displayed.
     */
    KDBindings::Signal<> viewChanged;

    /**
     * This signal is emitted when the menu can be closed and another screen can be displayed.
     */
    KDBindings::Signal<> closeMenu;

private:
    void setupBluetoothMenu();
    void setupSessionMenu();
    void setupRootMenu();

    void handleMenuViewChanged();
    void handleCloseEntry();

private:
    ScreenModel &mScreenModel;

    // Bluetooth MenuList
    MenuEntry mRootBluetoohMenuEntry;
    MenuEntryView mRootBluetoohMenuView;

    // Session MenuList
    MenuEntry mRootSessionMenuEntry;
    MenuEntryView mRootSessionMenuView;
    MenuEntryList mSessionDetailMenu;
    SessionViewModel mSessionViewModelEntry;
    SessionView mSessionView;
    MenuEntry mSessionDeleteAllEntry;
    MenuEntryView mSessionDeleteAllView;
    MenuEntry mSessionOverviewEntry;
    MenuEntryView mSessionOverviewView;

    // Root MenuList
    MenuEntryList mRootMenu;
};

#endif //!__MENUSCREENMODEL__H__
