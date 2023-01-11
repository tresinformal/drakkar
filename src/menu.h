
#ifndef MENU_H
#define MENU_H
#include "menu_button.h"

class menu
{
public:
  menu(int w_width = 1280,
       int w_height = 720,
       std::string label_button1 = "action",
       color color_button_1 = create_green_color(),
       std::string label_button2 = "options",
       color color_button_2 = create_blue_color(),
       std::string label_button3 = "about",
       color color_button_3 = create_red_color(),
       std::string label_button4 = "quit",
       color color_button_4 = color(120, 120, 0)
      );

  /// Gets the width of the screen
  int get_w_width() const noexcept;

  /// Gets height of the screen
  int get_height()const noexcept;

  /// Gets the vector of buttons
  std::vector<menu_button> &get_buttons() noexcept;

  /// Get one button at index i
  menu_button &get_button(int index);

  /// Get one button at index i
  menu_button &get_button(const std::string& label);

  /// Sets the position of the buttons
  /// aligned in the center and equally
  /// distant vertically
  void put_buttons_tidy() noexcept;

private:
  int m_window_width;
  int m_window_height;
  std::vector<menu_button> m_v_buttons;

  /// mock button to signal if button that does not exist is called
  menu_button m_mock_button =
      menu_button("INVALID INDEX!"
                  " Trying to get a button that does not exist",
                  color() // black
                  );
};

bool is_inside_button(const coordinate& c, const menu_button& mb);

void test_menu();

#endif // MENU_H
