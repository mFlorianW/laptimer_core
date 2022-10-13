#ifndef __SETTINGSVIEW__H__
#define __SETTINGSVIEW__H__

#include "ICommand.hpp"
#include "View.hpp"
#include <lvgl.h>

enum Type
{
    NoConfirmation,
    Confirmattion
};

class PopupView : public View
{
public:
    PopupView();
    ~PopupView();

    void setCloseCommand(ICommand *command);

    bool handleEnter() override;
    bool handleEscape() override;

    void setMainText(const std::string &mainText);
    void setSecondaryText(const std::string &secondaryText);

    /**
     * Sets
     * @param type
     */
    void setType(Type type);

private:
    ICommand *mCloseCommand{nullptr};
    Type mType = Type::Confirmattion;
    lv_style_t mLabelStyle;
    lv_obj_t *mConfirmLabel;
    lv_obj_t *mCancelLabel;

    lv_obj_t *mMainText;
    lv_obj_t *mSecondaryText;
};

#endif //!__SETTINGSVIEW__H__