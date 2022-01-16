#include "ChessBoard.h"

int main() {
    
    //use try-throw-catch to handle exceptions
    try {
    string name = "Chess game";
    int width = 800;
    int length = 800;

    RenderWindow window(VideoMode(width, length), name, Style::Titlebar);

    window.setFramerateLimit(120);
    window.setTitle(name);

    ChessBoard chessboard(name, window);
    chessboard.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch(...) {
        std::cerr << "Unknown error" << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}