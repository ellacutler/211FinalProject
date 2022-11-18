#include "view.hxx"

using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

int const grid_size = 10;

static Color const tile_color {100, 100, 100};


View::View(Model const& model)
        : model_(model),
          tile_sprite({grid_size,grid_size}, tile_color)
{ }

void
View::draw(ge211::Sprite_set& set)
{
    //empty for now
}
