#include "filereader.h"
#include <QDebug>
FileReader::FileReader(QObject *parent) {
}
FileReader::~FileReader() {

    if(nullptr!=file){
        delete file;
        file=nullptr;
    }
}
QString FileReader::getFileName() {
    return this->filename;
}
void FileReader::setFileName(const QString &filename) {
    this->filename = filename;
    if(nullptr!=file){
        delete file;
        file=nullptr;
    }
    file = new QFile(filename);
}
void FileReader::qmlRegister()
{
    qmlRegisterType<FileReader>("FileReader", 1, 0, "FileReader");
}

QString FileReader::getContent() {
    if( content.length() == 0 ) {
        file->open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(file);
        content = in.readAll();
        if( content.length() == 0) {
            qDebug() << "[Warning] FileReader: file " << this->filename << "is empty" << endl;
        }
    }
    return content;
}
void FileReader::clearContent() {
    content.clear();
}
