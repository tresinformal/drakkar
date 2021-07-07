#include "coordinate.h"

Coordinate::Coordinate()
{

}

bool Coordinate::operator==(Coordinate in_coord) {
    return (m_x == in_coord.m_x) && (m_y == in_coord.m_y);
}

