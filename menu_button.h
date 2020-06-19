#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H
#include <SFML/Graphics.hpp>
#include <cassert>
#include <string>

class menu_button
{
public:
  menu_button(std::string name,
              float b_width = 200.0f,
              float b_height = 100.0f);
  /// Get x pos of a button
  float get_x() const noexcept;
  /// Get y pos of a button
  float get_y() const noexcept;
  /// Set the x pos of a button
  void set_x(float x_pos) { m_x = x_pos; }
  /// Set the y pos of a button
  void set_y(float y_pos) { m_y = y_pos; }
  /// Get name of the button
  std::string get_name() const noexcept { return m_name; }
  /// Get the sizes of the button
  const sf::Vector2f &get_body() const noexcept;

private:
  sf::Vector2f m_body;
  std::string m_name;
  float m_x;
  float m_y;
};

void test_menu_button();
#endif // MENU_BUTTON_H
