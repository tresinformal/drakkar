#include "sound_type.h"
#include "cassert"

std::string to_str(const sound_type this_sound_type) noexcept
{
  if (this_sound_type == sound_type::rocket)
  {
    return "rocket";
  }
  assert(this_sound_type == sound_type::cat);
  return "cat";
}

void test_sound_type()
{
  #ifndef NDEBUG // no tests in release
  static_assert(sound_type::shoot != sound_type::hit, "");
  //#define FIX_ISSUE_263
  #ifdef FIX_ISSUE_263
  // Conversion to string
  {
    assert(to_str(sound_type::shoot) == "shoot");
    assert(to_str(sound_type::hit) == "hit");
  }
  #endif // FIX_ISSUE_263
  #endif
}

