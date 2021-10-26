#include <iostream>
#include "Piece.h"
#include "Echiquier.h"
using namespace std;

Piece::Piece(){}

Piece::Piece( int x, int y, bool white )
{
    m_x     = x;
    m_y     = y;
    m_white = white;
    firstMove = true;
}

Piece::Piece( const Piece &autre )
{
    m_x     = autre.m_x;
    m_y     = autre.m_y;
    m_white = autre.m_white;
    firstMove = autre.firstMove;
}

Piece::~Piece(){}

Piece &
Piece::operator=( const Piece &autre )
{
    m_x     = autre.m_x;
    m_y     = autre.m_y;
    m_white = autre.m_white;
    return *this;
}

void
Piece::init( int x, int y, bool white )
{
    m_x     = x;
    m_y     = y;
    m_white = white;
}

void
Piece::move( int x, int y )
{
    m_x = x;
    m_y = y;
}

int
Piece::x()
{
    return m_x;
}

int
Piece::y()
{
    return m_y;
}

bool
Piece::isWhite()
{
    return m_white;
}

bool
Piece::isBlack()
{
    return !m_white;
}

void
Piece::affiche()
{
    cout << "Piece: x=" << m_x << " y=" << m_y << " " << ( m_white ? "blanche" : "noire" ) << endl;
}

char
Piece::vue()
{
    return this->isWhite() ? 'B' : 'N';
}

Roi::Roi( bool white ) : Piece( 5, white ? 1 : 8, white ){}

Roi::~Roi(){}

bool
Roi::mouvementValide( Echiquier &e, int x, int y )
{
    return true;
}

char
Roi::vue()
{
    return m_white ? 'R' : 'r';
}

void
Roi::roque(){}

Reine::Reine( bool white )
    : Piece( 4, white ? 1 : 8, white ), Fou( white, true ), Tour( white, true ){}

Reine::~Reine(){}

bool
Reine::mouvementValide( Echiquier &e, int x, int y )
{
    return Fou::mouvementValide( e, x, y ) || Tour::mouvementValide( e, x, y );
}

char
Reine::vue()
{
    return Fou::m_white ? 'Q' : 'q';
}

Tour::Tour( bool white, bool gauche ) : Piece( gauche ? 1 : 8, white ? 1 : 8, white ){}

Tour::~Tour(){}

bool
Tour::mouvementValide( Echiquier &e, int x, int y )
{
    //Si on bouge en horizontale ou en vertical
    if( m_x == x && m_y != y || m_x != x && m_y == y  )
    {
        //Si on bouge en horizontale
        if ( m_x != x && m_y == y )
        {
            //Si on va à droite
            if ( x > m_x)
            {
                for ( int i = m_x + 1; i < x - 1  ; i++)
                {
                    //On récupère le pointeur de la position suivante
                    Piece *maPiece = e.getPiece(i,y);

                    if ( maPiece != nullptr )
                    {
                        return false;
                    }
                }
            }
            else
            {
                for ( int i = m_x - 1; i >= x + 1  ; i--)
                {
                    //On récupère le pointeur de la position suivante
                    Piece *maPiece = e.getPiece(i,y);

                    if ( maPiece != nullptr )
                    {
                        return false;
                    }
                }
            }
        }
        else if ( this->m_x == x && this->m_y != y )
        {
            //Si on va à en bas
            if ( y > m_y)
            {
                for ( int i = m_y + 1; i < y - 1  ; i++)
                {
                    //On récupère le pointeur de la position suivante
                    Piece *maPiece = e.getPiece(i,y);

                    if ( maPiece != nullptr )
                    {
                        return false;
                    }
                }
            }
            else
            {
                for ( int i = m_y - 1; i >= y + 1  ; i--)
                {
                    //On récupère le pointeur de la position suivante
                    Piece *maPiece = e.getPiece(x,i);

                    if ( maPiece != nullptr )
                    {
                        return false;
                    }
                }
            }
        }

        //On récupère le pointeur vers lequel on souhaite se déplacer
        Piece *maPiece = e.getPiece(x,y);

        //Si y'a pas de pièce
        if ( maPiece == nullptr ) { return true; }
        else if ( m_white != maPiece->isWhite() ) { return true; } 
    }
    return false;
}

char
Tour::vue()
{
    return m_white ? 'T' : 't';
}

Fou::Fou( bool white, bool gauche ) : Piece( gauche ? 3 : 6, white ? 1 : 8, white ){}

Fou::~Fou(){}

