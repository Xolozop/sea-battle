#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <sstream>

#include "exceptions.h"

class File {
private:
    std::fstream stream;

    // Копирование и присваивание не реализовано.  Предотвратим их использование,
    // объявив соответствующие методы закрытыми.
    File(const File&);
    File& operator=(const File&);
public:
    File(const char* filename, bool readOnly=true);
    ~File();
    void write(std::string str);
    std::stringstream read();
};

#endif