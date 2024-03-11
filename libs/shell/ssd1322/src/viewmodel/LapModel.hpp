#ifndef __LAPMODEL_H__
#define __LAPMODEL_H__

#include "TableModel.hpp"
#include <SessionData.hpp>
#include <cstddef>

class LapModel final : public TableModel
{
public:
    LapModel();
    ~LapModel();

    LapModel(LapModel const& ohter) = delete;
    LapModel& operator=(LapModel const& other) = delete;

    LapModel(LapModel&& model) = delete;
    LapModel& operator=(LapModel&& model) = delete;

    void setSessionData(LaptimerCore::Common::SessionData const session) noexcept;

    std::string data(std::size_t row, std::size_t column) const noexcept override;

    std::string headerData(std::size_t column) const noexcept override;

private:
    std::size_t mLapColumnIndex{0};
    std::size_t mLaptimeColumnIndex{1};
    LaptimerCore::Common::SessionData mSession;
};

#endif // __LAPMODEL_H__