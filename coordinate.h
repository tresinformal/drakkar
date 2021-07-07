#ifndef COORDINATE_H
#define COORDINATE_H


class Coordinate
{
private:
    double m_x = 0;
    double m_y = 0;

public:
  Coordinate();
  bool operator==(Coordinate in_coord);
  bool operator!=(Coordinate in_coord);
};

#endif // COORDINATE_H
