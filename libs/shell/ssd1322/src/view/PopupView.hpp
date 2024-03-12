// SPDX-FileCopyrightText: 2024 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef POPUPVIEW_HPP
#define POPUPVIEW_HPP

#include "PopupViewDefinition.hpp"
#include "Timer.hpp"
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
    PopupView(PopupView const& other) = delete;

    /**
     * Deleted copy assignment operator
     */
    PopupView& operator=(PopupView const& other) = delete;

    /**
     * Deleted move operator
     */
    PopupView(PopupView&& other) = delete;

    /**
     * Deleted move assignment operator
     */
    PopupView& operator=(PopupView&& other) = delete;

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
    void setMainText(std::string const& mainText);

    /**
     * Sets the secondary text in the popup. This text should be used to display addiontial information.
     * @param secondaryText The text that is display below the main text in smaller font size.
     */
    void setSecondaryText(std::string const& secondaryText);

    /**
     * Gives the type of the popup.
     * @return The type of the popup.
     */
    Type getType() const;

    /**
     * Sets the type of the popup view.
     * @param type The type of the popup.
     */
    void setType(Type type);

    /**
     * Sets the timeout for popup when it shall be closed automatically. The timeout take only effect when the popup
     * type is set to no confirmation otherwise the timeout is ignored.
     * @param timeout The timeout for auto closing.
     */
    void setAutoClosingTimeout(std::chrono::seconds timeout);

private:
    Type mType = Type::Confirmattion;
    lv_style_t mLabelStyle{};
    lv_obj_t* mConfirmLabel{nullptr};
    lv_obj_t* mCancelLabel{nullptr};

    lv_obj_t* mMainText{nullptr};
    lv_obj_t* mSecondaryText{nullptr};
    LaptimerCore::System::Timer mAutoClosingTimer;
};

#endif //! POPUPVIEW_HPP
