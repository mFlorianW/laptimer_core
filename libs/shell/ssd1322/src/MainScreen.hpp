#ifndef __MAIN_SCREEN__H__
#define __MAIN_SCREEN__H__

#include "Screen.hpp"
#include "StatusBarModel.hpp"
#include "View.hpp"

class MainScreen : public Screen
{
public:
    explicit MainScreen(LaptimerCore::Positioning::IGpsInformationProvider& gpsInfoProvider);
    ~MainScreen() override;

private:
    void onNumberOfSatelliteChanged();

private:
    // indication bar container
    lv_style_t mMainScreenContainerStyle;
    lv_obj_t* mIndicationBarContainer;
    lv_obj_t* mSatelliteLabel;

    // main screen separator
    lv_point_t mSeparatorPoints[2]{{0, 15}, {256, 15}};
    lv_style_t mSeparatorStyle;
    lv_obj_t* m_separator_line;

    StatusBarModel mStatusBarModel;
};

#endif //!__MAIN_SCREEN__H__