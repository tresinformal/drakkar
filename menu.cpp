#include "menu.h"

menu::menu( int w_width,  int w_height,
            std::string button1, std::string button2,
            std::string button3)
  : m_window_width{w_width}, m_window_height{w_height},
    m_v_buttons{menu_button(button1), menu_button(button2),
                menu_button(button3)}
{
  put_buttons_tidy();
}

menu_button &menu::get_button(int index)
{

  assert(index >= 0 && index < static_cast<int>(m_v_buttons.size()));
  return m_v_buttons[static_cast<unsigned int>(index)];

}

void menu::put_buttons_tidy() noexcept
{
  for (unsigned int i = 0; i != get_m_v_buttons().size(); ++i)
    {
      get_m_v_buttons()[i].set_x(m_window_width / 2);
      get_m_v_buttons()[i].set_y(static_cast<int>((i + 1)) *
                                 (m_window_height)/
                                 (static_cast<int>(m_v_buttons.size()) + 1));
    }
}

void test_menu()
{

  // menu_view is built with values
  // for width and height of the screen
  {
    int width = 1000;
    int height = 1000;
    menu v(width, height);
    assert(v.get_w_width() - width < 0.00000001);
    assert(v.get_height() - height < 0.00000001);
  }

  // buttons are returned only for indexes
  // inside range
  //***Question from Stefano:
  // could I use try and catch framework for exceptions in this case?
  {
    menu v;
    assert(v.get_button(0).get_name() == "action");
  }
  // buttons are evenly distributed
  // along the height of the screen
  {
    // in the middle

    int width = 1000;
    int height = 1000;
    menu v(width, height);
    v.put_buttons_tidy();
    for (unsigned int i = 0; i < v.get_m_v_buttons().size(); ++i)
      assert(v.get_m_v_buttons()[i].get_y() -
             (static_cast<int>(i) + 1) * (width) /
             (static_cast<int>(v.get_m_v_buttons().size()) + 1) <
             0.000001f);
  }
}
