#ifndef POPUPVIEW_HPP
#define POPUPVIEW_HPP

#include "PopupViewDefinition.hpp"
#include "View.hpp"
#include <lvgl.h>

class PopupView final : public View
{
public:
    /**
     * Contructs an PopupView instance and creates the label for the view.
     */
    PopupView();

    /**
     * Cleanup labels.
     */
    ~PopupView() override;

    /**
     * Deleted copy constructor
     */
    PopupView(const PopupView &other) = delete;

    /**
     * Deleted copy assignment operator
     */
    PopupView &operator=(const PopupView &other) = delete;

    /**
     * Deleted move operator
     */
    PopupView(PopupView &&other) = delete;

    /**
     * Deleted move assignment operator
     */
    PopupView &operator=(PopupView &&other) = delete;

    /**
     * Handles the enter key press sets the return type of the popup if it's modal.
     */
    void handleEnter() override;

    /**
     * Handles the enter key press sets the return type of the popup if it's modal.
     */
    void handleEscape() override;

    /**
     * Sets the main text in popup.
     * @param mainText The text that is displayed in the upper line.
     */
    void setMainText(const std::string &mainText);

    /**
     * Sets the secondary text in the popup. This text should be used to display addiontial information.
     * @param secondaryText The text that is display below the main text in smaller font size.
     */
    void setSecondaryText(const std::string &secondaryText);

    /**
     * Sets
     * @param type
     */
    void setType(Type type);

private:
    Type mType = Type::Confirmattion;
    lv_style_t mLabelStyle;
    lv_obj_t *mConfirmLabel;
    lv_obj_t *mCancelLabel;

    lv_obj_t *mMainText;
    lv_obj_t *mSecondaryText;
};

#endif //! POPUPVIEW_HPP
