#include "textconverter.h"

TextConverter::TextConverter(QObject *parent) : QObject(parent)
{

}

void TextConverter::convertTextFiles(QString path)
{
    auto win1251codec = QTextCodec::codecForName("Windows-1251");
    auto UTF8codec = QTextCodec::codecForName("UTF-8");

    auto txtFilesList = getTxtFiles(QDir(path));
    emit maximumSet(txtFilesList.count() - 1);

    for(int i = 0; i < txtFilesList.count(); i++) {
        emit currentFileChanged(i);

        QFile file(QString("%1/%2").arg(path).arg(txtFilesList[i]));
        file.open(QFile::ReadOnly | QFile::Text);
        auto fileText = file.readAll();
        auto unicodeString = win1251codec->toUnicode(fileText);
        file.close();
        file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text);
        file.write(UTF8codec->fromUnicode(unicodeString));
        file.close();
    }

    emit processFinished();
}

QStringList TextConverter::getTxtFiles(QDir path)
{
    return path.entryList(QStringList("*.txt"), QDir::Files);
}
