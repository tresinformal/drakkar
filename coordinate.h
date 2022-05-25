#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>

class coordinate
{
public:
  coordinate(const double x, const double y);
  bool operator==(coordinate in_coord);
  bool operator!=(coordinate in_coord);
  double get_x() const noexcept;
  double get_y() const noexcept;

  void set_x(const double x) { m_x = x; }
  void set_y(const double y) { m_y = y; }


private:
    double m_x = 0;
    double m_y = 0;
};

// Get position (coordinate) or x y of an item
template <typename T>
double get_position(const T& item)
{
    return item.get_position();
}
template <typename T>
double get_x(const T& item)
{
    return item.get_x();
}
template <typename T>
double  get_y(const T& item)
{
    return item.get_y();
}

/// Implement stream operator
std::ostream& operator << (std::ostream &out, const coordinate &cor);

void test_coordinate();

#endif // COORDINATE_H
