#include "LapModel.hpp"
#include <string>

LapModel::LapModel() = default;
LapModel::~LapModel() = default;

void LapModel::setSessionData(const LaptimerCore::Common::SessionData session) noexcept
{
    mSession = session;
    mLaptimeColumnIndex = 2 + mSession.getTrack().getNumberOfSections();
    setRowCount(mSession.getNumberOfLaps());
    setColumnCont(mSession.getTrack().getNumberOfSections() + 3);
}

std::string LapModel::data(std::size_t row, std::size_t column) const noexcept
{
    // If the index is out bound return an empty string.
    if (row >= getRowCount())
    {
        return {};
    }

    // First column is the lap index and that is equal to the row.
    const auto lap = mSession.getLaps().at(row);
    if (column == mLapColumnIndex)
    {
        return std::to_string(row + 1);
    }
    else if (column == mLaptimeColumnIndex)
    {
        return lap.getLaptime().asString().erase(0, 3);
    }
    else
    {

        return lap.getSectorTime(column - 1)->asString().erase(0, 3);
    }
}

std::string LapModel::headerData(std::size_t column) const noexcept
{
    // Out of bounds check
    if (column >= getColumnCount())
    {
        return {};
    }

    if (column == mLapColumnIndex)
    {
        return std::string{"Lap"};
    }
    else if (column == mLaptimeColumnIndex)
    {
        return std::string{"Laptime"};
    }
    else
    {
        return std::string{"S"} + std::to_string(column);
    }
}