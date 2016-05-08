#include "absencemultigraphexception.h"

AbsenceMultigraphException::AbsenceMultigraphException(const std::string& message): message(message)
{
}

const char* AbsenceMultigraphException::what() const throw()
{
    std::string main = "В мультиграфе отсутствует указанный элемент.";
    main += message;
    return main.c_str();
}
