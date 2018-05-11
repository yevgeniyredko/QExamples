#ifndef COPIER_H
#define COPIER_H

#include <QtCore>

class Copier : public QObject
{
    Q_OBJECT

public:
    explicit Copier(QObject *parent = 0);   

signals:
    void maximumSet(int value);
    void currentFileChanged(int value);
    void processFinished();
    bool fileExists(QString fileName);

public slots:
    void copyDirectory(QString from, QString to);

private:
    void getFilesList(QDir directory, QStringList &list, QString prefix);
};

#endif // COPIER_H
