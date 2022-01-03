#include "ChessBoard.h"

int main() {
    
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

    return 0;
}