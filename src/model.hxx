#pragma once

#include <ge211.hxx>

class Model
{

public:
    Model();

    using Position = ge211::Posn<int>;
    using Dimensions = ge211::Dims<int>;
    using Position_set = std::vector<Position>;

    friend struct Test_Access;

private:
    int board_[4][4];
    int score_;

    void set_at_(Position pos, int n);

    int get_at_(Position pos) const;

    void print_board_() const;

    bool in_bounds_(Position);

    Dimensions inverse_(Dimensions);

    Position choose_corner_(Dimensions);

    void shift_(Dimensions);

};