bool
Fou::mouvementValide( Echiquier &e, int x, int y )
{
    //Vérifie si on se déplace en diagonale
    if ( m_y != y && m_x != x)
    {
        int temp = m_y; 

        //Diagonale Haut Gauche vers bas droite
        if ( x > m_x && y > m_y )
        {
            for ( int i = m_x + 1 ; i < y ; i ++ )
            {
                temp++;

                Piece *maPiece = e.getPiece(i,temp);

                if ( maPiece != nullptr ) { return false; }
            }
        }
        //Diagonale bas gauche vers en haut à droite
        else if ( x > m_x && y < m_y )
        {
            for ( int i = m_x + 1 ; i < x ; i ++ )
            {
                temp--;

                Piece *maPiece = e.getPiece(i,temp);

                if ( maPiece != nullptr ) { return false; }
            }
        }
        //Diagonale bas droite vers haut gauche
        else if ( x < m_x && y < m_y ) 
        {
            for ( int i = m_x - 1 ; i > y ; i ++ )
            {
                temp--;

                Piece *maPiece = e.getPiece(i,temp);

                if ( maPiece != nullptr ) { return false; }
            }
        }
        //Diagonale haut droite vers bas gauche
        else
        {
            for ( int i = m_x - 1 ; i < x ; i ++ )
            {
                temp++;

                Piece *maPiece = e.getPiece(i,temp);

                if ( maPiece != nullptr ) { return false; }
            }
        }

        //On récupère le pointeur vers lequel on souhaite se déplacer
        Piece *maPiece = e.getPiece(x,y);

        //Si y'a pas de pièce
        if ( maPiece == nullptr ) { return true; }
        else if ( m_white != maPiece->isWhite() ) { return true; } 
    }
    return false;
}

char
Fou::vue()
{
    return m_white ? 'F' : 'f';
}

Cavalier::Cavalier( bool white, bool gauche ) : Piece( gauche ? 2 : 7, white ? 1 : 8, white ){}

Cavalier::~Cavalier(){}

bool
Cavalier::mouvementValide( Echiquier &e, int x, int y )
{
    if ( ( ( x == m_x + 2 ) && ( y == m_y + 1 || y == m_y - 1 ) )  ||    ( ( x == m_x - 2 )  && ( y == m_y + 1 || y == m_y - 1 ) )   ||   ( ( y == m_y + 2 )  && ( x == m_x + 1 || x == m_x - 1 )  ||  ( ( y == m_y - 2 )  && ( x == m_x + 1 || x == m_x - 1 ) )  ) )
    {
        Piece *maPiece = e.getPiece(x,y);

        //Si y'a pas de pièce
        if ( maPiece == nullptr ) { return true; }
        else if ( m_white != maPiece->isWhite() ) { return true; } 
    }                                                           

    return false;
}

char
Cavalier::vue()
{
    return m_white ? 'C' : 'c';
}

Pion::Pion( bool white, int x ) : Piece( x, white ? 2 : 7, white ){}

Pion::~Pion(){}

bool
Pion::mouvementValide( Echiquier &e, int x, int y )
{
    if ( m_white )
    {
        //Si on est sur la même ligne // Ou déplacement diag -> to Eat
        if( this->m_x == x || this->m_x + 1 == x && this->m_y + 1 == y || this->m_x - 1 == x && this->m_y + 1 == y )
        {
            //On récupère le pointeur vers lequel on souhaite se déplacer
            Piece *maPiece = e.getPiece(x,y);

            //Check la validité du déplacement déplacement
            if ( ( firstMove && y == this->m_y + 2 || y == this->m_y + 1 )  || ( !firstMove &&  y == this->m_y + 1 ) )
            {
                //Si y'a pas de pièce
                if (maPiece == nullptr )
                {
                    firstMove = false;
                    return true;
                }
                else 
                { 
                    //Si on va en diag 
                    if( this->m_x + 1 == x && this->m_y + 1 == y || this->m_x - 1 == x && this->m_y + 1 == y )
                    {
                        return true;
                    }
                }
            }
        }
    }
    else
    {
        //Si on est sur la même ligne // Ou déplacement diag -> to Eat
        if( this->m_x == x || this->m_x - 1 == x && this->m_y + 1 == y | this->m_x - 1 == x && this->m_y - 1 == y )
        {
            //On récupère le pointeur vers lequel on souhaite se déplacer
            Piece *maPiece = e.getPiece(x,y);

            //Check la validité du déplacement déplacement
            if ( ( firstMove && y == this->m_y - 2 || y == this->m_y - 1 )  || ( !firstMove &&  y == this->m_y - 1 ) )
            {
                //Si y'a pas de pièce
                if (maPiece == nullptr )
                {
                    firstMove = false;
                    return true;
                }
                else 
                { 
                    //Si on va en diag 
                    if( this->m_x - 1 == x && this->m_y + 1 == y | this->m_x - 1 == x && this->m_y - 1 == y )
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

char
Pion::vue()
{
    return m_white ? 'P' : 'p';
}
