#ifndef ABSENCEMULTIGRAPHEXCEPTION_H
#define ABSENCEMULTIGRAPHEXCEPTION_H

#include <exception>
#include <string>

class AbsenceMultigraphException : public std::exception
{
private:
    std::string message;
public:
    explicit AbsenceMultigraphException(const std::string& message);
    const char* what() const throw();
};

#endif // ABSENCEMULTIGRAPHEXCEPTION_H
