#if !defined Piece_h
#define Piece_h

class Echiquier;  

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
    void         move( int x, int y );
    int          x();
    int          y();
    bool         isWhite();
    bool         firstMove();
    virtual bool mouvementValide( Echiquier &e, int x, int y ) = 0;
    bool Echec(Echiquier &e, int x, int y);
    bool EchecMat(Echiquier &e, int x, int y );
};


class Tour : virtual public Piece
{
   public:
    Tour( bool white, bool gauche );
    ~Tour();
    bool mouvementValide( Echiquier &e, int x, int y );
    bool MouvementRealise();
};

class Roi : public Piece
{
   public:
    Roi( bool white );
    ~Roi();
    bool mouvementValide( Echiquier &e, int x, int y );
    bool roquePossible( Echiquier &e, Tour *p);
};

class Fou : virtual public Piece
{
   public:
    Fou( bool white, bool gauche );
    ~Fou();
    bool mouvementValide( Echiquier &e, int x, int y );
};

class Cavalier : public Piece
{
   public:
    Cavalier( bool white, bool gauche );
    ~Cavalier();
    bool mouvementValide( Echiquier &e, int x, int y );
};

class Reine : public Fou, public Tour
{
   public:
    Reine( bool white );
    ~Reine();
    bool mouvementValide( Echiquier &e, int x, int y );
};

class Pion : public Piece
{
   public:
    Pion( bool white, int x );
    ~Pion();
    bool mouvementValide( Echiquier &e, int x, int y );
};

#endif  
