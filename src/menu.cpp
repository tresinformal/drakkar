#include "menu.h"

menu::menu( int w_width,
            int w_height,
            std::string label_button1,
            color color_button1,
            std::string label_button2,
            color color_button2,
            std::string label_button3,
            color color_button3,
            std::string label_button4,
            color color_button4)
  : m_window_width{w_width}, m_window_height{w_height},
    m_v_buttons{
      menu_button(label_button1, color_button1),
      menu_button(label_button2, color_button2),
      menu_button(label_button3, color_button3),
      menu_button(label_button4, color_button4)
      }
{
  align_buttons();
}
/// Gets the width of the screen
int menu::get_w_width() const noexcept { return m_window_width; }

/// Gets height of the screen
int menu::get_height() const noexcept { return m_window_height; }

/// Gets the vector of buttons
const std::vector<menu_button>& menu::get_buttons() const noexcept { return m_v_buttons; }

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

void menu::align_buttons() noexcept
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
    v.align_buttons();
    for (unsigned int i = 0; i < v.get_buttons().size(); ++i)
      assert(v.get_buttons()[i].get_y() -
             (static_cast<int>(i) + 1) * (width) /
             (static_cast<int>(v.get_buttons().size()) + 1) <
             0.000001f);
  }

  // Add an "Options" button to the menu
  {
     menu m;
     assert(m.get_buttons().size() == 4);
     assert(m.get_button(1).get_label() == "options");
  }

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

    ///It should always be possible to go back to the option widows by pressing 'esc'
    {
//        ///Open the program
//        ///Go to the options
//        option_view ov;
//        ov.show_game();
//        assert(is_not_showing_options(ov));
//        press_esc(ov);
//        assert(is_showing_options(ov));
    }
  //#define FIX_ISSUE_714
  #ifdef FIX_ISSUE_714
  // Buttons are at the right half of the screen,
  // the artwork at the left has the same height as the window
  // and is square.
  {
    const menu m;
    const int height{m.get_height()};
    const auto& buttons{m.get_buttons()};
    const int min_x{height}; // the art is square

    for (const auto& button: buttons)
    {
      // The x of a button is its origin
      assert(button.get_x() >= min_x);
    }
  }
  #endif // FIX_ISSUE_714
}
