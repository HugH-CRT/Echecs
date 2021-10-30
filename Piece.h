/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Header de Piece
 * @file Piece.h
 * @date 26/10/2021
 * @version 0.5
 */

#if !defined Piece_h
#define Piece_h

#include <iostream>
#include <assert.h>

using namespace std;

class Echiquier;

class Piece
{
   protected:
    int  m_x;
    int  m_y;
    bool m_white;
    bool p_firstMove;
    string p_path;

   public:
    virtual ~Piece();
    Piece();
    Piece( int x, int y, bool white, string path);
    void         move( int x, int y );
    int          x();
    int          y();
    bool         isWhite();
    bool         firstMove();
    string       path();
    virtual bool mouvementValide( Echiquier &e, int x, int y ) = 0;
    bool Echec(Echiquier &e, int x, int y);
    bool EchecMat(Echiquier &e, int x, int y );
};


class Tour : virtual public Piece
{
   public:
    Tour( bool white, bool gauche, string path );
    ~Tour();
    bool mouvementValide( Echiquier &e, int x, int y );
    bool MouvementRealise();
};

class Roi : public Piece
{
   public:
    Roi( bool white, string path );
    ~Roi();
    bool mouvementValide( Echiquier &e, int x, int y );
    bool roquePossible( Echiquier &e, Tour *p);
};

class Fou : virtual public Piece
{
   public:
    Fou( bool white, bool gauche, string path );
    ~Fou();
    bool mouvementValide( Echiquier &e, int x, int y );
};

class Cavalier : public Piece
{
   public:
    Cavalier( bool white, bool gauche, string path );
    ~Cavalier();
    bool mouvementValide( Echiquier &e, int x, int y );
};

class Reine : public Fou, public Tour
{
   public:
    Reine( bool white, string path );
    ~Reine();
    bool mouvementValide( Echiquier &e, int x, int y );
};

class Pion : public Piece
{
   public:
    Pion( bool white, int x, string path );
    ~Pion();
    bool mouvementValide( Echiquier &e, int x, int y );
    void AfficheMouvementValide(Echiquier &e);
};

#endif

