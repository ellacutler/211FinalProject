#include "controller.hxx"

Controller::Controller()
        : view_(model_)
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
        model_.shift({-1,0});
    }
    if (key == ge211::Key::right()) {
        // shift the model to the right
        model_.shift({1,0});
    }
    if (key == ge211::Key::up()) {
        // shift the model up
        model_.shift({0,-1});
    }
    if (key == ge211::Key::down()) {
        // shift the model down
        model_.shift({0,1});
    }
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return screen_dimensions_;
}
