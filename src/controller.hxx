#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

// The main game class for 2048
class Controller : public ge211::Abstract_game
{
public:

    /// Constructs a game with a width x height empty board,
    /// then places 2 starting tiles at random positions.
    ///
    /// ## Errors
    ///  - Throws 'ge211::Client_logic_error' if either dimension is
    ///     <3 or >10.
    Controller(int width, int height);


protected:
    /// Quit on 'q', Restart on 'r', shift board on arrow key input using
    /// 'play_move(Direction corresponding to arrow key)'.
    void on_key_down(ge211::events::Key) override;

    // Functions delegated to the view
    void draw(ge211::Sprite_set& set) override;
    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    // Model and View pieces of the M-V-C structure.
    Model model_;
    View view_;
};
