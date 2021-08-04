#ifndef COORDINATE_H
#define COORDINATE_H


class coordinate
{
private:
    double m_x = 0;
    double m_y = 0;

public:
  coordinate();
  bool operator==(coordinate in_coord);
  bool operator!=(coordinate in_coord);
};

void test_coordinate();

#endif // COORDINATE_H
