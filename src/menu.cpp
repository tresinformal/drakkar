#include "menu.h"

menu::menu( int w_width,
            int w_height,
            std::string label_button1,
            color color_button1,
            std::string label_button2,
            color color_button2,
            std::string label_button3,
            color color_button3)
  : m_window_width{w_width}, m_window_height{w_height},
    m_v_buttons{
      menu_button(label_button1, color_button1),
      menu_button(label_button2, color_button2),
      menu_button(label_button3, color_button3)
      }
{
  put_buttons_tidy();
}
/// Gets the width of the screen
int menu::get_w_width() const noexcept { return m_window_width; }

/// Gets height of the screen
int menu::get_height() const noexcept { return m_window_height; }

/// Gets the vector of buttons
std::vector<menu_button> &menu::get_buttons() noexcept { return m_v_buttons; }

menu_button &menu::get_button(int index)
{
  assert(index >= 0 && index < static_cast<int>(m_v_buttons.size()));
  return m_v_buttons[static_cast<unsigned int>(index)];
}

menu_button &menu::get_button(const std::string& label)
{
  for (auto& mb : m_v_buttons)
    {
      if (mb.get_label() == label)
        {
          return mb;
        }
    }
  // If no match return an error
  throw std::logic_error("No button in menu has this label.");
}

void menu::put_buttons_tidy() noexcept
{
  for (unsigned int i = 0; i != get_buttons().size(); ++i)
    {
      get_buttons()[i].set_x(m_window_width / 2);
      get_buttons()[i].set_y(static_cast<int>((i + 1)) *
                                 (m_window_height)/
                                 (static_cast<int>(m_v_buttons.size()) + 1));
    }
}

bool is_inside_button(const coordinate& c, const menu_button& mb)
{
  const double right = mb.get_x() + mb.get_body().x / 2.0;
  const double left = mb.get_x() - mb.get_body().x / 2.0;
  const double bottom = mb.get_y() + mb.get_body().y / 2.0;
  const double top = mb.get_y() - mb.get_body().y / 2.0;

  return c.get_x() <= right &&
      c.get_x() >= left &&
      c.get_y() <= bottom &&
      c.get_y() >= top;
}

void test_menu()
{
  #ifndef NDEBUG // no tests in release
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
    assert(v.get_button(0).get_label() == "action");
  }
  {
    // (482) Menu button can be called from its label
    menu m;
    const std::string label = "about";
    const menu_button mb_about = m.get_button(label);
    assert(mb_about.get_label() == label);
  }
  {
    // (483) Calling a button that doesn't exist causes an error
    menu m;
    const std::string wrong_label = "whatever, doesn't exist";
    try {
      const menu_button mb = m.get_button(wrong_label); // throws exception
    }
    catch ( const std::exception& e ) {
      assert(std::string(e.what()) == std::string("No button in menu has this label."));
    }
  }
  // buttons are evenly distributed
  // along the height of the screen
  {
    // in the middle

    int width = 1000;
    int height = 1000;
    menu v(width, height);
    v.put_buttons_tidy();
    for (unsigned int i = 0; i < v.get_buttons().size(); ++i)
      assert(v.get_buttons()[i].get_y() -
             (static_cast<int>(i) + 1) * (width) /
             (static_cast<int>(v.get_buttons().size()) + 1) <
             0.000001f);
  }

  //#define FIX_ISSUE_446
  #ifdef FIX_ISSUE_446
  // Add an "Options" button to the menu
  {
     menu m;
     assert(m.get_buttons().size() == 4);
     assert(m.get_button(1).get_name() == "options");
  }
  #endif // FIX_ISSUE_446

  {
    // (484) One can detect if a position is inside or outside a menu button
    menu m;
    const menu_button mb = m.get_button(0);
    const float mb_width = mb.get_body().x;
    const float mb_height = mb.get_body().y;
    const coordinate c_inside(
          mb.get_x() + mb_width / 2.0,
          mb.get_y() + mb_height / 2.0
          );
    const coordinate c_outside1(
          mb.get_x() + mb_width / 2.0 + 1.0,
          mb.get_y() + mb_height / 2.0
          );
    const coordinate c_outside2(
          mb.get_x() + mb_width / 2.0,
          mb.get_y() + mb_height / 2.0 + 1.0
          );
    assert(is_inside_button(c_inside, mb));
    assert(!is_inside_button(c_outside1, mb));
    assert(!is_inside_button(c_outside2, mb));
  }
  #endif
}
