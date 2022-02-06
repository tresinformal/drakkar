#include "menu_button.h"
#include "coordinate.h"
#include "color.h"

menu_button::menu_button(std::string name,
                         color b_color,
                         float width,
                         float height)
    : m_body{width, height},
      m_name{name},
      m_color{b_color}
{
}
/// Get x pos of a button
float menu_button::get_x() const noexcept { return m_x; }

/// Get y pos of a button
float menu_button::get_y() const noexcept { return m_y; }

  /// Get the sizes of the button
const sf::Vector2f &menu_button::get_body() const noexcept { return m_body; }

void test_menu_button()
{
    #ifndef NDEBUG // no tests in release
    // (481) buttons can be set to a certain position
    {
        coordinate c = {1.2f, 3.4f};
        color col = create_blue_color();
        menu_button m_b("test", col, c);
        assert(m_b.get_position() == c);
        assert(m_b.get_x() - c.get_x() < 0.00000001f);
        assert(m_b.get_y() - c.get_y() < 0.00000001f);
    }
    //A button can be initialized with a given size
    //and a given name
    {
        auto width = 3.14f;
        auto height = 42.0f;
        coordinate c = {1.2f, 3.4f};
        color col = create_blue_color();
        std::string name = "Frank";
        menu_button m_b{name, col, c, width, height};
        assert(m_b.get_body().x == width
                && m_b.get_body().y == height
               && m_b.get_name() == name);
    }
#endif
}
