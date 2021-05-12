#ifndef SOUND_TYPE_H
#define SOUND_TYPE_H
#include <string>
enum class sound_type
{
  shoot,
  hit
};

/// Test the sound types and helper functions
void test_sound_type();

///converting sound type to str
   std::string to_str(const sound_type & in_sound);

#endif // SOUND_TYPE_H
