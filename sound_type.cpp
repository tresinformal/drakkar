#include "sound_type.h"
#include "cassert"

std::string to_str(const sound_type& this_sound_type)
{
  if (this_sound_type == sound_type::grow)
  {
    return "grow";
  }
  if (this_sound_type == sound_type::shrink)
  {
    return "shrink";
  }
  if (this_sound_type == sound_type::shoot)
  {
    return "shoot";
  }
  if (this_sound_type == sound_type::hit)
  {
    return "hit";
  }
  return {};
}

void test_sound_type()
{
  #ifndef NDEBUG // no tests in release
    {
        static_assert(sound_type::shoot != sound_type::hit, "");
    }
  #define FIX_ISSUE_263
  #ifdef FIX_ISSUE_263
  // Conversion to string
  {
        assert(to_str(sound_type::shoot) == "shoot");
        assert(to_str(sound_type::hit) == "hit");
        assert(to_str(sound_type::grow) == "grow");
        assert(to_str(sound_type::shrink) == "shrink");
  }
  #endif // FIX_ISSUE_263
  #endif
}

