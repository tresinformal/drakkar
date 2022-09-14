#include "view_manager.h"

view_manager::view_manager()
{

}

void test_view_manager()
{
  #ifndef NDEBUG
    
    ///View manager exists
    {
        view_manager{};
    }

  #endif
}
