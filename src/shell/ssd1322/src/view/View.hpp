#ifndef __SCREEN_CONTENT__H__
#define __SCREEN_CONTENT__H__

#include "ICommand.hpp"
#include "PopupRequest.hpp"
#include <kdbindings/signal.h>
#include <lvgl.h>

class View
{
public:
    virtual ~View();

    lv_obj_t *get_screen_content() const;

    virtual bool handleButtonDown();
    virtual bool handleButtonUp();
    virtual bool handleEscape();
    virtual bool handleEnter();

    virtual void setCloseCommand(ICommand *command);

    KDBindings::Signal<const PopupRequest &> requestPopup;

private:
    lv_style_t mScreenContentStyle;
    lv_obj_t *mBackScreen;

protected:
    View();
    ICommand *mCloseCommand{nullptr};
    lv_obj_t *mScreenContent;
};

#endif //!__SCREEN_CONTENT__H__
