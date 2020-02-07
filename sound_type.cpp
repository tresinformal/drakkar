#include "sound_type.h"
#include "cassert"

void test_sound_type()
{
  assert(sound_type::shoot != sound_type::hit);
}
