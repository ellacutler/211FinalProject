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
          background_sprite
            ({grid_size*model_.get_width(),grid_size*model_
            .get_height()+grid_size*10}, tile_color),
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
          score_font("sans.ttf", grid_size/2),
          win_lose_font("sans.ttf", grid_size/4),
          lose_screen(initial_window_dimensions(),lose_color),
          win_screen(initial_window_dimensions(),win_color),
          lose_text("You lose! Press R to restart!",win_lose_font),
          win_text("You win! Press R to play again!",win_lose_font),
          score_text("score: ",score_font)
{
 int i = 2;
 while(i <= 2048){
    std::string sval = std::to_string(i);
    number_sprites_.emplace_back(sval, number_font);
    i= i*2;
 }
 // making a different counter for score sprites
int g = 0;
 while(g<10 ){
     std::string scoreval = std::to_string(g);
     score_sprites_.emplace_back(scoreval,score_font);
     g = g+1;
 }
 ge211::Text_sprite::Builder builder(number_font); //use this somehow to get
 // sprite color
}

void
View::draw(ge211::Sprite_set& set)
{
    set.add_sprite(
            score_text,
            board_to_screen({0,0}) + ge211::Dims<int>{0,400},
            40
            );
    set.add_sprite(
        background_sprite,
        board_to_screen({0,0}),
        -10
        );
    add_score_sprite(
            set,
            board_to_screen({2,0}) + ge211::Dims<int>{0,400},
            40
            );
   for(Position pos : model_.all_positions()){
       set.add_sprite(
               tile_sprite,
               board_to_screen(pos),
               10
       );
       add_number_sprite(
               set,
               pos,
               15
       );
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
View::add_score_sprite(ge211::Sprite_set& set, Model::Position pos, int z) const
{

   // get the score
    int score = model_.get_score();
    std::string score_str = std::to_string(score);
    // make a vector for each value for the string (in char b/c c++)
    std::vector<char> str_vec;
    // then, iterate through each part of score and push back the value into
    // the string vector
    std::copy(score_str.begin(), score_str.end(), std::back_inserter(str_vec));
    // for each element of the vector
    // ge211::Posn<int> =
    // iterator for positions
    int i = 0;

    for (char& s: str_vec){
        // have corresponding integer value
        // i am a  bit tired so this might be a weird way to do it
        int g = s - '0';
        ge211::Posn<int> p = pos + grid_size/3.5*ge211::Dims<int>{i,0};
        std::cout << p.x << "\n";
        std::cout << model_.get_score() << "\n";

        set.add_sprite(

                score_sprites_.at(g),
                p,
                40

        );
        i+= 1;



    }

    // 1. convert to string (can't pass chars into text_sprite)
    // 2. find relevant text sprite with strcmp
    // 3. add to a position to the right of the previous digit



    // once we have the vector of each part of score, then set.add sprite all
    // of them
    // have to do this process so we don't have a text sprite for literally
    // every possible score hah

}
void
View::add_number_sprite(ge211::Sprite_set& set, Model::Position pos, int z)
const
{ // using from below, tried but it's not worth not-hard coding
    // (unless there's a way to convert between strings and sprites..)
    int val = model_[pos];
    //int displayindex = log2(val) - 1;
    if(val != 0){
        ge211::Posn<int> position= board_to_screen({pos.x ,pos.y})
                + ge211::Dims<int>(text_center,0);
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
                {model_.get_width()/3,model_.get_height()/2 },
                30);
    } else {
        set.add_sprite(
                lose_screen,
                {0,0},
                25);
        set.add_sprite(
                lose_text,
                {grid_size*model_.get_width()/10,grid_size*model_.get_height()
                /2},
                30);
    }

}

void
View::add_number_text(std::string&, ge211::Font&) const
{

}

View::Dimensions
View::initial_window_dimensions() const
{
    return

    {grid_size * model_.get_width(),
     grid_size*model_.get_height()+grid_size};

}

std::string
View::initial_window_title() const
{
    return "2048";
}

