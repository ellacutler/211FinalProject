#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    using Dimensions = ge211::Dims<int>;
    using Position = ge211::Posn<int>;

    Dimensions initial_window_dimensions() const;
    std::string initial_window_title() const;

private:
    Model const& model_;
    ge211::Rectangle_sprite const background_sprite;
    ge211::Font sans30_{"sans.ttf", 30};
    ge211::Text_sprite value_sprite_[4][4];
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

    View::Position board_to_screen(Model::Position pos) const;
    void add_score_sprite(ge211::Sprite_set&, Model::Position pos, int
    z) const;
    void add_number_sprite(ge211::Sprite_set&, Model::Position pos, int
    z) const;
    void add_number_text(std::string&,ge211::Font&) const;
    void add_end_screen_(bool, ge211::Sprite_set&) const;

};
