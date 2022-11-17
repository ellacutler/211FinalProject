#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

    ge211::Dims<int> initial_window_dimensions() const override;

protected:
    void draw(ge211::Sprite_set& set) override;
    void on_key_down(ge211::events::Key) override;



private:
    Model model_;
    View view_;
};
