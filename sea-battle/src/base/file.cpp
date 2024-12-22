#include "file.h"

File::File(const char* filename, bool readOnly) {
    if (readOnly)
        stream.open(filename);
    else 
        stream.open(filename, std::fstream::out);

    if (!stream.is_open())
        throw fileWriteException();
}

File::~File() {
    if (stream.is_open())
        stream.close();
}

void File::write(std::string str) {
    stream << str;
}

std::stringstream File::read() {
    std::stringstream res;
    res << stream.rdbuf();
    return res;
}