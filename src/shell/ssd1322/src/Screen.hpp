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

protected:
    Screen();
    static void handleLvglEvent(lv_obj_t *obj, lv_event_t event);

protected:
    lv_obj_t *m_screen;
    View *mActiveView{nullptr};

private:
    void closePopup(PopupReturnType popupReturnType);
    void onPopupRequested(const PopupRequest &popupRequest);

private:
    lv_style_t m_screen_style;
    lv_obj_t *mOldScreenContentParent{nullptr};

    // Popup View Handling
    bool mPopupActive{false};
    KDBindings::ConnectionHandle mPopupRequestConnectionHandle;
    const PopupRequest *mPopupRequest{nullptr};
    PopupView mPopupView;
    CloseCommand mPopupCloseCommand;
    OpenCommand mPopupConfirmCommand;
    lv_obj_t *mOldPopupParent;
};

#endif //!__SCREEN__H__
