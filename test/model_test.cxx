#include "model.hxx"
#include <ge211.hxx>
#include <catch.hxx>
#include <iostream>
#include <model.hxx>


using namespace ge211;

using Position = ge211::Posn<int>;
using Dimensions = ge211::Dims<int>;
using Position_set = std::vector<Position>;
struct Test_access
{
    Model& model;

    // Constructs a `Test_access` with a reference to the Model under test.
    Test_access(Model&);
    bool is_board_mergable() const;
    void set_all_positions(int i);
    void print_board() const;
    Position_set all_positions() const;

};
//TEST ACCESS MEMBER FUNCTIONS!
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

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

//
// TODO: Write preliminary model tests.
// TODO: Model tests for

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
    CHECK(model.get_score() == 96);
    model.print_board();
    // this section checks that illegal moves don't do any



}

