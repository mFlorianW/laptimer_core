#ifndef VIEW_HPP
#define VIEW_HPP

#include "ICommand.hpp"
#include "PopupRequest.hpp"
#include <kdbindings/signal.h>
#include <lvgl.h>

class View
{
public:
    virtual ~View();

    /**
     * Gives the screen context for rendering.
     * @return A object that contains the screen context to render.
     */
    lv_obj_t* get_screen_content() const;

    /**
     * This function is called when the user presses the down button.
     * The default implementation calls the set commands when it set otherwise the does nothing.
     */
    virtual void handleButtonDown();

    /**
     * This function is called when the user presses the up button.
     * The default implementation calls the set commands when it set otherwise the does nothing.
     */
    virtual void handleButtonUp();

    /**
     * This function is called when the user presses the escape button.
     * The default implementation calls the set commands when it set otherwise the does nothing.
     */
    virtual void handleEscape();

    /**
     * This function is called when the user presses the enter button.
     * The default implementation calls the set commands when it set otherwise the does nothing.
     */
    virtual void handleEnter();

    /**
     * Sets the command which is called, when the button down handler is called.
     * @param command The command to call on button down.
     */
    void setNavigateUpCommand(ICommand* command);

    /**
     * Sets the command which is called, when the button down handler is called.
     * @param command The command to call on button down.
     */
    void setNavigateDownCommand(ICommand* command);

    /**
     * Sets the command which is called, when the button down handler is called.
     * @param command The command to call on button down.
     */
    void setOpenCommand(ICommand* command);

    /**
     * Sets the command which is called, when the button down handler is called.
     * @param command The command to call on button down.
     */
    void setCloseCommand(ICommand* command);

    /**
     * This signal is emitted by the View when the shell display a popup window.
     * @param popupRequest The information about the request which kind of popup and text for the popup.
     */
    KDBindings::Signal<PopupRequest const&> requestPopup;

    /**
     * Gives visible state of the view.
     * @return True means view is display to the user otherwise false.
     */
    bool isVisible() const;

private:
    void setVisible(bool visible) noexcept;

    friend class Screen;
    lv_style_t mScreenContentStyle{};
    lv_obj_t* mBackScreen;
    bool mVisible;

protected:
    View();
    ICommand* mUpCommand{nullptr};
    ICommand* mDownCommand{nullptr};
    ICommand* mEnterCommand{nullptr};
    ICommand* mEscapeCommand{nullptr};
    lv_obj_t* mScreenContent;
};

#endif //! VIEW_HPP
