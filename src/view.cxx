#include "view.hxx"
#include <iostream>
#include <string>
#include <cmath>
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

int const grid_size = 100;
int const board_size = (grid_size - 2);
int  text_center = board_size/4 + 5 ;
// eventually make grid size a function of the model width and height
// i hard coded the background sprites because there wasn't a real pattern for
// all the numbers
static Color const tile_color {100, 100, 100};
static Color const c2 {238, 228, 218 };
static Color const c4 {237, 224, 200};
static Color const c8 {242, 177, 121};
static Color const c16 {245, 149, 99};
static Color const c32 {246, 124, 95};
static Color const c64 {246, 94, 59};
static Color const c128 {237, 207, 114};
static Color const c256 {237, 204, 97};
static Color const c512 {237, 200, 80};
static Color const c1024{237, 197, 63};
static Color const c2048{237, 194, 46};

static Color const lose_color{255,0,0,50};
static Color const win_color {255,255,0,50};


View::View(Model const& model)
        : model_(model),
          tile_sprite({grid_size,grid_size}, tile_color),
          s2({board_size, board_size}, c2),
          s4({board_size, board_size}, c4),
          s8({board_size, board_size}, c8),
          s16({board_size, board_size}, c16),
          s32({board_size, board_size}, c32),
          s64({board_size, board_size}, c64),
          s128({board_size, board_size}, c128),
          s256({board_size, board_size}, c256),
          s512({board_size, board_size}, c512),
          s1024({board_size, board_size}, c1024),
          s2048({board_size, board_size}, c2048),
          number_font("sans.ttf", grid_size/2),
          lose_screen(initial_window_dimensions(),lose_color),
          win_screen(initial_window_dimensions(),win_color),
          lose_text("You lose! Press R to restart!",number_font),
          win_text("You win! Press R to play again!",number_font)
{
 int i = 2;
 while(i <= 2048){
    std::string sval = std::to_string(i);
    number_sprites_.emplace_back(sval, number_font);
    i= i*2;
 }
 ge211::Text_sprite::Builder builder(number_font);
}

void
View::draw(ge211::Sprite_set& set)
{
   for(int i = 0; i < model_.get_height(); i++){
       for(int j = 0; j <model_.get_width(); j++){
           set.add_sprite(
                   tile_sprite,
                   board_to_screen({i,j}),
                   10
           );
           add_number_sprite(
                   set,
                   {i,j},
                   15
           );



       }
   }
   if (model_.is_gameover()) add_end_screen_(model_.get_won(), set);
}
View::Position
View::board_to_screen(Model::Position pos) const
{
    // should return the array position divided by total array length
    // multiplied by the screen dimensions
    return {(grid_size+1)*pos.x , (grid_size+1)*pos.y };
}
void
View::add_number_sprite(ge211::Sprite_set& set, Model::Position pos, int z)
const
{ // using from below, tried but it's not worth not-hard coding
    // (unless there's a way to convert between strings and sprites..)
    int val = model_.get_at_(pos);
    int displayindex = log2(val) - 1;
    // when
    if(model_.get_at_(pos) != 0){
        ge211::Posn<int> position= board_to_screen({pos.x ,pos.y
                                              }) + ge211::Dims<int>(text_center,
                                                         0);
        set.add_sprite(
                number_sprites_.at(log2(val) - 1),
                position,
                20

        );
    }

    if(val == 2){

        set.add_sprite(
                s2,
                board_to_screen({pos.x, pos.y}),
                15
        );
    }
    if(val == 4){
        set.add_sprite(
                s4,
                board_to_screen({pos.x, pos.y}),
                15
        );
    }
    if(val == 8){
        set.add_sprite(
                s8,
                board_to_screen({pos.x, pos.y}),
                15
        );
    }
    if(val == 16){
        set.add_sprite(
                s16,
                board_to_screen({pos.x, pos.y}),
                15
        );
    }
    if(val == 32){
        set.add_sprite(
                s32,
                board_to_screen({pos.x, pos.y}),
                15
        );
    }if(val == 64){
        set.add_sprite(
                s64,
                board_to_screen({pos.x, pos.y}),
                15
        );
    }if(val == 128){
        set.add_sprite(
                s128,
                board_to_screen({pos.x, pos.y}),
                15
        );
    }if(val == 256){
        set.add_sprite(
                s256,
                board_to_screen({pos.x, pos.y}),
                15
        );
    }if(val == 512){
        set.add_sprite(
                s512,
                board_to_screen({pos.x, pos.y}),
                15
        );
    }if(val == 1024 ){
        set.add_sprite(
                s1024,
                board_to_screen({pos.x, pos.y}),
                15
        );
    }
    if(val == 2048){
        set.add_sprite(
                s2048,
                board_to_screen({pos.x, pos.y}),
                15
        );
    }

}

void
View::add_end_screen_(bool is_win, Sprite_set& set) const
{
    if (is_win) {
        set.add_sprite(
                win_screen,
                {0,0},
                25);
        set.add_sprite(
                win_text,
                {model_.get_width()/3,model_.get_height()/2},
                30);
    } else {
        set.add_sprite(
                lose_screen,
                {0,0},
                25);
        set.add_sprite(
                lose_text,
                {0,grid_size*model_.get_height()/2,},
                30);
    }

}

void
View::add_number_text(std::string&, ge211::Font&) const
{

}
