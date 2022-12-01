#include "model.hxx"
#include <ge211.hxx>
#include <catch.hxx>
#include <iostream>
#include <model.hxx>


using namespace ge211;

using Position = ge211::Posn<int>;
using Dimensions = ge211::Dims<int>;
using Position_set = std::vector<Position>;
/*struct Test_access
{
    Model& model;

    // Constructs a `Test_access` with a reference to the Model under test.
    Test_access(Model&);


}; */

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

//
// TODO: Write preliminary model tests.
// TODO: Model tests for

TEST_CASE("starting condition test")
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






}


/*Test_access::Test_access(Model& model)
        : model(&model)
{ } */