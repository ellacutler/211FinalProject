#pragma once

#include <ge211.hxx>

class Model
{

public:
    Model();
    Model(int size);
    Model(int width, int height);
    Model(int width, int height, ge211::Posn<int> test1,ge211::Posn<int>
            test2 );

    using Position = ge211::Posn<int>;
    using Dimensions = ge211::Dims<int>;
    using Position_set = std::vector<Position>;

    void print_board() const;
    void print_score() const;
    Position_set all_positions() const;
    // accesses board positions and returns value at stated position
    int operator[](Model::Position pos) const;
    int get_width() const;
    int get_height() const;
    bool get_won() const;
    bool is_gameover() const;
    int get_score() const;
    void play_move(Dimensions);

    void restart();

    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;



private:
    int width_;
    int height_;
    int score_;
    ge211::Random_source<int> random_number_source;
    bool gameover_;
    bool won_;
    std::vector<std::vector<int>> board_;

    int get_at_(Position pos) const;
    void set_at_(Position pos, int n);

    bool in_bounds_(Position) const;
    Dimensions inverse_(Dimensions) const;
    Position choose_corner_(Dimensions) const;
    void increase_score_(int x);
    bool shift_(Dimensions);

    Position_set empty_positions_() const;
    void spawn_tile_(Position_set);
    bool is_in_board_(int x) const;
    bool is_board_mergable_() const;
    void next_turn_();

    friend struct Test_Access;
};
