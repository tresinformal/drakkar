#include "environment.h"
#include<assert.h>

environment::environment()
{

}


void test_environment(){

    environment e;

    assert(e.get_min_x()==-1000);
    assert(e.get_min_y()==-1000);
    assert(e.get_max_x()==1000);
    assert(e.get_max_y()==1000);
}
