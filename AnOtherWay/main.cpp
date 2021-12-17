#include "ChessBoard.h"

int main() {
    //std::cout << "No compilation error\n";

    string name = "Chess game";
    int width = 800;
    int length = 800;

    RenderWindow window(VideoMode(width, length), name, Style::Titlebar);

    window.setFramerateLimit(120);
    window.setTitle(name);

    ChessBoard chessboard(name, window);
    chessboard.run();

    return 0;
}