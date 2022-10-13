#ifndef __DUMMYLISTVIEW__H__
#define __DUMMYLISTVIEW__H__

#include "ICommand.hpp"
#include "ListView.hpp"
#include "PopupRequest.hpp"

class DummyListView : public ListView
{
public:
    ~DummyListView() = default;
    bool handleEnter() override;
    bool handleEscape() override;
    void setCloseCommand(ICommand *command);

protected:
    virtual std::size_t getRows() const override;
    void displayData(std::size_t row) override;

private:
    ICommand *mCloseCommand{nullptr};
    PopupRequest mPopupRequest;
};

#endif //!__DUMMYLISTVIEW__H__