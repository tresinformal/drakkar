#include <vector>
#include <iostream>

template <class T> class read_only
{
public:
  read_only() : m_value{std::vector<T>()} {};
  read_only(const T value) : m_value{std::vector<T>(1, value)} {};

  bool has_value() const { return !m_value.empty(); };

  T value() const {
    if(!this->has_value())
      {
        throw std::logic_error("this object does not contain a value!\n");
      }
    return m_value[0];
  };

  void operator=( const T value ) { m_value[0] = value; };

  T get() const noexcept { return m_value; };

private:
  std::vector<T> m_value;
};

/// Test our read_only class
void test_read_only();
