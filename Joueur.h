/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Header de Joueur
 * @file Joueur.h
 * @date 26/10/2021
 * @version 0.5
 */

#if !defined Joueur_h
#define Joueur_h

#include "Piece.h"
#include "Echiquier.h"

class Joueur
{
   protected:
    Piece *m_pieces[16];
    bool iswhite;

   public:
    Joueur();
    virtual ~Joueur();
    bool isWhite();
    bool placerPieces( Echiquier &e );
};

class JoueurBlanc : public Joueur
{
   public:
    JoueurBlanc();
};

class JoueurNoir : public Joueur
{
   public:
    JoueurNoir();
};

#endif
