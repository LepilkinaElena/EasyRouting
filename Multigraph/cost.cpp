#include "cost.h"

using namespace Multigraph;

Cost::Cost()
{
}

Cost::~Cost()
{

}

Cost* Cost::operator+(const Cost& other) const
{
    return nullptr;
}

Cost Cost::operator-(const Cost& other) const
{
    return *this;
}

bool Cost::operator<=(const Cost& other) const
{
    return false;
}

bool Cost::operator>(const Cost& other) const
{
    return false;
}

bool Cost::operator==(const Cost& other) const
{
    return false;
}

bool Cost::operator>=(const Cost& other) const
{
    return false;
}

bool Cost::operator<(const Cost& other) const
{
    return false;
}

std::ostream& Cost::save(std::ostream& output) const {
    return output;
}

std::istream& Cost::load(std::istream& input) {
    return input;
}
