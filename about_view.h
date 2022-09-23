#include <about.h>

#ifndef ABOUT_VIEW_H
#define ABOUT_VIEW_H


class about_view
{
  public:
    about_view();
    const about& get_about() { return m_about; }
  private:
    about m_about = about();
};

void test_about_view();

#endif // ABOUT_VIEW_H
