#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

private:
    Model const& model_;


    ge211::Font sans30_{"sans.ttf", 30};
    ge211::Text_sprite value_sprite_[4][4];
    ge211::Rectangle_sprite const tile_sprite;
};
