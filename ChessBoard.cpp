/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Source Code de ChessBoard
 * @file ChessBoard.cpp
 * @date 26/10/2021
 * @version 0.5
 */

#include <iostream>
#include <assert.h>
#include "ChessBoard.h"

using namespace std;

/**
 * @brief Initialise l'ChessBoard avec 64 pointeurs null
 */
ChessBoard::ChessBoard()
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
ChessBoard::GetPiece( int x, int y )
{
    if(  x >= 1 && x <= 8 && y >= 1 && y <= 8 )
         return m_cases[( x - 1 ) + ( y - 1 ) * 8];
    else return nullptr;
}

/**
 * @brief Place la piece en paramètre sur l'ChessBoard à ses coordonnées
 * @param Piece * -> Piece que l'on souhaite placer
 * @return bool -> Determine si le placement s'est bien effectué
 */
bool
ChessBoard::PlacePiece( Piece *p )
{
    if ( nullptr == p )
        return false;
    int x = p->GetX();
    int y = ( *p ).GetY();
    assert( x >= 1 && x <= 8 && y >= 1 && y <= 8 );
    assert( x >= 1 && x <= 8 && y >= 1 && y <= 8 );
    if ( nullptr != GetPiece( x, y ) )
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
ChessBoard::MovePiece( Piece *p, int x, int y )
{
    RemovePiece( p->GetX() , p->GetY() );
    RemovePiece( x , y );
    p->Move(x,y);
    PlacePiece(p);
}

/**
 * @brief Retire la piece au coordonnées en paramètre
 * @param x -> coordonnée de la colonne
 * @param y -> coordonnée de la ligne
 */
void
ChessBoard::RemovePiece( int x, int y )
{
    assert( x >= 1 && x <= 8 && y >= 1 && y <= 8 );
    m_cases[( x - 1 ) + ( y - 1 ) * 8] = nullptr;
}

/**
 * @brief ChessBoard::CheckRoqueValidity
 * @param King *r -> King qui effectue le roque
 * @param x ->
 * @param y ->
 * @return bool -> Determine si le roque est possible
 */
bool
ChessBoard::CheckRoqueValidity(King *r,int x ,int y)
{
    if ( r->GetX() > x )
    {
        for ( int i = r->GetX() - 1  ; i >= x ; i-- )
            for ( int j = 0; j < 64 ; j++ )
                if ( m_cases[j]->GetIsWhite() != r->GetIsWhite() && m_cases[j] != nullptr )
                {
//                    if ( m_cases[j]->mouvementValide( *this , i , y ) )
//                    {
//                        return false;
//                    }
                }
    }
    else
        for ( int i = r->GetX() + 1  ; i <= x ; i++ )
            for ( int j = 0; j < 64 ; j++ )
                if ( m_cases[j]->GetIsWhite()!= r->GetIsWhite() && m_cases[j] != nullptr )
                {
//                    if ( m_cases[j]->mouvementValide( *this , i , y ) )
//                    {
//                        return false;
//                    }
                }
    return true;
}

/**
 * @brief Effectue le roque du King et de la tour en paramètre
 * @param King *r -> King qui effectue le roque
 * @param Tour *t -> Tour qui effectue le roque
 */
void
ChessBoard::DoRoque( King *r, Rook *t)
{
    RemovePiece( r->GetX() , r->GetY() );
    RemovePiece( t->GetX() , t->GetY() );

    if ( r->GetIsWhite() )
    {
        if ( r->GetX() > t->GetX() )
        {
            r->Move( 3 , 8 );
            t->Move( 4 , 8 );
        }
        else
        {
            r->Move( 7 , 8 );
            t->Move( 6 , 8 );
        }
    }
    else
    {
        if ( r->GetX() > t->GetX() )
        {
            r->Move( 3 , 1 );
            t->Move( 4 , 1 );
        }
        else
        {
            r->Move( 7 , 1 );
            t->Move( 6 , 1 );
        }
    }

    PlacePiece(r);
    PlacePiece(t);
}
