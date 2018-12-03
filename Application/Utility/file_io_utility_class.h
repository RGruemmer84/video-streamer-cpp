#ifndef FILEIOUTILITY_H
#define FILEIOUTILITY_H

#include <string>
#include <QDebug>
#include <QFile>

using std::string;

/*  FileIOUtility class:
 *
 *  Description:
 *      This class is a generic class that handles all IO to a file in an arbitrary format.
 *      Initially, it will only parse and write csv in key value pairs, i.e. "var_name","var_value" */



class FileIOUtility
{

bool isReadMode;
string fileName;
string filePath;

QFile* file;
QTextStream* stream;
bool isOpen;

public:
    FileIOUtility(string fName, string fPath, bool read);

    void WriteKeyValue(string key, string value);
    QStringList ReadFileLines();
    void finalize();


};

#endif // FILEIOUTILITY_H
