#include "shelter.h"
#include <cassert>
#include <cmath>
#include <string>

shelter::shelter(const double x, const double y, const double radius,
                 const color &c, const double shelter_speed, const double direction)
    : m_color{c}, m_radius{radius}, m_x{x}, m_y{y},m_speed {shelter_speed},
      m_direction{direction}
{
}

const color& shelter::get_color() const noexcept
{
  return m_color;
}

double shelter::get_radius() const noexcept
{
  return m_radius;
}

double shelter::get_x() const noexcept
{
  return m_x;
}

double shelter::get_y() const noexcept
{
  return m_y;
}

void shelter::update_shelter_position()
{
  m_x += std::cos(rand());
  m_y += std::sin(rand());
}
double shelter::get_direction() const noexcept
{
    return m_direction;
}
double shelter::get_speed() const noexcept
{
    return m_speed;
}

int get_blueness(const shelter &f) noexcept
{
  return get_blueness(f.get_color());
}

int get_greenness(const shelter &f) noexcept
{
  return get_greenness(f.get_color());
}

int get_opaqueness(const shelter &f) noexcept
{
  return get_opaqueness(f.get_color());
}

int get_redness(const shelter &f) noexcept
{
  return get_redness(f.get_color());
}

//converting shelter to string in debugging purposes
const std::string to_str(const shelter& in_shelter) noexcept
{
    std::string msg;
    msg+="shelter info:\n";
    msg+="\tPosition:\n";
    msg+="\t\tx= "+std::to_string(in_shelter.get_x())+"\n";
    msg+="\t\ty= "+std::to_string(in_shelter.get_y())+"\n";
    msg+="\tRadius:\n"+std::to_string(in_shelter.get_radius())+"\n";
    msg+="\tColor:\n"+to_str(in_shelter.get_color())+"\n";
    msg+="\tSpeed:\n"+std::to_string(in_shelter.get_speed())+"\n";
    msg+="\tDirection:\n"+std::to_string(in_shelter.get_direction())+"\n";
    return msg;

}
void test_shelter() //!OCLINT tests may be complex
{
  {
    shelter f;
    assert(f.get_x() == 0.0);
    assert(f.get_y() == 0.0);
  }
  // X and Y work as expected
  {
    const double x{12.34};
    const double y{23.45};
    const shelter f(x, y);
    assert(std::abs(f.get_x() - x) < 0.00001);
    assert(std::abs(f.get_y() - y) < 0.00001);
  }
  //test that shelter moves with each tick
  {
    shelter f;
    assert(f.get_x() == 0.0);
    assert(f.get_y() == 0.0);
    f.update_shelter_position();
    f.update_shelter_position(); //move shelter
    assert(f.get_x() != 0.0); //see that shelter moves
  }
  // Colors
  {
    const int r{1};
    const int g{2};
    const int b{3};
    const int a{4};
    const color c(r, g, b, a);
    const shelter s(0.0, 0.0, 100.0, c);
    assert(get_blueness(s) == b);
    assert(get_greenness(s) == g);
    assert(get_opaqueness(s) == a);
    assert(get_redness(s) == r);
  }
  #define FIX_ISSUE_264
  #ifdef FIX_ISSUE_264
  // Conversion to string
  {
    const shelter s(1.2, 3.4, 5.6, color(7, 8, 9, 10));
    const std::string t = to_str(s);
    assert(!t.empty());
  }
  #endif // FIX_ISSUE_264
}
