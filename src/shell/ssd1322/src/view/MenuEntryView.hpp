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

private:
    ICommand *mNavigationMainScreenCommand{nullptr};

    lv_style_t mEntryLabelStyle;
    lv_obj_t *mEntryLabel;
    lv_style_t mSecondaryEntryLabelStyle;
    lv_obj_t *mSecondaryEnrtyLabel;

    std::string mEntryLabelText;
    std::string mSecondaryEntryLabelText;
};

#endif //!__MENUENTRYVIEW__H__
