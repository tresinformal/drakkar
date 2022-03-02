#include "food_state.h"
#include "cassert"



void test_food_state()
{
 #ifndef NDEBUG
 {
   assert(food_state::eaten!= food_state::uneaten);
 }
 #endif
}
