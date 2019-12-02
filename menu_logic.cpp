#include "menu_logic.h"


menu_logic::menu_logic(unsigned int w_width, unsigned int w_height,
           std::string button1,
           std::string button2,
           std::string button3):
    m_window_width{w_width},
    m_window_height{w_height},
    m_v_buttons{menu_button(button1),menu_button(button2),menu_button(button3)}
{
    put_buttons_tidy();
}

menu_button& menu_logic::get_button(unsigned int index)
{

   if(index < m_v_buttons.size()){
       return m_v_buttons[index];
   }
   else{
       return m_mock_button;
   }
}


void menu_logic::put_buttons_tidy() noexcept
{
    for(unsigned int i = 0; i < get_m_v_buttons().size(); ++i){
        get_m_v_buttons()[i].set_x(m_window_width/2);
        get_m_v_buttons()[i].set_y((i+1)*m_window_height/(m_v_buttons.size()+1));
    }

}


void test_menu(){

    //menu_view is built with values
    //for width and height of the screen
    {
      unsigned int width = 1000;
      unsigned int height = 1000;
      menu_logic v(width,height);
      assert(v.get_w_width() - width < 0.00000001);
      assert(v.get_height() - height < 0.00000001);
    }

    //buttons are returned only for indexes
    // inside range
    //***Question from Stefano:
    //could I use try and catch framework for exceptions in this case?
    {
        menu_logic v;
        assert(v.get_button(0).get_name() == "action");
        assert(v.get_button(1000).get_name() == "INVALID INDEX!"
                                                  " Trying to get a button that does not exist");
    }
    //buttons are evenly distributed
    // along the height of the screen
    {
        //in the middle

        unsigned int width = 1000;
        unsigned int height = 1000;
        menu_logic v(width,height);
        v.put_buttons_tidy();
        for(unsigned int i = 0; i < v.get_m_v_buttons().size(); ++i)
        assert(v.get_m_v_buttons()[i].get_y() - (i+1)*width/(v.get_m_v_buttons().size()+1) < 0.000001f );
    }

}
