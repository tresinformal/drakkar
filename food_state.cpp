#include "food_state.h"
#include "cassert"
#include <sstream>


std::ostream& operator << (std::ostream &out, const game_options &fs)
{
    return out << to_str(fs);
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
      assert(!s.str().empty());
    }
#endif // FIX_ISSUE_557
#endif
}

std::string to_str(const food_state &fs)
{
    switch (fs) {
    case food_state::eaten :
        return "eaten";
        break;
    case food_state::uneaten :
        return "uneaten";
        break;
    default:
        throw std::invalid_argument{"unrecognized food_state"};
        return "Invalid!";
        break;
    }
}
