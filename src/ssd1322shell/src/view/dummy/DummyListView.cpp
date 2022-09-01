
#include "DummyListView.hpp"

bool DummyListView::handleEnter()
{
    mPopupRequest.setMainText("Dummy text");
    mPopupRequest.setMainText("Set dummy Text2");
    requestPopup.emit(mPopupRequest);

    return true;
}

bool DummyListView::handleEscape()
{
    if (mCloseCommand == nullptr)
    {
        return false;
    }

    mCloseCommand->execute();
    return true;
}

void DummyListView::setCloseCommand(ICommand *command)
{
    mCloseCommand = command;
}

std::size_t DummyListView::getRows() const
{
    return 0;
}

void DummyListView::displayData(std::size_t row)
{
}
