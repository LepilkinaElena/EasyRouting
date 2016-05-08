#include "nullpointerexception.h"

NullPointerException::NullPointerException(const std::string &message): message(message)
{
}

const char* NullPointerException::what() const throw()
{
    std::string main = "Указатель нулевой";
    main += message;
    return main.c_str();
}
