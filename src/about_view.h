#include "about.h"
#include "view_mode.h"
#include "game_resources.h"
#include <SFML/Graphics/RenderWindow.hpp>

#ifndef ABOUT_VIEW_H
#define ABOUT_VIEW_H


class about_view
{
  public:
    about_view();
    const about& get_about() { return m_about; }

    void show();
    void exec();

    view_mode get_next_view() const
    {
        return m_next_view;
    }

    bool is_window_open() { return m_window.isOpen(); }

  private:
    about m_about = about();
    sf::RenderWindow m_window;
    game_resources m_game_resources;
    bool process_events();
    double m_height = 720;
    double m_width = 1280;
    view_mode m_next_view = view_mode::quit;
};

void test_about_view();

#endif // ABOUT_VIEW_H
