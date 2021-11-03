/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Header de ChessBoard
 * @file ChessBoard.h
 * @date 26/10/2021
 * @version 0.5
 */

#if !defined ChessBoard_h
#define ChessBoard_h
#include "Piece.h"

class ChessBoard
{
   private:
    Piece *m_cases[64];

   public:

    ChessBoard();
    Piece *GetPiece( int x, int y );
    bool PlacePiece( Piece *p );
    void MovePiece( Piece *p, int x, int y );
    void RemovePiece( int x, int y );
    bool CheckRoqueValidity( King *r, int x ,int y);
    void DoRoque( King *r, Rook *p);
};

#endif
