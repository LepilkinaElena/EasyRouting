#include "cost.h"

Cost::Cost()
{
}

Cost& Cost::operator+(Cost& other)
{
    return *this;
}

Cost& Cost::operator-(Cost& other)
{
    return *this;
}

bool Cost::operator<(Cost& other)
{
    return false;
}

bool Cost::operator>(Cost& other)
{
    return false;
}

bool Cost::operator==(Cost& other)
{
    return false;
}

bool Cost::operator>=(Cost& other)
{
    return false;
}

bool Cost::operator<=(Cost& other)
{
    return false;
}
