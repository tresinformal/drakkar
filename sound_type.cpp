#include "sound_type.h"
#include "cassert"

void test_sound_type()
{
  static_assert(sound_type::shoot != sound_type::hit, "");
}
