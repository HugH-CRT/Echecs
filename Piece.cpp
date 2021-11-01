/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Source Code de Piece
 * @file Piece.cpp
 * @date 26/10/2021
 * @version 0.5
 */
#include <iostream>
#include "Piece.h"
#include "Echiquier.h"
using namespace std;

/**
 * @brief Piece::Piece
 * @param x
 * @param y
 * @param white
 * @param path
 */
Piece::Piece( int x, int y, bool white, string path)
{
    m_x         = x;
    m_y         = y;
    m_white     = white;
    p_firstMove = true;
    p_path      = path;
    p_isEchec   = false;
}

/**
 * @brief Piece::~Piece
 */
Piece::~Piece(){}

/**
 * @brief Piece::move
 * @param x
 * @param y
 */
void
Piece::move( int x, int y )
{
    m_x = x;
    m_y = y;
    p_firstMove = false;
}

/**
 * @brief Piece::isEchec
 * @return
 */
bool
Piece::isEchec() { return p_isEchec; }

/**
 * @brief Piece::setIsEchec
 */
void
Piece::setIsEchec() { p_isEchec = !p_isEchec; }

/**
 * @brief Piece::x
 * @return
 */
int
Piece::x() { return m_x; }

/**
 * @brief Piece::y
 * @return
 */
int
Piece::y() { return m_y; }

/**
 * @brief Piece::firstMove
 * @return
 */
bool
Piece::firstMove() { return p_firstMove; }

/**
 * @brief Piece::isWhite
 * @return
 */
bool
Piece::isWhite() { return m_white; }

/**
 * @brief Piece::path
 * @return
 */
string
Piece::path() { return p_path; }

