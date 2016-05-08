#include "edgeabsencemultigraphexception.h"

EdgeAbsenceMultigraphException::EdgeAbsenceMultigraphException(const std::string &message): AbsenceMultigraphException(message)
{
}

const char* EdgeAbsenceMultigraphException::what() const throw()
{
    std::string main = "В мультиграфе отсутствует указанная дуга.";
    main += message;
    return main.c_str();
}
