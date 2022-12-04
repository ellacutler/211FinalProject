#include "model.hxx"
#include <iostream>
#include <ge211.hxx>
#include <algorithm>
#include <vector>

Model::Model()
        : Model(4,4)
{ }


Model::Model(int size)
        : Model(size, size)
{ }

Model::Model(int width, int height)
        : width_(width),
          height_(height),
          score_(0),
          random_number_source(ge211::unbounded),
          gameover_(false),
          won_(false)
{
    //for getting about-to-win or about-to-lose states
    // 1111 -> about to win 3x3
    // 2222 -> about to lose 3x3
    if (width == 1111) {
        width_ = 3;
        height_ = 3;
        std::vector<int> row(width, 0);
        for (int i = 0; i < height; i++) {
            board_.push_back(row);
        }
        board_[2][2] = 1024;
        board_[1][2] = 1024;
        return;
    }
    if (width == 2222) {
        width_ = 3;
        height_ = 3;
        std::vector<int> row(width, 0);
        for (int i = 0; i < height; i++) {
            board_.push_back(row);
        }
        board_[0][0] = 2;
        board_[0][1] = 4;
        board_[0][1] = 8;
        board_[0][2] = 16;
        board_[1][0] = 32;
        board_[1][1] = 64;
        board_[1][2] = 128;
        board_[2][0] = 256;
        board_[2][1] = 512;
        // note: board_[2][2] = 0;
        return;
    }

    //throw errors if dims too large/too small
    if (width > 10 || height > 10) {
        throw ge211::Client_logic_error("Board::Board: dims too large");
    } else if (width < 3 || height < 3) {
        throw ge211::Client_logic_error("Board::Board: dims too small");
    }


    std::vector<int> row(width, 0);
    for (int i = 0; i < height; i++) {
        board_.push_back(row);
    }

    //spawn starting tiles (2)
    spawn_tile_();
    spawn_tile_();
}
// For testing
Model::Model(int width, int height, ge211::Posn<int> test1, ge211::Posn<int>
        test2)
        : width_(width),
          height_(height),
          score_(0),
          random_number_source(ge211::unbounded),
          gameover_(false),
          won_(false)
{
    //throw errors if dims too large/too small
    if (width > 10 || height > 10) {
        throw ge211::Client_logic_error("Board::Board: dims too large");
    } else if (width < 3 || height < 3) {
        throw ge211::Client_logic_error("Board::Board: dims too small");
    }


    std::vector<int> row(width, 0);
    for (int i = 0; i < height; i++) {
        board_.push_back(row);
    }
    // non-random start positions, rng stub so that it's easier to test
    set_at_(test1, 2);
    set_at_(test2,2);
    random_number_source.stub_with(2);
}

int
Model::operator[](Model::Position pos) const
{
    if (in_bounds_(pos)) return get_at_(pos);
    throw std::logic_error("Accessed board position is out of bounds.");
}

