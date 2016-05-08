#include "vertexabsencemultigraphexception.h"

VertexAbsenceMultigraphException::VertexAbsenceMultigraphException(const std::string &message):AbsenceMultigraphException(message)
{
}

const char* VertexAbsenceMultigraphException::what() const throw()
{
    std::string main = "В мультиграфе отсутствует указанная вершина.";
    main += message;
    return main.c_str();
}
