#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <vector>

///Class to mimic std::optional.
///We do not use std::experimental::optional,
///because we use C++11
class optional
{
public:
  optional(const int value);
  bool has_value() const;
  int value() const;
private:
  std::vector<int> m_value;
};

/// Test our optional class
void test_optional();

#endif // OPTIONAL_H
