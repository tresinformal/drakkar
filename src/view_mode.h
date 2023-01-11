#ifndef VIEW_MODE
#define VIEW_MODE

#include <iosfwd>

enum class view_mode
{
  game,
  menu,
  options,
  quit
};

void test_view_mode();

std::ostream& operator<<(std::ostream& os, const view_mode m);

#endif // VIEW_MODE

