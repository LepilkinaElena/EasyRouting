#ifndef NULLPOINTEREXCEPTION_H
#define NULLPOINTEREXCEPTION_H

#include <exception>
#include <string>

class NullPointerException : public std::exception
{
private:
    std::string message;
public:
    explicit NullPointerException(const std::string& message);
    const char* what() const throw();
};

#endif // NULLPOINTEREXCEPTION_H
