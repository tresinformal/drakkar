#include "coordinate.h"
#include "shelter.h"
#include <cassert>
#include <cmath>
#include <string>

shelter::shelter(const coordinate c, const double radius,
                 const color &col, const double shelter_speed, const double direction)
    : m_color{col}, m_radius{radius}, m_c{c}, m_speed{shelter_speed},
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

coordinate shelter::get_position() const noexcept
{
  return m_c;
}

double shelter::get_x() const noexcept
{
  return m_c.get_x();
}

double shelter::get_y() const noexcept
{
  return m_c.get_y();
}

void shelter::make_shelter_drift()
{
  double new_x = m_c.get_x() + std::cos(rand());
  double new_y = m_c.get_y() + std::sin(rand());
  m_c = coordinate(new_x, new_y);
}

void place_randomly(std::mt19937 &rng, const coordinate &top_left, const coordinate &bottom_right)
{
    std::uniform_real_distribution<> dis_x(top_left.get_x(), bottom_right.get_x());
    std::uniform_real_distribution<> dis_y(top_left.get_y(), bottom_right.get_y());
    m_c = coordinate(dis_x(rng), dis_y(rng));
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
std::string to_str(const shelter& in_shelter) noexcept
{
    std::string msg;
    msg+="shelter info:\n";
    msg+="\tPosition:\n";
    msg+="\t\tx= "+std::to_string(get_x(in_shelter))+"\n";
    msg+="\t\ty= "+std::to_string(get_y(in_shelter))+"\n";
    msg+="\tRadius:\n"+std::to_string(in_shelter.get_radius())+"\n";
    msg+="\tColor:\n"+to_str(in_shelter.get_color())+"\n";
    msg+="\tSpeed:\n"+std::to_string(in_shelter.get_speed())+"\n";
    msg+="\tDirection:\n"+std::to_string(in_shelter.get_direction())+"\n";
    return msg;

}
void test_shelter() //!OCLINT tests may be complex
{
  #ifndef NDEBUG // no tests in release
  {
    shelter f;
    assert(get_x(f) == 0.0);
    assert(get_y(f) == 0.0);
  }
  // X and Y work as expected
  {
    const coordinate c{12.34, 23.45};
    const shelter f(c);
    assert(std::abs(get_x(f) - c.get_x()) < 0.00001);
    assert(std::abs(get_y(f) - c.get_y()) < 0.00001);
  }
  //test that shelter moves with each tick
  {
    shelter f;
    assert(get_x(f) == 0.0);
    assert(get_y(f) == 0.0);
    f.make_shelter_drift();
    f.make_shelter_drift(); //move shelter
    assert(get_x(f) != 0.0); //see that shelter moves
  }
  // Colors
  {
    const int r{1};
    const int g{2};
    const int b{3};
    const int a{4};
    coordinate c{0.0, 0.0};
    const color col(r, g, b, a);
    const shelter s(c, 100.0, col);
    assert(get_blueness(s) == b);
    assert(get_greenness(s) == g);
    assert(get_opaqueness(s) == a);
    assert(get_redness(s) == r);
  }
  #define FIX_ISSUE_325
  #ifdef FIX_ISSUE_325
    {
      coordinate some_random_point(1, 1);
      shelter n_shelter(some_random_point);
      assert(n_shelter.get_position() == some_random_point);
    }
  #endif
  #define FIX_ISSUE_264
  #ifdef FIX_ISSUE_264
  // Conversion to string
  {
    coordinate c{1.2, 3.4};
    const shelter s(c, 5.6, color(7, 8, 9, 10));
    const std::string t = to_str(s);
    assert(!t.empty());
  }
  #endif // FIX_ISSUE_264
  #endif
}
