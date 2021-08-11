#ifndef COORDINATE_H
#define COORDINATE_H


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

void test_coordinate();

#endif // COORDINATE_H
