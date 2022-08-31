#ifndef __SCREENCONTROLLER__H__
#define __SCREENCONTROLLER__H__

#include "ActiveSessionView.hpp"
#include "MainScreen.hpp"
#include "MainScreenModel.hpp"
#include "MenuModel.hpp"
#include "MenuScreen.hpp"
#include "ShowMainScreenCommand.hpp"
#include "ShowMenuScreenCommand.hpp"
#include <IPositionInformationProvider.hpp>

class ScreenModel
{
public:
    ScreenModel(LaptimerCore::Positioning::IGpsInformationProvider &gpsInfoProvider,
                LaptimerCore::Positioning::IPositionInformationProvider &posInfoProvider);

    void activateMainScreen();
    void activateMenuScreen();

private:
    // Screens
    MainScreen mMainScreen;
    MenuScreen mMenuScreen;

    // Screen Models
    MenuModel mMenuModel;
    MainScreenModel mMainScreenModel;
};

#endif //!__SCREENCONTROLLER__H__