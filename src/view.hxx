#pragma once

#include "model.hxx"

class View
{
public:
    // View dimensions, positions use 'int' coordinates
    using Dimensions = ge211::Dims<int>;
    using Position = ge211::Posn<int>;

    /// Constructs a view that knows about the given model
    explicit View(Model const& model);

    /// Draw sprites to screen
    void draw(ge211::Sprite_set& set);

    // Define window dimensions, title
    Dimensions initial_window_dimensions() const;
    std::string initial_window_title() const;

private:
    Model const& model_;

    ge211::Rectangle_sprite const background_sprite;

    /// Sprites for text, tiles, tile values
    ge211::Rectangle_sprite const tile_sprite;
    ge211::Rectangle_sprite const s2;
    ge211::Rectangle_sprite const s4;
    ge211::Rectangle_sprite const s8;
    ge211::Rectangle_sprite const s16;
    ge211::Rectangle_sprite const s32;
    ge211::Rectangle_sprite const s64;
    ge211::Rectangle_sprite const s128;
    ge211::Rectangle_sprite const s256;
    ge211::Rectangle_sprite const s512;
    ge211::Rectangle_sprite const s1024;
    ge211::Rectangle_sprite const s2048;
    ge211::Font number_font;
    ge211::Font score_font;
    ge211::Font win_lose_font;
    std::vector<ge211::Text_sprite> number_sprites_;
    std::vector<ge211::Text_sprite> score_sprites_;

    ge211::Rectangle_sprite const lose_screen;
    ge211::Rectangle_sprite const win_screen;
    ge211::Text_sprite lose_text;
    ge211::Text_sprite win_text;
    ge211::Text_sprite score_text;

    /// Converts abstract board position to concrete screen position
    View::Position board_to_screen(Model::Position pos) const;

    /// Adds score sprite to the 'ge211::Sprite_set' to be drawn to screen
    void add_score_sprite(ge211::Sprite_set&, Model::Position pos, int
    z) const;

    /// Adds text, tile sprites to the 'ge211::Sprite_set' to be drawn to screen
    void add_number_sprite(ge211::Sprite_set&, Model::Position pos, int
    z) const;

    /// Adds text, end screen overlay sprites to the 'ge211::Sprite_set' to be
    /// drawn to screen
    void add_end_screen_(bool, ge211::Sprite_set&) const;

};
