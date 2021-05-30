#include "read_only.h"

#include <cassert>
#include <vector>
#include <exception>

bool operator==(const read_only<int>& lhs, const read_only<int>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

bool operator==(const read_only<double>& lhs, const read_only<double>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

bool operator==(const read_only<std::string>& lhs, const read_only<std::string>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

bool operator!=(const read_only<int>& lhs, const read_only<int>& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

bool operator!=(const read_only<double>& lhs, const read_only<double>& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

bool operator!=(const read_only<std::string>& lhs, const read_only<std::string>& rhs) noexcept
{
    return lhs.get() != rhs.get();
}

bool operator<(const read_only<int>& lhs, const read_only<int>& rhs) noexcept
{
    return lhs.get() < rhs.get();
}

bool operator<(const read_only<double>& lhs, const read_only<double>& rhs) noexcept
{
    return lhs.get() < rhs.get();
}

bool operator<(const read_only<std::string>& lhs, const read_only<std::string>& rhs) noexcept
{
    return lhs.get() < rhs.get();
}

bool operator>(const read_only<int>& lhs, const read_only<int>& rhs) noexcept
{
    return lhs.get() > rhs.get();
}

bool operator>(const read_only<double>& lhs, const read_only<double>& rhs) noexcept
{
    return lhs.get() > rhs.get();
}

bool operator>(const read_only<std::string>& lhs, const read_only<std::string>& rhs) noexcept
{
    return lhs.get() > rhs.get();
}

bool operator<=(const read_only<int>& lhs, const read_only<int>& rhs) noexcept
{
    return lhs.get() <= rhs.get();
}

bool operator<=(const read_only<double>& lhs, const read_only<double>& rhs) noexcept
{
    return lhs.get() <= rhs.get();
}

bool operator<=(const read_only<std::string>& lhs, const read_only<std::string>& rhs) noexcept
{
    return lhs.get() <= rhs.get();
}

bool operator>=(const read_only<int>& lhs, const read_only<int>& rhs) noexcept
{
    return lhs.get() >= rhs.get();
}

bool operator>=(const read_only<double>& lhs, const read_only<double>& rhs) noexcept
{
    return lhs.get() >= rhs.get();
}

bool operator>=(const read_only<std::string>& lhs, const read_only<std::string>& rhs) noexcept
{
    return lhs.get() >= rhs.get();
}

void test_read_only()
{
#ifndef NDEBUG // no tests in release
    read_only<int> x(314); // Can only determine value at construction
    assert(x.get() == 314); // Can only get, not set
    read_only<int> x_again = x; // Can copy
    assert(x.get() == x_again.get());
    assert(x == x_again); // Can compare for equality
    read_only<int> x_other(271);
    assert(x != x_other); // Can compare for inequality
    assert(x > x_other);  // Can compare
    assert(x >= x_other); // Can compare
    assert(x_other < x);  // Can compare
    assert(x_other <= x); // Can compare

    read_only<double> y(3.14);
    assert(y.get() == 3.14);

    read_only<std::string> s("pi");
    assert(s.get() == "pi");
#endif
}


