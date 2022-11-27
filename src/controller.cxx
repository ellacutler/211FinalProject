#include "controller.hxx"

Controller::Controller(int width, int height)
        : model_(width, height),
          view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_key_down(ge211::events::Key key)
{
    if (key == ge211::Key::left()) {
        // shift the model to the left
        model_.play_move({-1,0});
    }
    if (key == ge211::Key::right()) {
        // shift the model to the right
        model_.play_move({1,0});
    }
    if (key == ge211::Key::up()) {
        // shift the model up
        model_.play_move({0,-1});
    }
    if (key == ge211::Key::down()) {
        // shift the model down
        model_.play_move({0,1});
    }
    if (key == ge211::Key::code('q')) {
        quit();
    }
    if (key == ge211::Key::code('r')) {
        //restart
        model_.restart();
    }
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}


