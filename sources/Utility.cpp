#include "Utility.h"
#include <cstdlib>
#include <filesystem>

namespace utilities
{
    namespace assisstants
    {
        const std::string &getResourceBasePath()
        {
            static std::string basePath;
            if (!basePath.empty())
            {
                return basePath;
            }

            // 1) Environment variable override
            if (const char *envPath = std::getenv("CHESS_GAME_RESOURCES"))
            {
                std::filesystem::path candidate(envPath);
                if (std::filesystem::exists(candidate))
                {
                    basePath = candidate.string();
                    if (basePath.back() != '/')
                        basePath += "/";
                    return basePath;
                }
            }

            // 2) resources under current working directory
            std::filesystem::path cwd = std::filesystem::current_path();
            std::filesystem::path candidates[] = {
                cwd / "resources",
                cwd / "../resources",
                cwd / "../../resources",
            };
            for (const auto &p : candidates)
            {
                if (std::filesystem::exists(p))
                {
                    basePath = p.string();
                    if (basePath.back() != '/')
                        basePath += "/";
                    return basePath;
                }
            }

            // Fallback to repository layout relative to binary
            basePath = "../resources/";
            return basePath;
        }
        // color: color of the piece
        // type: type of the piece (King, Queen, Bishop, Knight, Rook, Pawn)
        string getPieceLocation(PieceColor color, PieceType type)
        {
            // location of folder containing images of pieces
            string location = getResourceBasePath() + "images/pieces/";

            // formula of file names: color + type + .png

            // the following conditional statements can be replaced by switch statements

            if (color == PieceColor::WHITE)
            {
                location += "White";
            }
            else if (color == PieceColor::BLACK)
            {
                // of course it will be black if it is not white =))
                location += "Black";
            }

            if (type == PieceType::KING)
            {
                location += "King";
            }
            else if (type == PieceType::QUEEN)
            {
                location += "Queen";
            }
            else if (type == PieceType::BISHOP)
            {
                location += "Bishop";
            }
            else if (type == PieceType::KNIGHT)
            {
                location += "Knight";
            }
            else if (type == PieceType::ROOK)
            {
                location += "Rook";
            }
            else if (type == PieceType::PAWN)
            {
                // of course it will be a pawn if it go to this case
                location += "Pawn";
            }

            location += ".png";

            return location;
        }

        string getSoundLocation(GameSound soundType)
        {
            // location of folder containing sound effects
            string location = getResourceBasePath() + "sounds/";

            // formula of file names: soundType + "Sound.ogg";
            // sound effects from this link:
            // https://github.com/mbusy/chess/tree/master/resources/sounds
            if (soundType == GameSound::CAPTURE)
            {
                location += "Capture";
            }
            else if (soundType == GameSound::CHECK)
            {
                location += "Check";
            }
            else if (soundType == GameSound::CHECKMATE)
            {
                location += "Checkmate";
            }
            else if (soundType == GameSound::MOVE)
            {
                location += "Move";
            }
            else if (soundType == GameSound::STALEMATE)
            {
                // of course it will be stalemate if it go to this case
                location += "Stalemate";
            }

            location += "Sound.ogg";

            return location;
        }

        // it will be a valid position on board if
        // x >= 0 && x < 8
        // and y >= 0 && y < 8
        // this function will be called to implement the other overloaded functions with the same name
        bool isOnBoardPosition(int x, int y)
        {
            return (x >= 0 && x < 8 && y >= 0 && y < 8);
        }

        bool isOnBoardPosition(const Vector2i &pos)
        {
            return isOnBoardPosition(pos.x, pos.y);
        }

        bool isOnBoardPosition(const ChessMove &move)
        {
            return isOnBoardPosition(move._position);
        }

        bool isOnWindowPosition(const Vector2i &pos)
        {
            bool condition1 = pos.x >= 0 && pos.x <= 8 * Settings::getCellSize();
            bool condition2 = pos.y >= 0 && pos.y <= 8 * Settings::getCellSize();

            return (condition1 && condition2);
        }

        // formula of converting functions from this link:
        // https://github.com/mbusy/chess/blob/master/src/utils/helpers.cpp
        Vector2f convertToDrawablePosition(int x, int y)
        {
            return convertToDrawablePosition(Vector2i(x, y));
        }

        Vector2f convertToDrawablePosition(const Vector2i &pos)
        {
            float cellSize = Settings::getCellSize();
            Vector2i cellOffset = Settings::getCellOffset();

            int xres = cellOffset.x + pos.y * cellSize;
            int yres = cellOffset.y + pos.x * cellSize;

            return Vector2f(xres, yres);
        }

        Vector2i convertToBoardIndex(float x, float y)
        {
            return convertToBoardIndex(Vector2f(x, y));
        }

        Vector2i convertToBoardIndex(const Vector2f &pos)
        {
            float cellSize = Settings::getCellSize();
            Vector2i cellOffset = Settings::getCellOffset();

            int xres = (pos.y - cellOffset.y) / cellSize;
            int yres = (pos.x - cellOffset.x) / cellSize;

            return Vector2i(xres, yres);
        }
    }
}