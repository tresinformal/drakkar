#include "view_mode.h"
#include <cassert>
#include <iostream>
#include <sstream>

std::ostream& operator<<(std::ostream& os, const view_mode m)
{
  if (m == view_mode::game) os << "game";
  return os;
}

void test_view_mode()
{
 #ifndef NDEBUG
 {
   assert(view_mode::menu != view_mode::options);
   assert(view_mode::quit != view_mode::game);
 }
 #ifndef FIX_ISSUE_562
 // (562) operator<<
 {
   const view_mode m = view_mode::game;
   std::stringstream s;
   s << m;
   assert(s.str() == "game");
 }
 #endif // FIX_ISSUE_562

 #endif
}
