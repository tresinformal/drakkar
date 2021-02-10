#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

#include <iosfwd>
#include <string>

enum class program_state
{
  menu,
  playing,
  paused
};

void test_program_state();
std::string to_str(const program_state this_program_state) noexcept;
std::ostream &operator<<(std::ostream &os, const program_state t);

#endif // PROGRAM_STATE_H
