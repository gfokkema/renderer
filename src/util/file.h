#ifndef UTIL_FILE_H_
#define UTIL_FILE_H_

#include "common.h"

namespace util
{

class File
{
public:
    File(std::string path);
    ~File();

    std::string read();
private:
    std::ifstream stream;
};

}

#endif /* UTIL_FILE_H_ */
