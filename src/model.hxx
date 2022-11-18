#pragma once

#include <ge211.hxx>

class Model
{

public:
    Model();
    Model(int size);
    Model(int width, int height);

    using Position = ge211::Posn<int>;
    using Dimensions = ge211::Dims<int>;
    using Position_set = std::vector<Position>;

    void shift(Dimensions);

    void print_board() const;

    int operator[](Model::Position pos) const;

private:
    int width_;
    int height_;
    int score_;
    int** board_;

    void set_at_(Position pos, int n);

    int get_at_(Position pos) const;

    bool in_bounds_(Position) const;

    Dimensions inverse_(Dimensions) const;

    Position choose_corner_(Dimensions) const;

    Position_set empty_positions_() const;

    void increase_score_(int x);

    friend struct Test_Access;
};
