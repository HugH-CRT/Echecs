/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Header de Piece
 * @file Piece.h
 * @date 26/10/2021
 * @version 0.8
 */

#if !defined Piece_h
#define Piece_h

#include <iostream>
#include <assert.h>
#include <list>

using namespace std;

class ChessBoard;

class Piece
{
   protected:
    int  p_x;
    int  p_y;
    bool p_white;
    bool p_firstMove;
    bool p_isEchec;
    string p_path;

   public:
    virtual ~Piece();
    Piece( int x, int y, bool white, string path );
    void         Move( int x, int y );
    int          GetX();
    int          GetY();
    bool         GetIsWhite();
    bool         GetFirstMove();
    bool         GetIsEchec();
    void         SetIsEchec();
    string       GetPath();
    virtual list<string> DisplayAvailableMovement( ChessBoard &e, bool whitePlay ) = 0 ;
    list<string> CheckAvailableMovementKing( ChessBoard &e, int x, int y );
};

class Rook : virtual public Piece
{
   public:
    Rook( bool white, bool left, string path );
    ~Rook();
    list<string> DisplayAvailableMovement( ChessBoard &e, bool whitePlay );
};

class King : public Piece
{
   public:
    King( bool white, string path);
    ~King();
    bool CastlingAvailable( ChessBoard &e, Rook *r );
    list<string> DisplayAvailableMovement( ChessBoard &e, bool whitePlay );
};

class Bishop : virtual public Piece
{
   public:
    Bishop( bool white, bool left, string path );
    ~Bishop();
    list<string> DisplayAvailableMovement( ChessBoard &e, bool whitePlay );
};

class Knight : public Piece
{
   public:
    Knight( bool white, bool gauche, string path );
    ~Knight();
    list<string> DisplayAvailableMovement( ChessBoard &e, bool whitePlay );
};

class Queen : public Bishop, public Rook
{
   public:
    Queen( bool white, string path );
    ~Queen();
    list<string> DisplayAvailableMovement( ChessBoard &e, bool whitePlay );
};

class Pawn : public Piece
{
   public:
    Pawn( bool white, int x, string path );
    ~Pawn();
    bool DoitEvoluer( ChessBoard &e,bool whitePlay );
    list<string> DisplayAvailableMovement( ChessBoard &e, bool whitePlay );
};

#endif

