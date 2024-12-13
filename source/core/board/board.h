#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <memory>

class IPiece;

struct Case
{
    IPiece* piece;
    bool b_isEmpty = false;
};

class ChessBoard final
{
public:
    ChessBoard();
    ~ChessBoard();

private:
    std::vector<std::unique_ptr<Case>> m_cases;
};


#endif // CHESSBOARD_H
