#pragma once

#include <ge211.hxx>

/// Represents the state of the 2048 game.
class Model
{

public:
    // CONSTRUCTORS

    /// Constructs a 4x4 board (delegates to last constructor)
    Model();

    /// Constructs a size x size board (delegates to last constructor)
    explicit Model(int size);

    /// Constructs a width x height empty board,
    /// then places 2 starting tiles at random positions.
    ///
    /// ## Errors
    ///  - Throws 'ge211::Client_logic_error' if either dimension is
    ///     <3 or >10.
    Model(int width, int height);

    // HELPFUL TYPE ALIASES

    /// Board positions can be referenced using 'int' coordinates.
    using Position = ge211::Posn<int>;
    /// Used to define vector directions (ex. in shift_)
    using Dimensions = ge211::Dims<int>;
    /// Groups of board positions
    using Position_set = std::vector<Position>;

private:
    // PRIVATE DATA MEMBERS
    int width_;
    int height_;
    int score_;
    ge211::Random_source<int> random_number_source;
    bool gameover_;
    bool won_;
    std::vector<std::vector<int>> board_;
    // INVARIANT: Board[Valid Position] % 2 = 0
    // Note: Values of 0 are treated as empty.

public:
    // PUBLIC FUNCTIONS

    /// Prints to console the values stored at each position
    void print_board() const;

    /// Returns a Position_set containing all positions of the board,
    /// which can be used to iterate over the entire board.
    Position_set all_positions() const;

    /// Returns the `value` stored at `pos`.
    ///
    /// ## Errors
    ///  - throws `ge211::Client_logic_error` if `!in_bounds_(pos)`.
    int operator[](Model::Position pos) const;

    /// Getter for width_
    int get_width() const;

    /// Getter for height_
    int get_height() const;

    /// Getter for gameover_
    bool is_gameover() const;

    /// Getter for won_
    bool get_won() const;

    /// Given a 'Dimensions' indicating the directional arrow key pressed by
    /// the user, modify the board - shift and merge tiles as necessary -
    /// in the specified direction using 'shift_()'
    /// Then, check if the game is over.
    /// If the game is not over, and the 'shift_()' call \
    /// was a legal move (changed the board) spawn a new tile.
    /// Do not play a move if 'gameover_' is true.
    ///
    /// TL;DR: Actually play a move, shifting the board, checking for
    /// gameover, and only spawning a new block if the shift was a legal move.
    void play_move(Dimensions);

    /// Reset the board to be empty, then spawn 2 random starter tiles.
    /// also reset gameover_ and won_ to false, and reset score_ to 0.
    void restart();

private:
    // PRIVATE FUNCTIONS

    /// Return the value at the given board position
    int get_at_(Position pos) const;

    /// Set the value at the given board position
    void set_at_(Position pos, int val);

    /// Return a boolean corresponding to whether the input 'Position' is
    /// within the bounds of the board's size (a valid board position).
    bool in_bounds_(Position) const;

    /// Return a 'Dimensions' with the 'width' and 'height' components reversed.
    /// Equivalent to reflecting the vector represented by the 'Dimensions'
    /// over the line y=x.
    Dimensions inverse_(Dimensions) const;

    /// Return the 'Position' of either {0,0} or {width,height} for where to
    /// begin shift algorithm from depending on the user's input direction
    /// ({0,0} for left, up, {width,height} for right, down)
    Position choose_corner_(Dimensions) const;

    /// Increment score_ by a given value
    void increase_score_(int val);

    /// Shift the board based on input direction, corresponding to a arrow
    /// key input, as follows:
    ///     -All tiles are shifted in the input direction, stacking on other
    ///         blocks of different values (right arrow key -> shift right)
    ///     -If two tiles of the same value hit during the shift, they merge:
    ///         -Becoming one tile
    ///         -Of value equal to the sum of the two hitting tiles' values
    ///         -That shifts regularly in the input direction
    ///         -But can't merge again (stack even with other same value tiles)
    /// Return a boolean corresponding to whether the board changed as a
    /// result of the shift.
    bool shift_(Dimensions);

    /// Return a 'Position_set' corresponding to empty positions on the board
    Position_set empty_positions_() const;

    /// Add a (value 2 or 4) tile to the board at a random empty position.
    /// There is a 10% chance for a 4 tile, 90% chance for a 2 tile.
    void spawn_tile_();

    /// Return a boolean corresponding to whether or not there exists at
    /// least one tile on the board with the given value.
    bool is_in_board_(int val) const;

    /// Return a boolean corresponding to whether there exist any two
    /// adjacent tiles with the same value.
    /// This is logically equivalent to there being a possible move which
    /// causes two tiles to merge.
    bool is_board_mergable_() const;

    /// Check if the game was won. If not, spawn a new tile in an
    /// empty board position. Then check if the game was lost.
    void next_turn_();

    /// Allow Test_Access to access private functions for testing purposes
    friend struct Test_Access;
};
