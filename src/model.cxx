#include "model.hxx"
#include <iostream>
#include <ge211.hxx>

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
          random_number_source(ge211::unbounded)
{
    std::vector<int> row(width, 0);
    for (int i = 0; i < height; i++) {
        board_.push_back(row);
    }

    //spawn starting tiles
    spawn_tile_();
    spawn_tile_();
}

int
Model::operator[](Model::Position pos) const
{
    return get_at_(pos);
}

void
Model::print_board() const
{
    for (int i = 0; i<width_; i++){
        for (int j = 0; j<height_; j++){
            std::cout << get_at_({i,j}) << "\t";
        }
        std::cout << "\n";
    }
}

bool
Model::in_bounds_(Model::Position pos) const
{
    return (pos.x>=0 && pos.x<width_) && (pos.y>=0 && pos.y<height_);
}
int
Model::get_width() const
{
    return this->width_;
}
int
Model::get_height() const
{
    return this->height_;
}



///NOTE: Because of how arrays-in-arrays work (for get_at_ and set_at_)...
///the first index represents the row number, in this case is the y-coordinate
///the second index represents the column number, in this case the x-coordinate
///Therefore, to make manipulating the board more intuitive, our get and set
///functions are defined as below:

void
Model::set_at_(Model::Position pos, int n)
{
    board_[pos.y][pos.x] = n;
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
Model::shift(Model::Dimensions dir)
{
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
    // std::cout << choose_corner(dir) << "\n";

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
            }
            else if (behind_val > 0) behind += dir; //dif val, so move forward
                // to look for place to insert ahead_val
            else { //behind empty, ahead nonempty
                set_at_(behind, ahead_val);
                set_at_(ahead, 0);
                ahead += dir;
            }
        }

    }

    //spawn new tile
    spawn_tile_();

    ///for debug
    print_board();
    std::cout << "\n";
}

void
Model::increase_score_(int x)
{
    score_ += x;
}

Model::Position_set
Model::empty_positions_() const
{
    Position_set empty_positions;
    for (int i = 0; i<width_; i++){
        for (int j = 0; j<height_; j++){
            if (0==get_at_({i,j}))
            {
                empty_positions.push_back({i, j});
            }
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