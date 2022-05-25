#include "food_state.h"
#include "cassert"
#include <sstream>

std::ostream& operator << (std::ostream &out, const food_state &fs)
{
    return out << ;
}


void test_food_state()
{
#ifndef NDEBUG
    {
        assert(food_state::eaten!= food_state::uneaten);
    }
#define FIX_ISSUE_557
#ifdef FIX_ISSUE_557
    // to_str
    {
      assert(to_str(food_state::eaten) == "eaten");
      assert(to_str(food_state::uneaten) == "uneaten");
    }
    {
      const food_state food_state = food_state::eaten;
      std::stringstream s;
      s << food_state;
      //assert(!s.str().empty());
    }
#endif // FIX_ISSUE_557
#endif
}
