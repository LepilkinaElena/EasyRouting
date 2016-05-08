#ifndef VERTEXABSENCEMULTIGRAPHEXCEPTION_H
#define VERTEXABSENCEMULTIGRAPHEXCEPTION_H

#include "absencemultigraphexception.h"

class VertexAbsenceMultigraphException : public AbsenceMultigraphException
{
public:
    explicit VertexAbsenceMultigraphException(const std::string& message = "");
    const char* what() const throw();
};

#endif // VERTEXABSENCEMULTIGRAPHEXCEPTION_H
