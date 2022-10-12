#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <SFML/Graphics.hpp>
#include "color.h"
#include "coordinate.h"

#include <cassert>
#include <string>

class menu_button
{
public:
  menu_button(std::string label,
              color b_color,
              coordinate position = coordinate(0.0, 0.0),
              float b_width = 200.0f,
              float b_height = 100.0f);

  /// Get x pos of a button
  float get_x() const noexcept;
  /// Get y pos of a button
  float get_y() const noexcept;
  /// Get coordinate of a button
  coordinate get_position() const noexcept;
  /// Set the x pos of a button
  void set_x(float x_pos) { m_position.set_x(x_pos); }
  /// Set the y pos of a button
  void set_y(float y_pos) { m_position.set_y(y_pos); }
  /// Get name of the button
  std::string get_label() const noexcept { return m_label; }
  /// Get button color
  color get_color() const noexcept { return m_color;}
  /// Get the sizes of the button
  const sf::Vector2f &get_body() const noexcept;

private:
  sf::Vector2f m_body;
  std::string m_label;
  coordinate m_position;
  color m_color;
};

void test_menu_button();
#endif // MENU_BUTTON_H
