#include "utils.h"

bool are_equal(const double a, const double b, const double tolerance)
{
    return std::abs(a - b) < tolerance;
}

void test_utils()
{
#ifndef NDEBUG // no tests in release

  // (594) Equality between doubles can be checked, with some tolerance
  {
    assert(are_equal(0.0, 0.0));
    assert(!are_equal(0.0, 0.1));
    assert(!are_equal(0.00001, 0.00002, 0.000001));
    assert(are_equal(0.0001, 0.0002, 0.001));
  }

  #endif // NDEBUG
}
