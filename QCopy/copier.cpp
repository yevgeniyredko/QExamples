#include "copier.h"

Copier::Copier(QObject *parent) : QObject(parent)
{

}

void Copier::getFilesList(QDir directory, QStringList &list, QString prefix = "/")
{
    directory.setFilter(QDir::Dirs | QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot);
    QFileInfoList entryList = directory.entryInfoList();

    foreach (auto file, entryList) {
        if (file.isDir()) {
            getFilesList(QDir(file.absoluteFilePath()), list, prefix + file.fileName() + "/");
        } else {
            list.append(prefix + file.fileName());
        }
    }
}

void Copier::copyDirectory(QString from, QString to)
{
    QStringList filesList;
    getFilesList(QDir(from), filesList);

    emit maximumSet(filesList.length() - 1);

    for (int i = 0; i < filesList.length(); i++) {
        emit currentFileChanged(i);

        QFileInfo file(to + filesList[i]);
        if (!file.exists()) {
            QDir dir;
            dir.mkpath(file.absolutePath());
            QFile::copy(from + filesList[i], to + filesList[i]);
        } else {
            bool toChange = emit fileExists(filesList[i]);
            if (toChange) {
                QFile::remove(to + filesList[i]);
                QFile::copy(from + filesList[i], to + filesList[i]);
            }
        }
    }

    emit processFinished();
}
