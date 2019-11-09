#include "sound_type.h"

void test_sound_type()
{
  #ifdef FIX_ISSUE_72
  assert(sound_type::shoot != sound_type::hit);
  #endif
}
