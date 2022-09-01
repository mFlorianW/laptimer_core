#ifndef __MENUENTRYVIEW__H__
#define __MENUENTRYVIEW__H__

#include "ICommand.hpp"
#include "View.hpp"
#include <string>

class MenuEntryView : public View
{
public:
    MenuEntryView();
    ~MenuEntryView() override;

    void setEntryLabel(const std::string &entryLabel);
    void setSecondaryLabel(const std::string &entryLabel);

    bool handleEscape() final;
    bool handleButtonUp() final;
    bool handleButtonDown() final;
    bool handleEnter() final;

    void setNavigateUpCommand(ICommand *command);
    void setNavigateDownCommand(ICommand *command);
    void setOpenCommand(ICommand *command);
    void setCloseCommand(ICommand *command);

private:
    ICommand *mNavigationMainScreenCommand{nullptr};
    ICommand *mNavigateUpCommand{nullptr};
    ICommand *mNavigateDownCommand{nullptr};
    ICommand *mOpenCommand{nullptr};
    ICommand *mCloseCommand{nullptr};

    lv_style_t mEntryLabelStyle;
    lv_obj_t *mEntryLabel;
    lv_style_t mSecondaryEntryLabelStyle;
    lv_obj_t *mSecondaryEnrtyLabel;

    std::string mEntryLabelText;
    std::string mSecondaryEntryLabelText;
};

#endif //!__MENUENTRYVIEW__H__