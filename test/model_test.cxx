#include "model.hxx"
#include <ge211.hxx>
#include <catch.hxx>
#include <iostream>
#include <model.hxx>


using namespace ge211;

using Position = ge211::Posn<int>;
using Dimensions = ge211::Dims<int>;
using Position_set = std::vector<Position>;

/// TEST ACCESS STRUCTS AND MEMBER FUNCTIONS
struct Test_access
{
    Model& model;

    // Constructs a `Test_access` with a reference to the Model under test.
    Test_access(Model&);
    bool is_board_mergable() const;
    void set_all_positions(int i);
    void print_board() const;
    Position_set all_positions() const;
    void set_manual_positions(const std::vector<int> &vect);
    bool game_over();
    void next_turn();

};
//TEST ACCESS MEMBER FUNCTIONS!
void
Test_access::next_turn(){
    model.next_turn_();
}
Model::Position_set
Test_access::all_positions() const
{
    return model.all_positions();
}
Test_access::Test_access(Model& model)
        : model(model)
{ }

bool
Test_access::is_board_mergable() const
{
    return model.is_board_mergable_();
}
void
Test_access::set_all_positions(int i)
{
    model.set_all_positions(i);
}
void
Test_access::print_board() const
{
    model.print_board();
}
void
Test_access::set_manual_positions(const std::vector<int> &vect)
{
    model.set_manual_positions(vect);

}
bool
Test_access::game_over(){
    return model.gameover_;
}

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

///MODEL TESTS

TEST_CASE(" aa starting condition test")
{
    /*
     * Starting moves -
     * initialize the game,
     * press a few buttons,
     * check that stuff is created and merges correctly,
     * score increases correctly,.

     */
    Model model(4,4, {1,1}, {2,2} );
    // sets intial values at 1,1 and 2,2
    // Test_access m (model);
    CHECK_FALSE(model.is_gameover());
    CHECK(model.get_score() == 0);
    model.print_board();
    model.play_move({-1,0});
    model.print_score();
    model.print_board();

    CHECK((model.get_score() == 0));
    // shift the board down...
    model.play_move({0,1});
    model.print_score();
    model.print_board();
    CHECK(model.get_score() == 4);


}

// model tests run in order hense the aa, bb, etc.
TEST_CASE("bb complex merging test")
{
    Model model(4,4, {1,1}, {2,2} );
    Test_access access(model);
    access.set_all_positions(2);
    access.print_board();
    CHECK(access.is_board_mergable() == true);
    std::cout << "hi \n" ;
    model.play_move({-1,0});
    access.print_board();
    CHECK(model.get_score() == 32);
    model.play_move({0,-1});
    CHECK(model.get_score() == 64);
    model.play_move({0,1});
    model.print_score();
    // this one can either be 100 or 96 depending only on what is randomly

    CHECK((model.get_score() == 96 || model.get_score() == 100));
    model.print_board();
}
TEST_CASE( "game win ")
{
    Model model(4,4, {1,1}, {2,2} );
    Test_access access(model);
    access.set_manual_positions(
            {1024,512, 0, 0,
             0,256, 0, 0,
             0,256, 0, 0,
             0,0, 0, 0}
            );

    access.print_board();
    model.play_move({0,-1});
    model.play_move({0,-1});
    CHECK(model.get_won()== false);
    model.play_move({-1,0});
    CHECK(model.get_won() == true);
    CHECK(model.is_gameover()==true);

}
TEST_CASE("game lose")
{
    Model model(4,4, {1,1}, {2,2} );
    Test_access access(model);
    access.set_manual_positions(
            {256,16,32, 4,
             4,128, 1024, 8,
             32,0, 8, 64,
             256,16, 256, 8}
    );

    access.print_board();
    model.play_move({0,1});
    access.print_board();


    CHECK(model.get_won()== false);
    CHECK(access.is_board_mergable()==false);
    CHECK(access.game_over() == true);

}
TEST_CASE("game merge 2")
{
    Model model(4,4, {1,1}, {2,2} );
    Test_access access(model);
    access.set_manual_positions(
            {256,128,32, 4,
             4,128, 4, 8,
             4,0, 8, 64,
             256,16, 256, 8}
    );

    access.print_board();
    model.play_move({0,-1});
    model.play_move({-1,0});

    access.print_board();


    CHECK(model.get_won()== false);
    CHECK(access.is_board_mergable()==true);
    CHECK(access.game_over() == false);

}



