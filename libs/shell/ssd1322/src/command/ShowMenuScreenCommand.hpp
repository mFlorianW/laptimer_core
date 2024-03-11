#ifndef __SHOWMENUSCREENCOMMAND__H__
#define __SHOWMENUSCREENCOMMAND__H__

#include "ICommand.hpp"

class ScreenModel;
class ShowMenuScreenCommand : public ICommand
{
public:
    ShowMenuScreenCommand(ScreenModel& screenModel);
    ~ShowMenuScreenCommand() override = default;

    void execute() override;

private:
    ScreenModel& mScreenModel;
};

#endif //!__SHOWMENUSCREENCOMMAND__H__