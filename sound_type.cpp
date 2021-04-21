#include "sound_type.h"
#include "cassert"

void test_sound_type()
{
  static_assert(sound_type::shoot != sound_type::hit, "");
  //#define FIX_ISSUE_263
  #ifdef FIX_ISSUE_263
  // Conversion to string
  {
    assert(to_str(sound_type::shoot) == "shoot");
    assert(to_str(sound_type::hit) == "hit");
  }
  #endif // FIX_ISSUE_263

}

