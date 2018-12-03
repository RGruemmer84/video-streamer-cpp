#include "file_io_utility_class.h"


#include "file_io_utility_class.h"
#include <QFile>


FileIOUtility::FileIOUtility(string fName, string fPath, bool read)
{
    fileName = fName;
    filePath = fPath;
    isReadMode = read;

    file = new QFile(QString::fromStdString( filePath + "/" + fileName ));

    if (isReadMode)
    {
        isOpen = file->open(QIODevice::ReadOnly);
    }
    else
    {
        isOpen = file->open(QIODevice::WriteOnly);
    }

    stream = new QTextStream(file);

}

void FileIOUtility::finalize()
{
    file->close();
}

void FileIOUtility::WriteKeyValue(string key, string value)
{
    if (isOpen) *stream << QString::fromStdString(key + "," + value + "\n");
}

QStringList FileIOUtility::ReadFileLines()
{
    QStringList wordList;
    if (isOpen)
    {
        while (!file->atEnd())
        {
            QByteArray line = file->readLine();
            wordList.append(line);
        }
        finalize();
    }
    return wordList;

}
