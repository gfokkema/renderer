#include "file.h"

util::File::File(std::string path)
: stream(path, std::ios::in)
{
    if(!this->stream.is_open())
        throw BaseException("Failed to open file: " + path);
}

util::File::~File()
{
    if (this->stream.is_open()) this->stream.close();
}

std::string
util::File::read()
{
    std::string text;
    std::string line = "";
    while(getline(this->stream, line))
    {
        text += "\n" + line;
    }

    return text;
}
