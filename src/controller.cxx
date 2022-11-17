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
Controller::on_key_down(ge211::events::Key)
{
    if (key == ge211::Key::left()) {
        model_.turn_left(false);
    }
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return screen_dimensions_;
}
