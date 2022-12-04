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
    void check_positions(const std::vector<int> &vect);
    bool game_over();

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
void
Test_access::set_manual_positions(const std::vector<int> &vect)
{
    Position_set all_pos = all_positions();
    for (size_t i = 0; i<vect.size(); i++) {
        model.set_at_(all_pos[i], vect[i]);
    }
}
void
Test_access::check_positions(const std::vector<int> &vect)
{
    Position_set all_pos = all_positions();
    for (size_t i = 0; i<vect.size(); i++) {
        if (model.get_at_(all_pos[i]) != vect[i]) {
            std::cout << "Fail at: " << all_pos[i] << "\n";
        }
        CHECK(model.get_at_(all_pos[i]) == vect[i]);
    }
}
bool
Test_access::game_over(){
    return model.gameover_;
}

///MODEL TESTS

TEST_CASE(" aa starting condition test")
{
    /*
     * Starting moves -
     * initialize the game,
     * press a few buttons,
     * check that stuff is created and merges correctly,
     * score increases correctly.
     */
    std::cout << "\n----------STARTING CONDITION TEST----------\n";
    Model model(4,4, {1,1}, {2,2} );
    Test_access access(model);
    // sets intial values at 1,1 and 2,2
    CHECK_FALSE(model.is_gameover());
    CHECK(model.get_score() == 0);
    model.print_board();
    access.check_positions({
        0,0,0,0,
        0,2,0,0,
        0,0,2,0,
        0,0,0,0,
    });

    model.play_move({-1,0});
    model.print_score();
    CHECK((model.get_score() == 0));
    model.print_board();
    access.check_positions({
        0,0,2,0,
        2,0,0,0,
        2,0,0,0,
        0,0,0,0,
    });

    // shift the board down...
    model.play_move({0,1});
    model.print_score();
    CHECK(model.get_score() == 4);
    model.print_board();
    access.check_positions({
           0,0,2,0,
           0,0,0,0,
           0,0,0,0,
           4,0,2,0,
    });

    std::cout << "--------------------------------------\n";
}

// model tests run in order hence the aa, bb, etc.
TEST_CASE("bb complex merging test")
{
    std::cout << "\n----------COMPLEX MERGING TEST----------\n";
    Model model(4,4, {1,1}, {2,2});
    Test_access access(model);
    access.set_all_positions(2);
    access.print_board();
    access.check_positions({
           2,2,2,2,
           2,2,2,2,
           2,2,2,2,
           2,2,2,2,
    });
    CHECK(access.is_board_mergable() == true);

    model.play_move({-1,0});
    access.print_board();
    access.check_positions({
           4,4,0,0,
           4,4,2,0,
           4,4,0,0,
           4,4,0,0,
    });
    CHECK(model.get_score() == 32);

    model.play_move({0,-1});
    CHECK(model.get_score() == 64);
    access.print_board();
    access.check_positions({
           8,8,2,0,
           8,8,0,2,
           0,0,0,0,
           0,0,0,0,
    });

    model.play_move({0,1});
    model.print_score();
    CHECK(model.get_score() == 96);
    model.print_board();
    access.check_positions({
           0,0,2,0,
           0,0,0,0,
           0,0,0,0,
           16,16,2,2,
    });
    std::cout << "--------------------------------------\n";
}
TEST_CASE("game win")
{
    std::cout << "\n----------GAME WIN TEST----------\n";
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
    access.print_board();
    access.check_positions({
           1024,512,0,0,
           2,512,0,0,
           0,0,0,0,
           0,0,0,0,
    });

    model.play_move({0,-1});
    access.print_board();
    access.check_positions({
           1024,1024,0,0,
           2,2,0,0,
           0,0,0,0,
           0,0,0,0,
    });
    CHECK(model.get_won()== false);

    model.play_move({-1,0});
    access.print_board();
    access.check_positions({
           2048,0,0,0,
           4,0,0,0,
           0,0,0,0,
           0,0,0,0,
    });
    CHECK(model.get_won() == true);
    CHECK(model.is_gameover()==true);
    std::cout << "--------------------------------------\n";
}
TEST_CASE("game lose")
{
    std::cout << "\n----------GAME LOSE TEST----------\n";
    Model model(4,4, {1,1}, {2,2} );
    Test_access access(model);
    access.set_manual_positions(
            {256,16,32, 4,
             4,128, 1024, 8,
             32,0, 8, 64,
             256,16, 256, 8}
    );
    access.print_board();
    CHECK(model.get_won()== false);
    CHECK(access.is_board_mergable()==false);
    CHECK(access.game_over() == false);

    model.play_move({0,1});
    access.check_positions({
           256,2,32, 4,
           4,16, 1024, 8,
           32,128, 8, 64,
           256,16, 256, 8
    });
    access.print_board();


    CHECK(model.get_won()== false);
    CHECK(access.is_board_mergable()==false);
    CHECK(access.game_over() == true);
    std::cout << "--------------------------------------\n";
}
TEST_CASE("More complex merging")
{
    std::cout << "\n----------MERGING TEST 2----------\n";
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
    access.check_positions({
           256,256,32,4,
           8,16,4,8,
           256,0,8,64,
           0,2,256,8
    });
    access.print_board();

    model.play_move({-1,0});
    access.check_positions({
           512,32,4,0,
           8,16,4,8,
           256,8,64,0,
           2,256,8,2,
    });
    access.print_board();


    CHECK(model.get_won()== false);
    CHECK(access.is_board_mergable()==true);
    CHECK(access.game_over() == false);
    std::cout << "--------------------------------------\n";
}



