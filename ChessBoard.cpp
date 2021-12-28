/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Source Code de ChessBoard
 * @file ChessBoard.cpp
 * @date 26/10/2021
 * @version 0.8
 */

#include <iostream>
#include <assert.h>
#include "ChessBoard.h"

using namespace std;

/**
 * @brief Initializes the ChessBoard with 64 null pointers
 */
ChessBoard::ChessBoard()
{
    for ( int i = 0; i < 64; i++ )
        m_cases[i] = nullptr;
}

/**
 * @param x -> column coordinate
 * @param y -> line coordinate
 * @return Returns the pointer to the coordinates as a parameter
 */
Piece *
ChessBoard::GetPiece( int x, int y )
{
    if(  x >= 1 && x <= 8 && y >= 1 && y <= 8 )
         return m_cases[( x - 1 ) + ( y - 1 ) * 8];
    else return nullptr;
}

Piece**
ChessBoard::GetTab(){return m_cases;}
/**
 * @brief Place the part as a parameter on the ChessBoard at its coordinates
 * @param Piece * -> Piece that we want to place
 * @return bool -> Determine if the placement went well
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
 * @brief Clear the starting square and arriving then place the Piece in the finishing square
 * @param Piece *p -> Piece that we move
 * @param x -> coordinate of the targeted column
 * @param y -> coordinate of the targeted line
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
 * @brief Remove the part at the coordinates in parameter
 * @param x -> column coordinate
 * @param y -> line coordinate
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
 * @param x -> column coordinate
 * @param y -> line coordinate
 * @return bool -> Determine if castling is possiblee
 */
bool
ChessBoard::CheckRoqueValidity(Piece *k,int x ,int y)
{
    //Si le roi se déplace à gauche du plateau
    if ( k->GetX() > x )
    {
        //Parcours toutes les cases vers la gauche jusqua son arrivée
        for ( int i = k->GetX() - 1  ; i >= x ; i-- )
            //Parcours les 64 cases du plateau
            for ( int j = 0; j < 64 ; j++ )
                if ( m_cases[j] != nullptr )
                    //Si la cases est de couleur opposée && que c'est une piece
                    if ( m_cases[j]->GetIsWhite() != k->GetIsWhite() )
                        //Si la piece peut atteindre la case ou le roi souhaite passer
                        if ( m_cases[j]->Deplace( *this , i , k->GetY() ) ){ return false; }
    }
    else
        for ( int i = k->GetX() + 1  ; i <= x ; i++ )
            for ( int j = 0; j < 64 ; j++ )
                if ( m_cases[j] != nullptr )
                    if ( m_cases[j]->GetIsWhite() != k->GetIsWhite() )
                        if ( m_cases[j]->Deplace( *this , i , k->GetY() ) ){ return false; }
    return true;
}


