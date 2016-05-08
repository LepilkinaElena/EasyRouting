#ifndef EDGEABSENCEMULTIGRAPHEXCEPTION_H
#define EDGEABSENCEMULTIGRAPHEXCEPTION_H

#include "absencemultigraphexception.h"

class EdgeAbsenceMultigraphException : public AbsenceMultigraphException
{
public:
    explicit EdgeAbsenceMultigraphException(const std::string& message = "");
    const char* what() const throw();
};

#endif // EDGEABSENCEMULTIGRAPHEXCEPTION_H
