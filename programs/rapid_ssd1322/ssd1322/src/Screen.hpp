// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "CloseCommand.hpp"
#include "IOpenCloseHandler.hpp"
#include "OpenCommand.hpp"
#include "PopupView.hpp"
#include "View.hpp"
#include <lvgl.h>

class Screen : public IOpenCloseHandler
{
public:
    virtual ~Screen();

    // Delete copy constructor
    Screen(Screen const&) = delete;

    // Delete copy assignment operator
    Screen& operator=(Screen const&) = delete;

    // Delete move constructor
    Screen(Screen&&) = delete;

    // Delete move assignment operator
    Screen& operator=(Screen&&) = delete;

    lv_obj_t* getScreen() const;

    void open() override;
    void close() override;

    void setScreenContent(View* content);

    /**
     * Gives the visibility of the screen.
     * @return True screen is shown to the user otherwise false.
     */
    bool isVisible() const noexcept;

protected:
    Screen();
    static void handleLvglEvent(lv_obj_t* obj, lv_event_t event);

protected:
    lv_obj_t* m_screen;
    View* mActiveView{nullptr};

private:
    void closePopup(PopupReturnType popupReturnType);
    void onPopupRequested(PopupRequest const& popupRequest);
    void restoreParent();
    /**
     * Sets the visibility of screen.
     * @param visible The new visibility of the screen.
     */
    void setVisible(bool const visible) noexcept;

private:
    friend class ScreenModel;
    lv_style_t mScreenStyle{};
    lv_obj_t* mOldScreenContentParent{nullptr};

    bool mVisible{false};

    // Popup View Handling
    bool mPopupActive{false};
    KDBindings::ConnectionHandle mPopupRequestConnectionHandle;
    PopupRequest const* mPopupRequest{nullptr};
    PopupView mPopupView;
    CloseCommand mPopupCloseCommand;
    OpenCommand mPopupConfirmCommand;
    lv_obj_t* mOldPopupParent{nullptr};
};