void
Model::print_board() const
{
    for (int j = 0; j<height_; j++){
        for (int i = 0; i<width_; i++){
            std::cout << get_at_({i, j}) << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
void
Model::print_score() const
{
    std::cout << score_ << "\n";
}

bool
Model::in_bounds_(Model::Position pos) const
{
    return (pos.x>=0 && pos.x<width_) && (pos.y>=0 && pos.y<height_);
}

int
Model::get_width() const
{
    return width_;
}

int
Model::get_height() const
{
    return height_;
}

bool
Model::is_gameover() const
{
    return gameover_;
}

bool
Model::get_won() const
{
    return won_;
}

int
Model::get_score() const
{
    return score_;
}

///Actually play a move, shifting the board, checking for gameover and only
// spawning a new block if the shift was a legal move

void
Model::play_move(Dimensions dir)
{
    //disallow moves if game is over
    if (gameover_) {
        return;
    }

    bool board_changed = shift_(dir);
    if (board_changed) next_turn_();

    ///for debug
    // print_board();
    // std::cout << "\n";
}

///NOTE: Because of how arrays-in-arrays work (for get_at_ and set_at_)...
///the first index represents the row number, in this case is the y-coordinate
///the second index represents the column number, in this case the x-coordinate
///Therefore, to make manipulating the board more intuitive, our get and set
///functions are defined as below:

void
Model::set_at_(Model::Position pos, int val)
{
    board_[pos.y][pos.x] = val;
}

int
Model::get_at_(Model::Position pos) const
{
    return board_[pos.y][pos.x];
}


Model::Dimensions
Model::inverse_(Model::Dimensions dims) const
{
    return {dims.height,dims.width};
}

Model::Position
Model::choose_corner_(Model::Dimensions dir) const
{
    //Position start = {0,0}; if dir = {1,0} or {0,1}
    //Position start = {w-1,h-1}; if dir = {-1,0} or {0,-1}
    if (dir.width > 0 || dir.height > 0) return {0,0};
    return {width_-1,height_-1};
}

void
Model::increase_score_(int val)
{
    score_ += val;
}

bool
Model::shift_(Model::Dimensions dir)
{
    ///for debug
    // std::cout << dir << "\n";

    //for returning whether or not board has changed as a result of the shift
    bool board_changed = false;

    ///To shift the board to the right, we want to start on the right and
    /// travel to the left, replacing any empty tiles (0's) with ones from
    /// further to the left. For this reason, to make this function more
    /// intuitive to use, we immediately negate the INPUT DIRECTION to
    /// get the direction along which we will TRAVEL
    dir *= -1;
    ///This way:
    ///     right arrow => shift({1,0}) => shift right, travel left
    ///     up arrow => shift({0,-1}) => shift up (y decreasing), travel down

    ///for debug
    // std::cout << choose_corner_(dir) << "\n";

    for (Position start = choose_corner_(dir); in_bounds_(start);
         start+=inverse_(dir))
    {
        Position behind = start;
        Position ahead = start+dir;

        ///for debug
        // std::cout << behind << " :b|a: " << ahead << "\n";

        //shift, merge, etc
        while (in_bounds_(ahead)) {
            //if a's pos == b's pos, a++
            //if nothing at a, a++
            //if b_val == a_val, set b*=2, score+=b*2, set a to 0, then a++, b++
            //if b_val!= a_val != 0, b++
            //if something at a but not b, set b to a_val, set a to 0, a++
            int ahead_val = get_at_(ahead);
            int behind_val = get_at_(behind);

            /// for debug
            // std::cout << behind << " :b|val: " << behind_val << "\t|\t" << ahead
            // << " :a|val: " << ahead_val << "\n";

            if (ahead == behind) ahead += dir; //overlapping positions
            else if (ahead_val == 0) ahead += dir; //ahead is empty
            else if (behind_val == ahead_val) { //same val, so merge
                set_at_(behind,2*behind_val);
                increase_score_(2*behind_val);
                set_at_(ahead,0);
                behind += dir;
                ahead += dir;
                board_changed = true;
            }
            else if (behind_val > 0) behind += dir; //dif val, so move forward
                // to look for place to insert ahead_val
            else { //behind empty, ahead nonempty, set behind to ahead_val
                set_at_(behind, ahead_val);
                set_at_(ahead, 0);
                ahead += dir;
                board_changed = true;
            }
        }

    }
    return board_changed;
}

Model::Position_set
Model::empty_positions_() const
{
    Position_set empty_positions;
    for (Position pos : all_positions()){
        if (0 == get_at_(pos)) {
            empty_positions.push_back(pos);
        }
    }
    return empty_positions;
}

void
Model::spawn_tile_()
{
    Position_set empty_pos = empty_positions_();
    //get a random element of empty_pos, set it to value of 2 or 4
    int loc = random_number_source(0,empty_pos.size()-1);
    int val = random_number_source(1,10) == 1 ? 4 : 2; //10% chance of 4
    set_at_(empty_pos.at(loc), val);

    ///debug
    //std::cout << val << " spawing at: " << empty_pos.at(loc) << "\n";
}

bool
Model::is_in_board_(int val) const
{
    for (Position pos : all_positions()) {
        if (get_at_(pos) == val) return true;
    }
    return false;
}

bool
Model::is_board_mergable_() const
{


    // iterate through the board, checking the number TO THE RIGHT and BELOW
    // each one.
    // If this number is the same, return true.
    // Return false at the end if this is not the case anywhere on the board.

    // iterate through the board,
    // checking the number TO THE RIGHT and BELOW each one.
    // If this number is the SAME, return TRUE.
    // Return FALSE at the end if this is not the case anywhere on the board.


    int cur;
    for (int j = 0; j<height_; j++){
        for (int i = 0; i<width_; i++){
            cur = get_at_({i,j});
            if (cur==0) continue;
            if (i+1<width_ && (get_at_({i+1,j}) == cur)) return true;
            if (j+1<height_ && (get_at_({i,j+1}) == cur)) return true;
        }
    }
    return false;
}

void
Model::next_turn_()
{
    // check if game won
    if (is_in_board_(2048)) {
        gameover_ = true;
        won_ = true;
        return;
    }
    spawn_tile_();
    // check if game lost
    if (empty_positions_().empty() && !is_board_mergable_()) {
        gameover_ = true;
        return;
    }
}

Model::Position_set
Model::all_positions() const
{
    Position_set result;
    for (int j = 0; j<height_; j++) {
        for (int i = 0; i < width_; i++) {
            result.push_back({i,j});
        }
    }
    return result;
}

void
Model::restart()
{

    score_ = 0;
    gameover_ = false;
    won_ = false;
    //reset board
    for (Position pos : all_positions()) {
        set_at_(pos,0);
    }
    //spawn starting tiles (2)
    spawn_tile_();
    spawn_tile_();
}

void
Model::set_all_positions(int i)
{

    for (Position pos : all_positions()) {
        set_at_(pos,i);

    }
}