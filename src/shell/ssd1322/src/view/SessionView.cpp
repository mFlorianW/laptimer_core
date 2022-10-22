#include "SessionView.hpp"

SessionView::SessionView(SessionViewModel &sessionViewModel)
    : mSessionViewModel(sessionViewModel)
{
    // Setup View Container
    lv_obj_set_size(mScreenContent, 228, 64);
    lv_obj_set_pos(mScreenContent, 0, 0);

    // Setup label style
    lv_style_init(&mLabelStyle);
    lv_style_set_text_font(&mLabelStyle, LV_STATE_DEFAULT, &lv_font_montserrat_16);

    // Setup track name label
    mTrackNameLabel = lv_label_create(mScreenContent, nullptr);
    lv_obj_add_style(mTrackNameLabel, LV_LABEL_PART_MAIN, &mLabelStyle);
    lv_obj_set_size(mTrackNameLabel, lv_obj_get_width(mScreenContent), 16);
    lv_obj_set_x(mTrackNameLabel, 0);
    lv_obj_set_y(mTrackNameLabel, 0);
    mSessionViewModel.trackName.valueChanged().connect([=]() { setTrackName(); });

    // Setup date label
    mDateLabel = lv_label_create(mScreenContent, nullptr);
    lv_obj_add_style(mDateLabel, LV_LABEL_PART_MAIN, &mLabelStyle);
    lv_obj_set_size(mDateLabel, lv_obj_get_width(mScreenContent), 16);
    lv_obj_set_x(mDateLabel, 0);
    lv_obj_set_y(mDateLabel, 20);
    mSessionViewModel.date.valueChanged().connect([=]() { setDate(); });

    // Setup time label
    mTimeLabel = lv_label_create(mScreenContent, nullptr);
    lv_obj_add_style(mTimeLabel, LV_LABEL_PART_MAIN, &mLabelStyle);
    lv_obj_set_size(mTimeLabel, lv_obj_get_width(mScreenContent), 16);
    lv_obj_set_x(mTimeLabel, 128);
    lv_obj_set_y(mTimeLabel, 20);
    mSessionViewModel.time.valueChanged().connect([=]() { setTime(); });

    // Setup lap label
    mLapLabel = lv_label_create(mScreenContent, nullptr);
    lv_obj_add_style(mLapLabel, LV_LABEL_PART_MAIN, &mLabelStyle);
    lv_obj_set_size(mLapLabel, lv_obj_get_width(mScreenContent), 16);
    lv_obj_set_x(mLapLabel, 0);
    lv_obj_set_y(mLapLabel, 40);
    mSessionViewModel.laps.valueChanged().connect([=]() { setLaps(); });

    // Setup best lap time label
    mBestLapLabel = lv_label_create(mScreenContent, nullptr);
    lv_obj_add_style(mBestLapLabel, LV_LABEL_PART_MAIN, &mLabelStyle);
    lv_obj_set_size(mBestLapLabel, lv_obj_get_width(mScreenContent), 16);
    lv_obj_set_x(mBestLapLabel, 128);
    lv_obj_set_y(mBestLapLabel, 40);
    mSessionViewModel.bestlap.valueChanged().connect([=]() { setBestLap(); });

    // Load initial values of model.
    setTrackName();
    setDate();
    setTime();
    setLaps();
    setBestLap();
}

SessionView::~SessionView()
{
    lv_obj_del(mTrackNameLabel);
    lv_obj_del(mDateLabel);
    lv_obj_del(mLapLabel);
    lv_obj_del(mTimeLabel);
    lv_obj_del(mBestLapLabel);
}

bool SessionView::handleButtonDown()
{
    mSessionViewModel.handleNavigationDown();
    return true;
}

bool SessionView::handleButtonUp()
{
    mSessionViewModel.handleNavigationUp();
    return true;
}

void SessionView::setTrackName()
{
    lv_label_set_text(mTrackNameLabel, mSessionViewModel.trackName.get().c_str());
}

void SessionView::setDate()
{
    lv_label_set_text(mDateLabel, mSessionViewModel.date.get().c_str());
}

void SessionView::setTime()
{
    lv_label_set_text(mTimeLabel, mSessionViewModel.time.get().c_str());
}

void SessionView::setLaps()
{
    lv_label_set_text_fmt(mLapLabel, "Laps:%s", mSessionViewModel.laps.get().c_str());
}

void SessionView::setBestLap()
{
    lv_label_set_text(mBestLapLabel, mSessionViewModel.bestlap.get().c_str());
}
