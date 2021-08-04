#include "coordinate.h"

coordinate::coordinate(){}

bool coordinate::operator==(coordinate in_coord) {
    return (m_x == in_coord.m_x) && (m_y == in_coord.m_y);
}

bool coordinate::operator!=(coordinate in_coord) {
    return not((m_x == in_coord.m_x) && (m_y == in_coord.m_y));
}

