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
#include <list>

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
    bool p_isEchec;

   public:
    virtual ~Piece();
    Piece( int x, int y, bool white, string path);
    void         move( int x, int y );
    int          x();
    int          y();
    bool         isWhite();
    bool         firstMove();
    bool         isEchec();
    void setIsEchec();
    string       path();
    virtual list<string> AfficheMouvementValide(Echiquier &e, bool whitePlay) = 0 ;
    list<string> MouvementPossibleRoi(Echiquier &e, int x, int y );
};


class Tour : virtual public Piece
{
   public:
    Tour( bool white, bool gauche, string path );
    ~Tour();
    list<string> AfficheMouvementValide(Echiquier &e, bool whitePlay);
};

class Roi : public Piece
{
   public:
    Roi( bool white, string path);
    ~Roi();
    bool roquePossible( Echiquier &e, Tour *p);
    list<string> AfficheMouvementValide(Echiquier &e, bool whitePlay);
};

class Fou : virtual public Piece
{
   public:
    Fou( bool white, bool gauche, string path );
    ~Fou();
    list<string> AfficheMouvementValide(Echiquier &e, bool whitePlay);
};

class Cavalier : public Piece
{
   public:
    Cavalier( bool white, bool gauche, string path );
    ~Cavalier();
    list<string> AfficheMouvementValide(Echiquier &e, bool whitePlay);
};

class Reine : public Fou, public Tour
{
   public:
    Reine( bool white, string path );
    ~Reine();
    list<string> AfficheMouvementValide(Echiquier &e, bool whitePlay);
};

class Pion : public Piece
{
   public:
    Pion( bool white, int x, string path );
    ~Pion();
    bool DoitEvoluer(Echiquier &e,bool whitePlay );
    list<string> AfficheMouvementValide(Echiquier &e, bool whitePlay);
};

#endif

