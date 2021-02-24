#ifndef OPTIONAL_H
#define OPTIONAL_H

///Class to mimic std::optional.
///We do not use std::experimental::optional,
///because we use C++11
class optional
{
public:
  optional();
  bool has_value() const;
  int value() const;
};

/// Test our optional class
void test_optional();

#endif // OPTIONAL_H
