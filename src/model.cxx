#include "model.hxx"
#include <iostream>

Model::Model()
        : score_(0)
{
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            board_[i][j] = 0;
        }
    }
}

void
Model::print_board_() const
{
    for (int i = 0; i<4; i++){
        for (int j = 0; j<4; j++){
            std::cout << board_[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

bool
Model::in_bounds_(Model::Position pos)
{
    return (pos.x>=0 && pos.x<width_) && (pos.y>=0 && pos.y<height_);
}

void
Model::set_at_(Model::Position pos, int n)
{
    board_[pos.x][pos.y] = n;
}

int
Model::get_at_(Model::Position pos) const
{
    return board_[pos.x][pos.y];
}


Model::Dimensions
Model::inverse_(Model::Dimensions dims)
{
    return {dims.height,dims.width};
}

Model::Position
Model::choose_corner_(Model::Dimensions dir)
{
    //Position start = {0,0}; if dir = {1,0} or {0,1}
    //Position start = {w-1,h-1}; if dir = {-1,0} or {0,-1}
    if (dir.width > 0 || dir.height > 0) return {0,0};
    return {width_-1,height_-1};
}

void
Model::shift(Model::Dimensions dir)
{
    ///NOTE: Because of how arrays-in-arrays work...
    /// -The x coordinate of dir corresponds to the row, so {1,0} means down
    /// -The y coordinate of dir corresponds to the column, so {0,1} means right
    /// To make shift() work intuitively, dir is immediately inverted and =*-1:
    dir = inverse_(dir);
    dir *= -1;
    ///This way, an input of {1,0} = right arrow = shift right,
    ///                      {0,-1} = up arrow = shift up (y decreasing)

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
            //if b_val == a_val, set b*=2, set a to 0, then a++, b++
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
}

Model::Position_set
Model::empty_positions_()
{
    Position_set empty_positions;
    for (int i = 0; i<4; i++){
        for (int j = 0; j<4; j++){
            if (board_[i][j] == 0) empty_positions.push_back({i,j});
        }
    }
    return empty_positions;
}
