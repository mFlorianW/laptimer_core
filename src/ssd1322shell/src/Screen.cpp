#include "Screen.hpp"
#include "../include/ScreenModel.hpp"
#include <cstdio>
#include <lv_obj.h>

Screen::Screen()
    : m_screen{lv_obj_create(nullptr, nullptr)}
    , mPopupCloseCommand{*this}
{
    // setup screen
    lv_style_init(&m_screen_style);
    lv_obj_set_size(m_screen, 256, 64);
    lv_style_set_bg_color(&m_screen_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_add_style(m_screen, LV_OBJ_PART_MAIN, &m_screen_style);

    // setup event handling
    lv_obj_set_event_cb(m_screen, Screen::handleLvglEvent);
    lv_obj_set_user_data(m_screen, this);

    mPopupView.setCloseCommand(&mPopupCloseCommand);
}

Screen::~Screen()
{
    lv_obj_del(m_screen);
}

lv_obj_t *Screen::getScreen() const
{
    return m_screen;
}

void Screen::open()
{
    if (mPopupRequest == nullptr)
    {
        return;
    }

    printf("Close popup confirmed\n");
    closePopup(PopupReturnType::Confirmed);
}

void Screen::close()
{
    if (mPopupRequest == nullptr)
    {
        return;
    }

    printf("Close popup canceld\n");
    closePopup(PopupReturnType::Cancled);
}

void Screen::setScreenContent(View *content)
{
    // Restore old parent otherwise the Screen may contain
    // old objects.
    if (mOldScreenContentParent != nullptr && mActiveView != nullptr)
    {
        lv_obj_set_parent(mActiveView->get_screen_content(), mOldScreenContentParent);
        mActiveView->requestPopup.disconnect(mPopupRequestConnectionHandle);
    }

    mOldScreenContentParent = lv_obj_get_parent(content->get_screen_content());
    lv_obj_set_parent(content->get_screen_content(), m_screen);
    lv_event_send_refresh_recursive(m_screen);
    mActiveView = content;
    mPopupRequestConnectionHandle = mActiveView->requestPopup.connect(&Screen::onPopupRequested, this);
}

void Screen::handleLvglEvent(lv_obj_t *obj, lv_event_t event)
{
    if (event != LV_EVENT_KEY)
    {
        return;
    }

    auto *screen = static_cast<Screen *>(lv_obj_get_user_data(obj));
    auto *view = screen->mPopupActive ? &screen->mPopupView : screen->mActiveView;
    const auto *keyType = static_cast<const lv_key_t *>(lv_event_get_data());
    if (view && *keyType == LV_KEY_ENTER)
    {
        view->handleEnter();
    }
    else if (view && *keyType == LV_KEY_ESC)
    {
        view->handleEscape();
    }
    else if (view && *keyType == LV_KEY_UP)
    {
        view->handleButtonUp();
    }
    else if (view && *keyType == LV_KEY_DOWN)
    {
        view->handleButtonDown();
    }
    else
    {
        printf("Unsupported key event. key type: %d", *keyType);
    }
}

void Screen::closePopup(PopupReturnType popupReturnType)
{
    mPopupActive = false;
    // TODO: Cleanup PopupView
    mPopupView.setMainText("");
    mPopupView.setSecondaryText("");
    mPopupRequest->confirmed.emit(popupReturnType);
    lv_obj_set_parent(mPopupView.get_screen_content(), mOldPopupParent);
}

void Screen::onPopupRequested(const PopupRequest &popupRequest)
{
    mPopupActive = true;
    mPopupRequest = &popupRequest;
    mOldPopupParent = lv_obj_get_parent(mPopupView.get_screen_content());
    mPopupView.setMainText(mPopupRequest->getMainText());
    mPopupView.setSecondaryText(mPopupRequest->getSecondaryText());
    lv_obj_set_parent(mPopupView.get_screen_content(), lv_layer_top());
}
