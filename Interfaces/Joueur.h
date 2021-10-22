#if !defined Joueur_h
#define Joueur_h

#include "Piece.h"
#include "Echiquier.h"
class Joueur
{
   protected:
    Piece *m_pieces[16];

   public:
    Joueur();
    virtual ~Joueur();
    void         affiche();
    virtual bool isWhite() = 0;
    bool         placerPieces( Echiquier &e );
};

class JoueurBlanc : public Joueur
{
   public:
    JoueurBlanc();
    bool isWhite();
};

class JoueurNoir : public Joueur
{
   public:
    JoueurNoir();
    bool isWhite();
};

#endif