#ifndef __CLOSECOMMAND__H__
#define __CLOSECOMMAND__H__

#include "ICommand.hpp"
#include "IOpenCloseHandler.hpp"

class CloseCommand : public ICommand
{
public:
    CloseCommand(IOpenCloseHandler &handler);

    void execute() override;

private:
    IOpenCloseHandler &mHandler;
};

#endif //!__CLOSECOMMAND__H__