/**
 *  @brief Méthode appelée apres la méthode echec() , vérifie si le roi à un déplacement valide
 *  @param Echiquier &e
 *  @param int x -> Position x du roi
 *  @param int y -> Position y du roi
 *  @return bool -> true si le roi possède un déplacement valable et que la piece qui l'as mis en echec ne le laisse pas en echec suite à ce déplacement , ou false dans le cas contraire
*/
list<string>
Piece::MouvementPossibleRoi(Echiquier &e, int x, int y)
{
    list<string> values;
    Piece *monRoi = e.getPiece(x,y);

    for ( int i = -1 ; i < 2 ; i++ )
        for ( int j = - 1 ; j < 2 ; j++ )
            if ( ( monRoi->x() + j > 0 && monRoi->x() + j < 9 ) && ( monRoi->y() + i > 0 && monRoi->y() + i <  9)  )
            {
                Piece *maPiece = e.getPiece( monRoi->x() + j , monRoi->y() + i );

                if ( maPiece == nullptr || maPiece->isWhite() != monRoi->isWhite())
                    values.push_back( std::to_string( monRoi->x() + j - 1) + "-" + std::to_string( monRoi->y() + i - 1 ) + "-false" );
            }
   return values;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Roi::Roi
 * @param white
 * @param path
 */
Roi::Roi( bool white, string path ) : Piece( 5, white ? 1 : 8, white, path){}

/**
 * @brief Roi::~Roi
 */
Roi::~Roi(){}


/**
 *  @brief Vérifie si un "roque" est possible entre le roi et la tour en paramètre.
 *  @param Echiquier &e
 *  @param *Tour x -> Pointeur vers la tour
 *  @return bool -> true si le déplacement est possible false dans le cas contraire
*/
bool
Roi::roquePossible( Echiquier &e, Tour *p )
{
    if ( !p_firstMove && !firstMove() )
    {
        if ( this->m_white )
        {
            if ( p->x() > m_x )
            {
                for ( int i = m_x + 1; i < p->x(); i++ )
                {
                    Piece *maPiece = e.getPiece( i , 8 );
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.VerifMoveRoiRoque( this , 7 , 8);
            }
            else if ( p->x() > m_x && p->x() == 1 && p->y() == 8 )
            {
                for ( int i = m_x - 1; i > p->x() ; i-- )
                {
                    Piece *maPiece = e.getPiece( i , 8 );
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.VerifMoveRoiRoque( this , 3 , 8 );
            }
        }
        else
        {
            if ( p->x() < m_x  )
            {
                for ( int i = m_x - 1; i > p->x() ; i-- )
                {
                    Piece *maPiece = e.getPiece( i , 1 );
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.VerifMoveRoiRoque( this , 1 , 2 );
            }
            else if ( p->x() > m_x )
            {

                for ( int i = m_x + 1; i < p->x() ; i++ )
                {
                    Piece *maPiece = e.getPiece( i , 1 );
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.VerifMoveRoiRoque( this , 1 , 7 );
            }
        }
    }
    return false;
}

/**
 * @brief Roi::AfficheMouvementValide
 * @param e
 * @param whitePlay
 * @return
 */
list<string>
Roi::AfficheMouvementValide(Echiquier &e, bool whitePlay)
{
    list<string> values;

    if ( m_white == whitePlay )
        for ( int i = m_x - 1; i <= m_x + 1 ; i++ )
            for ( int j = m_y - 1 ; j <= m_y + 1 ; j++ )
            {
                Piece *maPiece = e.getPiece( i , j );
                if ( maPiece == nullptr )
                    values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( j - 1 ) + "-false" );
                else if ( m_white != maPiece->isWhite() )
                   values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( j - 1 ) + "-true" );
            }
    return values;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Reine::Reine
 * @param white
 * @param path
 */
Reine::Reine( bool white, string path ) : Piece( 4, white ? 1 : 8, white , path ), Fou( white, true ,path ), Tour( white, true ,path ){}

/**
 * @brief Reine::~Reine
 */
Reine::~Reine(){}

/**
 * @brief Reine::AfficheMouvementValide
 * @param e
 * @param whitePlay
 * @return
 */
list<string>
Reine::AfficheMouvementValide(Echiquier &e, bool whitePlay)
{
    list<string> casesValideFou  = Fou::AfficheMouvementValide( e, whitePlay);
    list<string> casesValideTour = Tour::AfficheMouvementValide( e,whitePlay);
    casesValideFou.insert( casesValideFou.end(), casesValideTour.begin(), casesValideTour.end() );

    return casesValideFou;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Tour::Tour
 * @param white
 * @param gauche
 * @param path
 */
Tour::Tour( bool white, bool gauche, string path ) : Piece( gauche ? 1 : 8, white ? 1 : 8, white, path ){}

/**
 * @brief Tour::~Tour
 */
Tour::~Tour(){}

/**
 * @brief Tour::AfficheMouvementValide
 * @param e
 * @param whitePlay
 * @return
 */
list<string>
Tour::AfficheMouvementValide(Echiquier &e, bool whitePlay)
{
    list<string> casesValideTour;

    if ( m_white == whitePlay)
    {
        for ( int i = m_x + 1; i <= 8 ; i++ )
        {
            Piece *maPiece = e.getPiece( i , m_y );

            if ( maPiece == nullptr )
                casesValideTour.push_back( std::to_string( i - 1 ) + "-" + std::to_string( m_y - 1 )+ "-false" );
            else if ( m_white != maPiece->isWhite() )
            {
                casesValideTour.push_back( std::to_string( i - 1 ) + "-" + std::to_string( m_y - 1 )+ "-true" );
                break;
            }
            else break;
        }

        for ( int i = m_x - 1; i >= 0 ; i-- )
        {
            Piece *maPiece = e.getPiece( i , m_y );

            if ( maPiece == nullptr )
                casesValideTour.push_back( std::to_string( i - 1 ) + "-" + std::to_string( m_y - 1 )+ "-false" );
            else if ( m_white != maPiece->isWhite() )
            {
                casesValideTour.push_back( std::to_string( i - 1 ) + "-" + std::to_string( m_y - 1 )+ "-true" );
                break;
            }
            else break;
        }

        for ( int i = m_y + 1; i <= 8 ; i++ )
        {
            Piece *maPiece = e.getPiece( m_x , i );

            if ( maPiece == nullptr )
                casesValideTour.push_back( std::to_string( m_x - 1 ) + "-" + std::to_string( i - 1 ) + "-false" );
            else if ( m_white != maPiece->isWhite() )
            {
                casesValideTour.push_back( std::to_string( m_x - 1 ) + "-" + std::to_string( i - 1 ) + "-true" );
                break;
            }
            else break;
        }

        for ( int i = m_y - 1; i >= 0 ; i-- )
        {
            Piece *maPiece = e.getPiece( m_x , i );

            if ( maPiece == nullptr )
                casesValideTour.push_back( std::to_string( m_x - 1 ) + "-" + std::to_string( i - 1 ) + "-false");
            else if ( m_white != maPiece->isWhite() )
            {
                casesValideTour.push_back( std::to_string( m_x - 1 ) + "-" + std::to_string( i - 1 ) + "-true");
                break;
            }
            else break;
        }
    }
    return casesValideTour;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Fou::Fou
 * @param white
 * @param gauche
 * @param path
 */
Fou::Fou( bool white, bool gauche, string path ) : Piece( gauche ? 3 : 6, white ? 1 : 8, white, path ){}

/**
 * @brief Fou::~Fou
 */
Fou::~Fou(){}

/**
 * @brief Fou::AfficheMouvementValide
 * @param e
 * @param whitePlay
 * @return
 */
list<string>
Fou::AfficheMouvementValide(Echiquier &e, bool whitePlay)
{
    list<string> casesValideFou;

    if ( m_white == whitePlay )
    {
        int saveLinePosition = m_y;
        for ( int i = m_x + 1 ; i <= 8 ; i ++ )
        {
            saveLinePosition++;

            Piece *maPiece = e.getPiece(i,saveLinePosition);

            if ( maPiece == nullptr )
                casesValideFou.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-false" );
            else if ( maPiece->isWhite() != m_white  )
            {
                casesValideFou.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-true" );
                break;
            }
            else break;
        }

        saveLinePosition = m_y;
        for ( int i = m_x + 1 ; i <= 8 ; i ++ )
        {
            saveLinePosition--;

            Piece *maPiece = e.getPiece(i,saveLinePosition);

            if ( maPiece == nullptr )
                casesValideFou.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-false");
            else if ( maPiece->isWhite() != m_white ){
                casesValideFou.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-true" );
                break;
            }
            else break;
        }

        saveLinePosition = m_y;
        for ( int i = m_x - 1 ; i >= 0 ;i -- )
        {
            saveLinePosition++;

            Piece *maPiece = e.getPiece(i,saveLinePosition);

            if ( maPiece == nullptr )
                casesValideFou.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-false");
            else if ( maPiece->isWhite() != m_white )
            {
                casesValideFou.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-true" );
                break;
            }
            else break;
        }

        saveLinePosition = m_y;
        for ( int i = m_x - 1 ; i >= 0 ;i -- )
        {
            saveLinePosition--;

            Piece *maPiece = e.getPiece(i,saveLinePosition);

            if ( maPiece == nullptr )
                casesValideFou.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-false");
            else if ( maPiece->isWhite() != m_white )
            {
                casesValideFou.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-true");
                break;
            }
            else break;
        }
    }
    return casesValideFou;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Cavalier::Cavalier
 * @param white
 * @param gauche
 * @param path
 */
Cavalier::Cavalier( bool white, bool gauche, string path ) : Piece( gauche ? 2 : 7, white ? 1 : 8, white, path ){}

/**
 * @brief Cavalier::~Cavalier
 */
Cavalier::~Cavalier(){}

/**
 * @brief Cavalier::AfficheMouvementValide
 * @param e
 * @param whitePlay
 * @return
 */
list<string>
Cavalier::AfficheMouvementValide(Echiquier &e, bool whitePlay )
{
    list<string> casesValideCavalier;
    string Bool;

    if ( m_white == whitePlay )
    {
        Bool = e.getPiece( m_x + 2 , m_y - 1  ) == nullptr ? "false" : e.getPiece( m_x + 2 , m_y - 1 )->isWhite() != m_white ?  "true" : "";
        casesValideCavalier.push_back( std::to_string( m_x + 1 ) + "-" + std::to_string( m_y - 2 ) + "-" + Bool );

        Bool = e.getPiece( m_x + 2 , m_y + 1  ) == nullptr ? "false" : e.getPiece( m_x + 2 , m_y + 1 )->isWhite() != m_white ? "true" : "";
        casesValideCavalier.push_back( std::to_string( m_x + 1 ) + "-" + std::to_string( m_y ) + "-" +  Bool );

        Bool = e.getPiece( m_x - 2 , m_y - 1  ) == nullptr ? "false" : e.getPiece( m_x - 2 , m_y - 1 )->isWhite() != m_white ? "true" : "";
        casesValideCavalier.push_back( std::to_string( m_x - 3 ) + "-" + std::to_string( m_y - 2 ) +  "-" +Bool );

        Bool = e.getPiece( m_x - 2 , m_y + 1  ) == nullptr ? "false" : e.getPiece( m_x - 2 , m_y + 1 )->isWhite() != m_white ? "true" : "";
        casesValideCavalier.push_back( std::to_string( m_x - 3 ) + "-" + std::to_string( m_y ) + "-" +Bool);

        Bool = e.getPiece( m_x + 1 , m_y + 2  ) == nullptr ? "false" : e.getPiece( m_x + 1 , m_y + 2 )->isWhite() != m_white ? "true" : "";
        casesValideCavalier.push_back( std::to_string( m_x ) + "-" + std::to_string( m_y + 1 ) + "-" + Bool );

        Bool = e.getPiece( m_x - 1 , m_y + 2  ) == nullptr ? "false" : e.getPiece( m_x - 1 , m_y + 2 )->isWhite() != m_white ? "true" : "" ;
        casesValideCavalier.push_back( std::to_string( m_x - 2 ) + "-" + std::to_string( m_y + 1 ) + "-" + Bool );

        Bool = e.getPiece( m_x + 1 , m_y - 2  ) == nullptr ? "false" : e.getPiece( m_x + 1 , m_y - 2 )->isWhite() != m_white ? "true" : "";
        casesValideCavalier.push_back( std::to_string( m_x ) + "-" + std::to_string( m_y - 3 ) + "-" + Bool );

        Bool = e.getPiece( m_x - 1 , m_y - 2  ) == nullptr ? "false" : e.getPiece( m_x - 1 , m_y - 2 )->isWhite() != m_white ?  "true" : "";
        casesValideCavalier.push_back( std::to_string( m_x - 2 ) + "-" + std::to_string( m_y - 3 ) + "-" + Bool );
    }
    return casesValideCavalier;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Pion::Pion
 * @param white
 * @param x
 * @param path
 */
Pion::Pion( bool white, int x, string path ) : Piece( x, white ? 2 : 7, white, path ){}

/**
 * @brief Pion::~Pion
 */
Pion::~Pion(){}

/**
 * @brief Pion::AfficheMouvementValide
 * @param e
 * @param whitePlay
 * @return
 */
list<string>
Pion::AfficheMouvementValide(Echiquier &e, bool whitePlay)
{
    list<string> casesValidePion;
    int destination = (firstMove() ? 2 : 1 );

    if ( m_white && whitePlay)
    {
        for ( int i = m_y + 1  ; i <= m_y + destination ; i++ )
            if ( e.getPiece( m_x , i  ) == nullptr )
                casesValidePion.push_back( std::to_string( m_x - 1 ) + "-" + std::to_string( i - 1 )  + "-false" );

        if ( e.getPiece( m_x + 1 , m_y + 1 ) != nullptr && e.getPiece( m_x + 1 , m_y + 1 )->isWhite() != isWhite() )
            casesValidePion.push_back( std::to_string( m_x ) + "-" + std::to_string( m_y ) + "-true");

        if ( e.getPiece( m_x - 1 , m_y + 1 ) != nullptr && e.getPiece( m_x - 1 , m_y + 1 )->isWhite() != isWhite() )
             casesValidePion.push_back( std::to_string( m_x - 2 ) + "-" + std::to_string( m_y )  + "-true");
    }
    else if ( !m_white && !whitePlay )
    {
        for ( int i = m_y - 1  ; i >= m_y - destination ; i-- )
            if ( e.getPiece( m_x , i  ) == nullptr )
              casesValidePion.push_back(  std::to_string( m_x - 1 ) + "-" + std::to_string( i - 1 ) + "-false" );

        if ( e.getPiece( m_x + 1 , m_y - 1 ) != nullptr && e.getPiece( m_x + 1 , m_y - 1 )->isWhite() != isWhite())
            casesValidePion.push_back( std::to_string( m_x ) + "-" + std::to_string( m_y - 2 ) + "-true");

        if ( e.getPiece( m_x - 1 , m_y - 1 ) != nullptr && e.getPiece( m_x - 1 , m_y - 1 )->isWhite() != isWhite() )
            casesValidePion.push_back( std::to_string( m_x - 2 ) + "-" + std::to_string( m_y - 2 ) + "-true" );
    }
    return casesValidePion;
}
