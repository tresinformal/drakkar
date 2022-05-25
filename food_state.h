#ifndef FOOD_STATE_H
#define FOOD_STATE_H

#include <iostream>

enum class food_state
{
  eaten, uneaten
};
void test_food_state();

/// Implement stream operator
std::ostream& operator << (std::ostream &out, const food_state &fs);


#endif // FOOD_STATE_H
