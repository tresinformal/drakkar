#include "environment.h"
#include <cassert>

environment::environment(environment_type enviroment_type)
    : m_environment_type{enviroment_type}

{

}

void test_environment()
{
  // Minimal and maximal coordinats should make sense
  {
    const environment e;
    assert(e.get_min_x() < e.get_max_x());
    assert(e.get_min_y() < e.get_max_y());
  }

  // An environment has a type
  {
    const environment e;
    assert(e.get_type() == environment_type::empty);
    const environment e1(environment_type::quiet);
    assert(e1.get_type() == environment_type::quiet);

  }

}
