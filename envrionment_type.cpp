
#include "environment_type.h"
#include <cassert>

void test_environment(){
#define FIX_ISSUE_40
#ifdef  FIX_ISSUE_40
//Conversion to string

  assert(static_cast<int>(environment_type::empty) == 0);
  assert(static_cast<int>(environment_type::random) == 2);
  assert(static_cast<int>(environment_type::random) != 9);
#endif
}
