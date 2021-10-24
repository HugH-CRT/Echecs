/**
 * Header de Piece.cxx
 *
 * @file Piece.h
 */

#if !defined Piece_h
#define Piece_h

//#include "Echiquier.h"
class Echiquier;  // pb de reference croisee

/**
 * Declaration d'une classe modelisant une piece de jeu d'echec.
 */
class Piece
{
   protected:
    int  m_x;
    int  m_y;
    bool m_white;
    bool firstMove;

   public:
    virtual ~Piece();
    Piece();
    Piece( int x, int y, bool white );
    Piece( const Piece &autre );
    Piece &      operator=( const Piece &autre );
    void         init( int x, int y, bool white );
    void         move( int x, int y );
    int          x();
    int          y();
    bool         isWhite();
    bool         isBlack();
    void         affiche();
    virtual char vue();
    virtual bool mouvementValide( Echiquier &e, int x, int y ) = 0;
};

class Roi : public Piece
{
   public:
    Roi( bool white );
    ~Roi();
    char vue();
    bool mouvementValide( Echiquier &e, int x, int y );
    void roque();
};

class Tour : virtual public Piece
{
   public:
    Tour( bool white, bool gauche );
    ~Tour();
    char vue();
    bool mouvementValide( Echiquier &e, int x, int y );
};

class Fou : virtual public Piece
{
   public:
    Fou( bool white, bool gauche );
    ~Fou();
    char vue();
    bool mouvementValide( Echiquier &e, int x, int y );
};

class Cavalier : public Piece
{
   public:
    Cavalier( bool white, bool gauche );
    ~Cavalier();
    char vue();
    bool mouvementValide( Echiquier &e, int x, int y );
};

class Reine : public Fou, public Tour
{
   public:
    Reine( bool white );
    ~Reine();
    char vue();
    bool mouvementValide( Echiquier &e, int x, int y );
};

class Pion : public Piece
{
   public:
    Pion( bool white, int x );
    ~Pion();
    char vue();
    bool mouvementValide( Echiquier &e, int x, int y );
};

#endif  // !defined Piece_h
