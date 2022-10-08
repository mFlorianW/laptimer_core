#ifndef CSVGPSFILEREADER_HPP
#define CSVGPSFILEREADER_HPP

#include <PositionData.hpp>
#include <QString>
#include <vector>

namespace LaptimerCore::QtShell
{

class CsvGpsFileReader
{
public:
    void setFileName(const QString &fileName);

    bool read();

    std::vector<Common::PositionData> getPostions() const noexcept;

private:
    QString mFileName;
    std::vector<Common::PositionData> mPositions;
};

} // namespace LaptimerCore::QtShell

#endif // CSVGPSFILEREADER_HPP
