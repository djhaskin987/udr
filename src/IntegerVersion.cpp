#include "IntegerVersion.hpp"
#include <memory>

UDR::IntegerVersion::IntegerVersion(int val) :
    ver(val)
{ }

UDR::IntegerVersion::~IntegerVersion()
{ }

int UDR::IntegerVersion::compare(const ConstVersionPtr & other) const
{
    const IntegerVersion * other_ptr;
    other_ptr = dynamic_cast<const IntegerVersion*>(other.get());
    if (other_ptr == nullptr)
    {
        throw UDR::VersionMismatchException();
    }

    return (this->ver) - (other_ptr->ver);
}

bool UDR::IntegerVersion::matches(const ConstVersionPtr & other) const
{
    const IntegerVersion * other_ptr;
    if (! (other_ptr =
            dynamic_cast<const IntegerVersion*>(other.get())))
    {
        throw UDR::VersionMismatchException();
    }
    return (other_ptr->ver / 10) == (this->ver / 10);
}

UDR::ConstVersionPtr UDR::IntegerVersion::Create(int val)
{
    return std::unique_ptr<const Version>(
            static_cast<const Version*>(new IntegerVersion(val)));
}

