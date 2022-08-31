#include "MainScreen.hpp"
#include <stdio.h>

MainScreen::MainScreen(LaptimerCore::Positioning::IGpsInformationProvider &gpsInfoProvider)
    : Screen{}
    , mIndicationBarContainer{lv_cont_create(m_screen, nullptr)}
    , mStatusBarModel{gpsInfoProvider}
{
    // set style for indication bar
    lv_style_init(&mMainScreenContainerStyle);
    lv_style_set_bg_color(&mMainScreenContainerStyle, LV_CONT_PART_MAIN, LV_COLOR_BLACK);
    lv_style_set_border_width(&mMainScreenContainerStyle, LV_CONT_PART_MAIN, 0);

    // configure empty indication bar container
    lv_obj_set_size(mIndicationBarContainer, 256, 14);
    lv_obj_add_style(mIndicationBarContainer, LV_CONT_PART_MAIN, &mMainScreenContainerStyle);

    // create main screen separator
    m_separator_line = lv_line_create(m_screen, nullptr);
    lv_style_init(&mSeparatorStyle);
    lv_style_set_line_width(&mSeparatorStyle, LV_STATE_DEFAULT, 1);
    lv_style_set_line_color(&mSeparatorStyle, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    lv_line_set_points(m_separator_line, mSeparatorPoints, 2);
    lv_obj_add_style(m_separator_line, LV_LINE_PART_MAIN, &mSeparatorStyle);

    // Style for Satellite in indicationbar.
    static lv_style_t m_style_label1;
    lv_style_init(&m_style_label1);
    lv_style_set_text_font(&m_style_label1, LV_STATE_DEFAULT, &lv_font_montserrat_12);

    // // Configure Dummy
    mSatelliteLabel = lv_label_create(mIndicationBarContainer, nullptr);
    lv_obj_add_style(mSatelliteLabel, LV_LABEL_PART_MAIN, &m_style_label1);
    lv_label_set_long_mode(mSatelliteLabel, LV_LABEL_LONG_DOT);
    lv_label_set_text_fmt(mSatelliteLabel, "S%d", 0);
    lv_obj_set_width(mSatelliteLabel, 20);

    mStatusBarModel.numberOfSatellitesChanged.connect(&MainScreen::onNumberOfSatelliteChanged, this);
}

MainScreen::~MainScreen()
{
    lv_obj_del(mIndicationBarContainer);
    lv_obj_del(m_separator_line);
}

void MainScreen::onNumberOfSatelliteChanged()
{
    lv_label_set_text_fmt(mSatelliteLabel, "S%d", mStatusBarModel.getNumberOfStatellites());
}
