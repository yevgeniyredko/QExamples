#ifndef TEXTCONVERTER_H
#define TEXTCONVERTER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QTextCodec>

class TextConverter : public QObject
{
    Q_OBJECT

public:
    explicit TextConverter(QObject *parent = 0);

public slots:
    void convertTextFiles(QString path);

signals:
    void maximumSet(int value);
    void currentFileChanged(int value);
    void processFinished();

private:
    QStringList getTxtFiles(QDir path);
};

#endif // TEXTCONVERTER_H
