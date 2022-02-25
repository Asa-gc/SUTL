#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QQmlEngine>
class FileReader : public QObject
{
    Q_OBJECT
public:
    static void qmlRegister();
    Q_PROPERTY(QString content READ getContent)
    Q_PROPERTY(QString filename READ getFileName WRITE setFileName)
    Q_INVOKABLE QString getContent();
    Q_INVOKABLE QString getFileName();
    FileReader(QObject *parent = 0);
    ~FileReader();
private:
    QFile   *file=nullptr;
    QString content;
    QString filename;
public slots:
    void setFileName(const QString& filename);
    void clearContent();
};

#endif // FILEREADER_H
