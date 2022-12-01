#include "controller.hxx"
#include <iostream>
#include <typeinfo>

int
main(int argc, char *argv[])
{
    try {
        int width;
        int height;
        switch (argc) {
        case 1:
            width = 4;
            height = 4;
            break;
        case 2:
            width = std::stoi(argv[1]);
            height = width;
            break;
        case 3:
            width = std::stoi(argv[1]);
            height = std::stoi(argv[2]);
            break;
        default:
            std::cerr << "Usage: " << argv[0] << " [WIDTH HEIGHT]\n";
            return 1;
        }

        Controller(width, height).run();

    } catch (std::exception const& e) {
        // This prints out error messages if the command-line argument
        // cannot be parsed as `int`s.
        std::cerr << argv[0] << ": " << e.what() << "\n";
        return 1;
    }
    return 0;
}
