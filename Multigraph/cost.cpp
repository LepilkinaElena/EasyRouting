#include "cost.h"

using namespace Multigraph;

Cost::Cost()
{
}

Cost Cost::operator+(const Cost& other)
{
    return *this;
}

Cost Cost::operator-(const Cost& other)
{
    return *this;
}

bool Cost::operator<(const Cost& other)
{
    return false;
}

bool Cost::operator>(const Cost& other)
{
    return false;
}

bool Cost::operator==(const Cost& other)
{
    return false;
}

bool Cost::operator>=(const Cost& other)
{
    return false;
}

bool Cost::operator<=(const Cost& other)
{
    return false;
}
