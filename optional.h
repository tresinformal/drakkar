#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <vector>
#include <iostream>

///Class to mimic std::optional.
///We do not use std::experimental::optional,
///because we use C++11
template <class T> class optional
{
public:
  optional() : m_value{std::vector<T>()} {};
  optional(const T& value) : m_value{std::vector<T>(1, value)} {};

  bool has_value() const { return !m_value.empty(); };

  T value() const {
    if(!this->has_value())
      {
        throw std::logic_error("this object does not contain a value!\n");
      }
    return m_value[0];
  };

  void operator=( const T& value ) { m_value[0] = value; };
private:
  std::vector<T> m_value;
};

/// Test our optional class
void test_optional();

#endif // OPTIONAL_H
