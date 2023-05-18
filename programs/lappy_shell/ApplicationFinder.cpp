#include "ApplicationFinder.hpp"
#include <QDirIterator>
#include <QFileInfo>

namespace LaptimerCore::LappyShell
{

ApplicationFinder::ApplicationFinder(QStringList appDirs)
    : mAppDirs{std::move(appDirs)}
{
}

QVector<QFileInfo> ApplicationFinder::findApplications() const noexcept
{
    auto applications = QVector<QFileInfo>{};
    for (const auto &appDir : mAppDirs)
    {
        auto dirIter = QDirIterator{appDir, QDirIterator::Subdirectories};
        while (dirIter.hasNext())
        {
            dirIter.next();
            if (dirIter.fileInfo().isFile() and dirIter.fileInfo().completeSuffix() == QStringLiteral(".json"))
            {
                applications.push_back(dirIter.filePath());
            }
        }
    }

    return applications;
}

} // namespace LaptimerCore::LappyShell
