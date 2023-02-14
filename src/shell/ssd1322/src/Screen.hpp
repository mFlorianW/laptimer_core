#ifndef __SCREEN__H__
#define __SCREEN__H__

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

    lv_obj_t *getScreen() const;

    void open() override;
    void close() override;

    void setScreenContent(View *content);

    /**
     * Gives the visibility of the screen.
     * @return True screen is shown to the user otherwise false.
     */
    bool isVisible() const noexcept;

protected:
    Screen();
    static void handleLvglEvent(lv_obj_t *obj, lv_event_t event);

protected:
    lv_obj_t *m_screen;
    View *mActiveView{nullptr};

private:
    void closePopup(PopupReturnType popupReturnType);
    void onPopupRequested(const PopupRequest &popupRequest);
    void restoreParent();
    /**
     * Sets the visibility of screen.
     * @param visible The new visibility of the screen.
     */
    void setVisible(const bool visible) noexcept;

private:
    friend class ScreenModel;
    lv_style_t mScreenStyle{};
    lv_obj_t *mOldScreenContentParent{nullptr};

    bool mVisible{false};

    // Popup View Handling
    bool mPopupActive{false};
    KDBindings::ConnectionHandle mPopupRequestConnectionHandle;
    const PopupRequest *mPopupRequest{nullptr};
    PopupView mPopupView;
    CloseCommand mPopupCloseCommand;
    OpenCommand mPopupConfirmCommand;
    lv_obj_t *mOldPopupParent{nullptr};
};

#endif //!__SCREEN__H__
