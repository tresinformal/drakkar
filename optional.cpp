#include "optional.h"

#include <cassert>
#include <vector>
#include <exception>

void test_optional()
{
  // Initialize with a value
  {
    const int value = 42;
    const optional<int> x = value;
    assert(x.has_value());
    assert(x.value() == value);
  }
  // Reset the value
  {
    const int value = 42;
    optional<int> x = value * 2;
    assert(x.value() != value);
    x = value;
    assert(x.value() == value);
  }
  // No value
  #define FIX_ISSUE_189
  #ifdef FIX_ISSUE_189
  {
    const optional<int> x;
    assert(!x.has_value());
    try
    {
      x.value();
      assert(!"Should not get here: there is no value");
    }
    catch (const std::exception&)
    {
      //Great! x should throw, as there is no value
    }
  }
  #endif // FIX_ISSUE_189
}


