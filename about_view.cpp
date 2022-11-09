#include "about_view.h"
#include "about.h"

about_view::about_view()
{

}

void test_about_view()
{
  // An about view has a member of class about
  about_view av;
  about some_info;
  some_info = av.get_about();
}
