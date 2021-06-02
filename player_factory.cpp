#include "player_factory.h"

player_factory::player_factory()
{

}

void test_player_factory()
{

    {
        const std::string id = "31415";
        player_factory f;
        f.set_id(id);
        const player p = f.create();
        assert(p.get_ID() == id);
      }

//  {   const color = {"31415"};
//      player_factory f;
//      f.set_id(id);
//      const player p = f.create();
//      assert(p.get_ID() == id);
//    }
}
