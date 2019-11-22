#include "environment.h"
#include<assert.h>

environment::environment()
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
  #ifdef FIX_ISSUE_95
  // An environment has a type
  {
    const environment e;
    assert(e.get_type() == environment_type::empty );
  }
  #endif // FIX_ISSUE_95
}
