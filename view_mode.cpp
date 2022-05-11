#include "view_mode.h"
#include "cassert"

void test_view_mode()
{
 #ifndef NDEBUG
 {
   assert(view_mode::menu != view_mode::options);
   assert(view_mode::quit != view_mode::game);
 }
 #endif
}
