#include "model.hxx"

Model::Model()
        : turn_('X'),
          winner_(' '),
          score_(0)
{
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            squares_[i][j] = 'X';
        }
    }
}

void
Model::set_at_(Model::Position pos, int n)
{

}

int
Model::get_at_(Model::Position pos) const
{
    return board_[pos.x][pos.y];
}

void
Model::print_board_() const
{}

bool
Model::in_bounds_(Model::Position)
{}

Model::Dimensions
inverse_(Model::Dimensions)
{

}

Model::Position
choose_corner_(Model::Dimensions)
{

}

void
shift_(Model::Dimensions)
{

}