#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "environment_type.h"


class environment
{
public:
    environment();
    int get_min_x() const noexcept {return m_min_x;}
    int get_min_y() const noexcept {return m_min_y;}
    int get_max_x() const noexcept {return m_max_x;}
    int get_max_y() const noexcept {return m_max_y;}
private:
    int m_min_x=-1000;
    int m_min_y=-1000;
    int m_max_x=1000;
    int m_max_y=1000;
};


void test_environment();
#endif // ENVIRONMENT_H
