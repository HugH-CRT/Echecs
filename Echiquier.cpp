/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Source Code de Echiquier
 * @file Echiquier.cpp
 * @date 26/10/2021
 * @version 0.5
 */

#include <iostream>
#include <assert.h>
#include "Echiquier.h"

using namespace std;

/**
 * @brief Initialise l'echiquier avec 64 pointeurs null
 */
Echiquier::Echiquier()
{
    for ( int i = 0; i < 64; i++ )
        m_cases[i] = nullptr;
}

/**
 * @param x -> coordonnée de la colonne
 * @param y -> coordonnée de la ligne
 * @return Renvoie le pointeur aux coordonnées en paramètre
 */
Piece *
Echiquier::getPiece( int x, int y )
{
    if(  x >= 1 && x <= 8 && y >= 1 && y <= 8 )
         return m_cases[( x - 1 ) + ( y - 1 ) * 8];
    else return nullptr;
}

/**
 * @brief Place la piece en paramètre sur l'echiquier à ses coordonnées
 * @param Piece * -> Piece que l'on souhaite placer
 * @return bool -> Determine si le placement s'est bien effectué
 */
bool
Echiquier::placer( Piece *p )
{
    if ( nullptr == p )
        return false;
    int x = p->x();
    int y = ( *p ).y();
    assert( x >= 1 && x <= 8 && y >= 1 && y <= 8 );
    assert( x >= 1 && x <= 8 && y >= 1 && y <= 8 );
    if ( nullptr != getPiece( x, y ) )
        return false;  // case non vide
    m_cases[( x - 1 ) + ( y - 1 ) * 8] = p;
    return true;
}

/**
 * @brief Vide la case de départ et d'arriver puis place la Piece dans la case d'arrivée
 * @param Piece *p -> Piece que l'on deplace
 * @param x -> coordonnée de la colonne ciblée
 * @param y -> coordonnée de la ligne ciblée
 */
void
Echiquier::deplacer( Piece *p, int x, int y )
{
    enleverPiece( p->x() , p->y() );
    enleverPiece( x , y );
    p->move(x,y);
    placer(p);
}

/**
 * @brief Retire la piece au coordonnées en paramètre
 * @param x -> coordonnée de la colonne
 * @param y -> coordonnée de la ligne
 */
void
Echiquier::enleverPiece( int x, int y )
{
    assert( x >= 1 && x <= 8 && y >= 1 && y <= 8 );
    m_cases[( x - 1 ) + ( y - 1 ) * 8] = nullptr;
}

/**
 * @brief Echiquier::VerifMoveRoiRoque
 * @param Roi *r -> Roi qui effectue le roque
 * @param x ->
 * @param y ->
 * @return bool -> Determine si le roque est possible
 */
bool
Echiquier::VerifMoveRoiRoque(Roi *r,int x ,int y)
{
    if ( r->x() > x )
    {
        for ( int i = r->x() - 1  ; i >= x ; i-- )
            for ( int j = 0; j < 64 ; j++ )
                if ( m_cases[j]->isWhite()!= r->isWhite() && m_cases[j] != nullptr )
                {
//                    if ( m_cases[j]->mouvementValide( *this , i , y ) )
//                    {
//                        return false;
//                    }
                }
    }
    else
        for ( int i = r->x() + 1  ; i <= x ; i++ )
            for ( int j = 0; j < 64 ; j++ )
                if ( m_cases[j]->isWhite()!= r->isWhite() && m_cases[j] != nullptr )
                {
//                    if ( m_cases[j]->mouvementValide( *this , i , y ) )
//                    {
//                        return false;
//                    }
                }
    return true;
}

/**
 * @brief Effectue le roque du roi et de la tour en paramètre
 * @param Roi *r -> Roi qui effectue le roque
 * @param Tour *t -> Tour qui effectue le roque
 */
void
Echiquier::deplacementRoque( Roi *r, Tour *t)
{
    enleverPiece( r->x() , r->y() );
    enleverPiece( t->x() , t->y() );

    if ( r->isWhite() )
    {
        if ( r->x() > t->x() )
        {
            r->move( 3 , 8 );
            t->move( 4 , 8 );
        }
        else
        {
            r->move( 7 , 8 );
            t->move( 6 , 8 );
        }
    }
    else
    {
        if ( r->x() > t->x() )
        {
            r->move( 3 , 1 );
            t->move( 4 , 1 );
        }
        else
        {
            r->move( 7 , 1 );
            t->move( 6 , 1 );
        }
    }

    placer(r);
    placer(t);
}
