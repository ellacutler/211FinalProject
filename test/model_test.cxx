#include "model.hxx"
#include <ge211.hxx>
#include <catch.hxx>
#include <iostream>

using Position = ge211::Posn<int>;
using Dimensions = ge211::Dims<int>;
using Position_set = std::vector<Position>;
int board_array[4][4] = { {2, 0, 2, 4},
                          {0, 2, 4, 0},
                          {16, 0, 2, 8},
                          {2, 4, 2, 4}};

static void
set_at(Position pos, int n);
static int
get_at(Position pos);
static void
print_board();
static bool
in_bounds(Position);
static Dimensions
inverse(Dimensions);
static Position
choose_corner(Dimensions);
static void
shift(Dimensions);

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

TEST_CASE("writing shifter function")
{

    // set_at({0,0}, 2); //WORKS!!!
    // print_board();
    // std::cout << "\n";

    //using the following, could easily make it adaptable tho
    // int w = 4;
    // int h = 4;


    ///TRY UNCOMMENTING ONE OF THESE LINES AND CHANGING THE BOARD_ARRAY ABOVE
    ///TO SEE THE SHIFT WORKING!!!!
    //Dimensions dir = {-1,0}; //left input
    // Dimensions dir = {1,0}; //right input
    Dimensions dir = {0,-1}; //up input
    // Dimensions dir = {0,1}; //down input
    std::cout << "Shift direction: " << dir << "\n";
    std::cout << "Pre-Shift: \n";
    print_board();
    std::cout << "Post-Shift: \n";
    shift(dir);
    print_board();
}

TEST_CASE("writing functions for shifting/combining")
{
    // int board_array[4][4] = { {1, 0, 0, 0},
    //                           {0, 2, 0, 0},
    //                           {0, 0, 3, 0},
    //                           {0, 0, 0, 4}};

    // print_board();

    ///empty_postitions_()
    Position_set empty_positions;
    for (int i = 0; i<4; i++){
        for (int j = 0; j<4; j++){
            if (board_array[i][j] == 0) empty_positions.push_back({i,j});
        }
    }

    // //return empty_positions
    // std::cout << "empty_positions_(): \n";
    // for (Position pos : empty_positions){
    //     std::cout << pos << "\n";
    // }
}

static int
get_at(Position pos)
{
    return board_array[pos.x][pos.y];
}

static void
set_at(Position pos, int n)
{
    board_array[pos.x][pos.y] = n;
}

static bool
in_bounds(Position pos)
{
    //instead of 4, do w,h of board
    return (pos.x>=0 && pos.x<4) && (pos.y>=0 && pos.y<4);
}

static Dimensions
inverse(Dimensions dims)
{
    return {dims.height,dims.width};
}

static Position
choose_corner(Dimensions dir)
{
    //w,h instead of 4
    //Position start = {0,0}; if dir = {1,0} or {0,1}
    //Position start = {w-1,h-1}; if dir = {-1,0} or {0,-1}
    if (dir.width > 0 || dir.height > 0) return {0,0};
    return {4-1,4-1};
}

static void
shift(Dimensions dir)
{
    ///NOTE: Because of how arrays-in-arrays work...
    /// -The x coordinate of dir corresponds to the row, so {1,0} means down
    /// -The y coordinate of dir corresponds to the column, so {0,1} means right
    /// To make shift() work intuitively, dir is immediately inverted and =*-1:
    dir = inverse(dir);
    dir *= -1;
    ///This way, an input of {1,0} = right arrow = shift right,
    ///                      {0,-1} = up arrow = shift up (y decreasing)

    ///for debug
    // std::cout << choose_corner(dir) << "\n";

    for (Position start = choose_corner(dir); in_bounds(start);
         start+=inverse(dir))
    {
        Position behind = start;
        Position ahead = start+dir;

        ///for debug
        // std::cout << behind << " :b|a: " << ahead << "\n";

        //shift, merge, etc
        while (in_bounds(ahead)) {
            //if a's pos == b's pos, a++
            //if nothing at a, a++
            //if b_val == a_val, set b*=2, set a to 0, then a++, b++
            //if b_val!= a_val != 0, b++
            //if something at a but not b, set b to a_val, set a to 0, a++
            int ahead_val = get_at(ahead);
            int behind_val = get_at(behind);

            /// for debug
            // std::cout << behind << " :b|val: " << behind_val << "\t|\t" << ahead
            // << " :a|val: " << ahead_val << "\n";

            if (ahead == behind) ahead += dir; //overlapping positions
            else if (ahead_val == 0) ahead += dir; //ahead is empty
            else if (behind_val == ahead_val) { //same val, so merge
                set_at(behind,2*behind_val);
                set_at(ahead,0);
                behind += dir;
                ahead += dir;
            }
            else if (behind_val > 0) behind += dir; //dif val, so move forward
                // to look for place to insert ahead_val
            else { //behind empty, ahead nonempty
                set_at(behind, ahead_val);
                set_at(ahead, 0);
                ahead += dir;
            }
        }

    }
}

//could do board_old == board_new for each input to see if no valid moves

static void
print_board()
{
    for (int i = 0; i<4; i++){
        for (int j = 0; j<4; j++){
            std::cout << board_array[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//
