#include "sound_type.h"
#include "cassert"
#include <iostream>
#include <sstream>

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

std::ostream& operator << (std::ostream& os, const sound_type& sound)
{
    os << to_str(sound);
    return os;
}

void test_sound_type()
{
  #ifndef NDEBUG // no tests in release
    {
        static_assert(sound_type::shoot != sound_type::hit, "");
    }
  // (508) operator<<
  {
    std::stringstream s;
    const sound_type st = sound_type::shoot;
    s << st;
    assert(!s.str().empty());
  }
  // (263) Conversion to string
  {
        assert(to_str(sound_type::shoot) == "shoot");
        assert(to_str(sound_type::hit) == "hit");
        assert(to_str(sound_type::grow) == "grow");
        assert(to_str(sound_type::shrink) == "shrink");
  }
  #endif
}

