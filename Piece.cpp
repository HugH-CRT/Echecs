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

Piece::Piece(){}

Piece::Piece( int x, int y, bool white, string path)
{
    m_x     = x;
    m_y     = y;
    m_white = white;
    p_firstMove = true;
    p_path = path;
    p_isEchec = false;
}

Piece::~Piece(){}

void
Piece::move( int x, int y )
{
    m_x = x;
    m_y = y;
    p_firstMove = false;
}

bool
Piece::isEchec() { return p_isEchec; }

void
Piece::setIsEchec()
{
    p_isEchec = !p_isEchec;
}

int
Piece::x() { return m_x; }

int
Piece::y() { return m_y; }

bool
Piece::firstMove() { return p_firstMove; }

bool
Piece::isWhite() { return m_white; }

string
Piece::path() { return p_path; }

/** @brief Méthode appelée après chaque coup, elle regarde si la pièce qui vient de bouger peut en faisant 1 action aller au Roi adverse.
    @param Echiquier &e
    @param int x -> Position x du roi adverse
    @param int y -> Position y du roi adverse
    @return bool -> true si il y'a echec ou false dans le cas contraire.
*/
bool
Piece::Echec(Echiquier &e, int x, int y)
{
    if ( this->mouvementValide( e , x , y ) )
    {
        return true;
    }
    return false;
}

/** @brief Méthode appelée apres la méthode echec() , vérifie si le roi à un déplacement valide
    @param Echiquier &e
    @param int x -> Position x du roi
    @param int y -> Position y du roi
    @return bool -> true si le roi possède un déplacement valable et que la piece qui l'as mis en echec ne le laisse pas en echec suite à ce déplacement , ou false dans le cas contraire
*/
bool
Piece::EchecMat(Echiquier &e, int x, int y)
{
    Piece *monRoi = e.getPiece(x,y);

    for ( int i = -1 ; i < 2 ; i++ )
        for ( int j = - 1 ; j < 2 ; j++ )
            if ( ( monRoi->x() + j > 0 && monRoi->x() + j < 9 ) && ( monRoi->y() + i > 0 && monRoi->y() + i <  9)  )
            {
                Piece *maPiece = e.getPiece( monRoi->x() + j , monRoi->y() + i );

                if ( maPiece == nullptr || maPiece->isWhite() != monRoi->isWhite())
                    if ( !this->mouvementValide( e , monRoi->x() + j , monRoi->y() + i ) )
                        return false;
            }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Roi::Roi( bool white, string path ) : Piece( 5, white ? 1 : 8, white, path){}

Roi::~Roi(){}

/** @brief Verifie si les coordonnées renseigner sont un déplacement valide pour le roi
    @param Echiquier &e
    @param int x -> Position x de la case souhaitée
    @param int y -> Position y de la case souhaitée
    @return bool -> true si le déplacement est possible false dans le cas contraire
*/
bool
Roi::mouvementValide( Echiquier &e, int x, int y )
{
    if ( ( x == m_x + 1 && ( y == m_y + 1 || y == m_y  || y == m_y - 1 ) ) ||  ( x == m_x - 1 && ( y == m_y + 1 || y == m_y  || y == m_y - 1 ) ) || x == m_x  && y == m_y + 1 || x == m_x  && y == m_y - 1 )
    {
        Piece *maPiece = e.getPiece(x,y);

        if ( maPiece == nullptr ) { return true; }
        else if ( m_white != maPiece->isWhite() ) { return true; }
    }
    return false;
}


/** @brief Vérifie si un "roque" est possible entre le roi et la tour en paramètre.
    @param Echiquier &e
    @param *Tour x -> Pointeur vers la tour
    @return bool -> true si le déplacement est possible false dans le cas contraire
*/
bool
Roi::roquePossible( Echiquier &e, Tour *p )
{
    //Si le roi et la tour n'ont pas bougés
    if ( !p_firstMove && !p->firstMove())
    {
        if ( this->m_white )
        {
            //La tour se situe à droite
            if ( p->x() > m_x )
            {
                for ( int i = m_x + 1; i < p->x() ; i++ )
                {
                    Piece *maPiece = e.getPiece(i,8);
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.VerifMoveRoiRoque( this , 7 , 8);
            }
            else if ( p->x() > m_x && p->x() == 1 && p->y() == 8 )
            {
                for ( int i = m_x - 1; i > p->x() ; i-- )
                {
                    Piece *maPiece = e.getPiece(i,8);
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.VerifMoveRoiRoque( this , 3 , 8);
            }

        }
        else
        {
            //La tour se situe à droite du roi
            if ( p->x() < m_x  )
            {
                for ( int i = m_x - 1; i > p->x() ; i-- )
                {
                    Piece *maPiece = e.getPiece(i,1);
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.VerifMoveRoiRoque( this , 1 , 2);
            }
            else if ( p->x() > m_x )
            {

                for ( int i = m_x + 1; i < p->x() ; i++ )
                {
                    Piece *maPiece = e.getPiece(i,1);
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.VerifMoveRoiRoque( this , 1 , 7);
            }
        }
    }
    return false;
}

list<string>
Roi::AfficheMouvementValide(Echiquier &e, bool whitePlay)
{
    list<string> values ;

    if ( m_white == whitePlay)
    {
        for ( int i = m_x - 1; i <= m_x + 1 ; i++ )
        {
            for ( int j = m_y - 1 ; j <= m_y + 1 ; j++ )
            {
                Piece *maPiece = e.getPiece(i,j);
                if ( maPiece == nullptr )
                {
                    values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( j - 1 ) + "-false" );
                }else if ( m_white != maPiece->isWhite() )
                {
                   values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( j - 1 ) + "-true" );
                }
            }
        }
    }

    return values;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Reine::Reine( bool white, string path ) : Piece( 4, white ? 1 : 8, white , path), Fou( white, true ,path), Tour( white, true ,path){}

Reine::~Reine(){}

/** @brief Verifie si les coordonnées renseigner sont un déplacement valide pour la reine
    @param Echiquier &e
    @param int x -> Position x de la case souhaitée
    @param int y -> Position y de la case souhaitée
    @return bool -> true si le déplacement est possible false dans le cas contraire
*/
bool
Reine::mouvementValide( Echiquier &e, int x, int y ) { return Fou::mouvementValide( e, x, y ) || Tour::mouvementValide( e, x, y ); }

list<string>
Reine::AfficheMouvementValide(Echiquier &e, bool whitePlay)
{
    list<string> values = Fou::AfficheMouvementValide( e, whitePlay);
    list<string> values2 = Tour::AfficheMouvementValide( e,whitePlay);
    values.insert(values.end(), values2.begin(), values2.end());

    return values;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Tour::Tour( bool white, bool gauche, string path ) : Piece( gauche ? 1 : 8, white ? 1 : 8, white, path){}

Tour::~Tour(){}

/** @brief Vérifie si les coordonnées renseigner sont un déplacement valide pour la tour
    @param Echiquier &e
    @param int x -> Position x de la case souhaitée
    @param int y -> Position y de la case souhaitée
    @return bool -> true si le déplacement est possible false dans le cas contraire
*/
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
                for ( int i = m_x + 1; i < x ; i++)
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
                for ( int i = m_y + 1; i < y ; i++)
                {
                    //On récupère le pointeur de la position suivante
                    Piece *maPiece = e.getPiece(x,i);

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

list<string>
Tour::AfficheMouvementValide(Echiquier &e, bool whitePlay)
{
    list<string> values;

    if ( m_white == whitePlay)
    {
        for ( int i = m_x + 1; i <= 8 ; i++)
        {
            Piece *maPiece = e.getPiece( i , m_y );

            if ( maPiece == nullptr )
            {
                values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( m_y - 1 )+ "-false" );
            }else if ( m_white != maPiece->isWhite() ){
                values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( m_y - 1 )+ "-true" );
                break;
            }else{break;}
        }

        for ( int i = m_x - 1; i >= 0 ; i--)
        {
            Piece *maPiece = e.getPiece( i , m_y );

            if ( maPiece == nullptr )
            {
                values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( m_y - 1 )+ "-false" );
            }else if ( m_white != maPiece->isWhite() ){
                values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( m_y - 1 )+ "-true" );
                break;
            }else{break;}
        }

        for ( int i = m_y + 1; i <= 8 ; i++)
        {
            Piece *maPiece = e.getPiece( m_x , i );

            if ( maPiece == nullptr )
            {
                values.push_back( std::to_string( m_x - 1 ) + "-" + std::to_string( i - 1 ) + "-false" );
            }else if ( m_white != maPiece->isWhite() ){
                values.push_back( std::to_string( m_x - 1 ) + "-" + std::to_string( i - 1 ) + "-true" );
                break;
            }else{break;}
        }

        for ( int i = m_y - 1; i >= 0 ; i--)
        {
            Piece *maPiece = e.getPiece( m_x , i );

            if ( maPiece == nullptr )
            {
                values.push_back( std::to_string( m_x - 1 ) + "-" + std::to_string( i - 1 ) + "-false");
            }else if ( m_white != maPiece->isWhite() ){
                values.push_back( std::to_string( m_x - 1 ) + "-" + std::to_string( i - 1 ) + "-true");
                break;
            }else{break;}
        }
    }

    return values;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Fou::Fou( bool white, bool gauche, string path ) : Piece( gauche ? 3 : 6, white ? 1 : 8, white, path){}

Fou::~Fou(){}

/** @brief Vérifie si les coordonnées renseigner sont un déplacement valide pour le fou
    @param Echiquier &e
    @param int x -> Position x de la case souhaitée
    @param int y -> Position y de la case souhaitée
    @return bool -> true si le déplacement est possible false dans le cas contraire
*/
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
            for ( int i = m_x + 1 ; i < x ; i ++ )
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
            for ( int i = m_x - 1 ; i > x ; i -- )
            {
                temp--;

                Piece *maPiece = e.getPiece(i,temp);

                if ( maPiece != nullptr ) { return false; }
            }
        }
        //Diagonale haut droite vers bas gauche
        else
        {
            for ( int i = m_x - 1 ; i > x ; i -- )
            {
                temp++;

                Piece *maPiece = e.getPiece(i,temp);

                if ( maPiece != nullptr ) { return false; }
            }
        }

        bool SurLaDiag = false;
        int LigneUp = m_y;
        int Lignedown = m_y;
        int colonneDown = m_x;
        int colonneUp = m_x;
        for ( int i = 0  ; i < 8 ; i++)
        {
            LigneUp++;
            Lignedown--;
            colonneDown--;
            colonneUp++;
            if ( x == colonneUp && y == LigneUp || x == colonneUp && y == Lignedown || x == colonneDown && y == LigneUp || x == colonneDown && y == Lignedown)
            {
                SurLaDiag = true;
            }
        }

        //On récupère le pointeur vers lequel on souhaite se déplacer
        Piece *maPiece = e.getPiece(x,y);

        //Si y'a pas de pièce
        if ( maPiece == nullptr && SurLaDiag ) { return true; }
        else if ( maPiece != nullptr && m_white != maPiece->isWhite() && SurLaDiag) { return true; }
    }



    return false;
}

list<string>
Fou::AfficheMouvementValide(Echiquier &e, bool whitePlay)
{
    list<string> values;

    if ( m_white == whitePlay )
    {
        int temp = m_y;
        for ( int i = m_x + 1 ; i <= 8 ; i ++ )
        {
            temp++;

            Piece *maPiece = e.getPiece(i,temp);

            if ( maPiece == nullptr )
            {
                values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( temp - 1 ) + "-false" );
            }else if ( maPiece->isWhite() != m_white  )
            {
                values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( temp - 1 ) + "-true" );
                break;
            }else {  break; }
        }

        temp = m_y;
        for ( int i = m_x + 1 ; i <= 8 ; i ++ )
        {
            temp--;

            Piece *maPiece = e.getPiece(i,temp);

            if ( maPiece == nullptr )
            {
                values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( temp - 1 ) + "-false");
            }else if ( maPiece->isWhite() != m_white ){
                values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( temp - 1 ) + "-true" );
                break;
            }else {  break; }
        }


        temp = m_y;
        for ( int i = m_x - 1 ; i >= 0 ;i -- )
        {
            temp++;

            Piece *maPiece = e.getPiece(i,temp);

            if ( maPiece == nullptr )
            {
                values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( temp - 1 ) + "-false");
            }else if ( maPiece->isWhite() != m_white ){

                values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( temp - 1 ) + "-true" );
                break;
            }
            else {  break; }
        }

        temp = m_y;
        for ( int i = m_x - 1 ; i >= 0 ;i -- )
        {
            temp--;

            Piece *maPiece = e.getPiece(i,temp);

            if ( maPiece == nullptr )
            {
                values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( temp - 1 ) + "-false");
            }else if ( maPiece->isWhite() != m_white )
            {
                values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( temp - 1 ) + "-true");
                break;
            }else {  break; }
        }
    }

    return values;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Cavalier::Cavalier( bool white, bool gauche, string path) : Piece( gauche ? 2 : 7, white ? 1 : 8, white, path ){}

Cavalier::~Cavalier(){}

/** @brief Vérifie si les coordonnées renseigner sont un déplacement valide pour le fou
    @param Echiquier &e
    @param int x -> Position x de la case souhaitée
    @param int y -> Position y de la case souhaitée
    @return bool -> true si le déplacement est possible false dans le cas contraire
*/
bool
Cavalier::mouvementValide( Echiquier &e, int x, int y )
{
    if ( ( ( x == m_x + 2 ) && ( y == m_y + 1 || y == m_y - 1 ) )  ||    ( ( x == m_x - 2 )  && ( y == m_y + 1 || y == m_y - 1 ) )   ||   ( ( y == m_y + 2 )  && ( x == m_x + 1 || x == m_x - 1 )  ||  ( ( y == m_y - 2 )  && ( x == m_x + 1 || x == m_x - 1 ) )  ) )
    {
        Piece *maPiece = e.getPiece(x,y);

        if ( maPiece == nullptr ) { return true; }
        else if ( m_white != maPiece->isWhite() ) { return true; }
    }

    return false;
}

list<string>
Cavalier::AfficheMouvementValide(Echiquier &e, bool whitePlay)
{
    list<string> values;
    string Bool;

    if ( m_white == whitePlay)
    {
        Bool = e.getPiece( m_x + 2 , m_y - 1  ) == nullptr ? "-false" : e.getPiece( m_x + 2 , m_y - 1 )->isWhite() != m_white ?  "-true" : "";
        values.push_back( std::to_string( m_x + 1 ) + "-" + std::to_string( m_y - 2 ) + Bool );


        Bool = e.getPiece( m_x + 2 , m_y + 1  ) == nullptr ? "-false" : e.getPiece( m_x + 2 , m_y + 1 )->isWhite() != m_white ? "-true" : "";
        values.push_back( std::to_string( m_x + 1 ) + "-" + std::to_string( m_y ) + Bool );


        Bool = e.getPiece( m_x - 2 , m_y - 1  ) == nullptr ? "-false" : e.getPiece( m_x - 2 , m_y - 1 )->isWhite() != m_white ? "-true" : "";
        values.push_back( std::to_string( m_x - 3 ) + "-" + std::to_string( m_y - 2 )  + Bool );


        Bool = e.getPiece( m_x - 2 , m_y + 1  ) == nullptr ? "-false" : e.getPiece( m_x - 2 , m_y + 1 )->isWhite() != m_white ? "-true" : "";
        values.push_back( std::to_string( m_x - 3 ) + "-" + std::to_string( m_y ) + Bool);


        Bool = e.getPiece( m_x + 1 , m_y + 2  ) == nullptr ? "-false" : e.getPiece( m_x + 1 , m_y + 2 )->isWhite() != m_white ? "-true" : "";
        values.push_back( std::to_string( m_x ) + "-" + std::to_string( m_y + 1 ) + Bool );


        Bool = e.getPiece( m_x - 1 , m_y + 2  ) == nullptr ? "-false" : e.getPiece( m_x - 1 , m_y + 2 )->isWhite() != m_white ? "-true" : "" ;
        values.push_back( std::to_string( m_x - 2 ) + "-" + std::to_string( m_y + 1 ) + Bool );


        Bool = e.getPiece( m_x + 1 , m_y - 2  ) == nullptr ? "-false" : e.getPiece( m_x + 1 , m_y - 2 )->isWhite() != m_white ? "-true" : "";
        values.push_back( std::to_string( m_x ) + "-" + std::to_string( m_y - 3 ) + Bool );

        Bool = e.getPiece( m_x - 1 , m_y - 2  ) == nullptr ? "-false" : e.getPiece( m_x - 1 , m_y - 2 )->isWhite() != m_white ?  "-true" : "";
        values.push_back( std::to_string( m_x - 2 ) + "-" + std::to_string( m_y - 3 ) + Bool );
    }
    return values;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Pion::Pion( bool white, int x, string path ) : Piece( x, white ? 2 : 7, white, path ){}

Pion::~Pion(){}

/** @brief Vérifie si les coordonnées renseigner sont un déplacement valide pour le pion
    @param Echiquier &e
    @param int x -> Position x de la case souhaitée
    @param int y -> Position y de la case souhaitée
    @return bool -> true si le déplacement est possible false dans le cas contraire
*/
bool
Pion::mouvementValide( Echiquier &e, int x, int y )
{
    if ( m_white )
    {
        //Si on est sur la même ligne // Ou déplacement diag -> to Eat
        if( this->m_x == x || this->m_y + 1 == y && ( this->m_x + 1 == x || this->m_x - 1 == x ) )
        {
            for ( int i = m_y + 1  ; i < y ; i++ )
            {
                if (e.getPiece(x,i) != nullptr){ return false; }
            }
            //On récupère le pointeur vers lequel on souhaite se déplacer
            Piece *maPiece = e.getPiece(x,y);

            //Check la validité du déplacement déplacement
            if ( ( p_firstMove && ( y == this->m_y + 2 || y == this->m_y + 1 ) )  || ( !p_firstMove &&  y == this->m_y + 1 ) )
            {
                //Si y'a pas de pièce
                if (maPiece == nullptr && x == m_x)
                {
                    p_firstMove = false;
                    return true;
                }
                else
                {
                    //Si on va en diag
                    if( this->m_y + 1 == y && (this->m_x + 1 == x ||  this->m_x - 1 == x )  && maPiece != nullptr && maPiece->isWhite() != m_white)
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
        if( this->m_x == x || this->m_y - 1 == y && ( this->m_x + 1 == x || this->m_x - 1 == x ) )
        {
            for ( int i = m_y - 1 ; i > y ; i-- )
            {
                if (e.getPiece(x,i) != nullptr){ return false; }
            }
            //On récupère le pointeur vers lequel on souhaite se déplacer
            Piece *maPiece = e.getPiece(x,y);

            //Check la validité du déplacement déplacement
            if ( ( p_firstMove && ( y == this->m_y - 2 || y == this->m_y - 1 ) )  || ( !p_firstMove &&  y == this->m_y - 1 ) )
            {
                //Si y'a pas de pièce
                if (maPiece == nullptr && x == m_x)
                {
                   p_firstMove = false;
                   return true;
                }
                else
                {
                    //Si on va en diag
                    if( this->m_y - 1 == y && ( this->m_x + 1 == x || this->m_x - 1 == x ) && maPiece != nullptr && maPiece->isWhite() != m_white)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

list<string>
Pion::AfficheMouvementValide(Echiquier &e, bool whitePlay)
{
    list<string> values;
    int destination = (firstMove() ? 2 : 1 );

    if ( m_white && whitePlay)
    {
        for ( int i = m_y + 1  ; i <= m_y + destination ; i++ )
        {
            if ( e.getPiece( m_x , i  ) == nullptr ) { values.push_back( std::to_string( m_x - 1 ) + "-" + std::to_string( i - 1 )  + "-false" ); }
        }

        if ( e.getPiece( m_x + 1 , m_y + 1 ) != nullptr && e.getPiece( m_x + 1 , m_y + 1 )->isWhite() != isWhite())
        {
            values.push_back( std::to_string( m_x ) + "-" + std::to_string( m_y ) + "-true");
        }
        if ( e.getPiece( m_x - 1 , m_y + 1 ) != nullptr && e.getPiece( m_x - 1 , m_y + 1 )->isWhite() != isWhite() )
        {
             values.push_back( std::to_string( m_x - 2 ) + "-" + std::to_string( m_y )  + "-true");
        }
    }
    else if ( !m_white && !whitePlay )
    {
        for ( int i = m_y - 1  ; i >= m_y - destination ; i-- )
        {
            if ( e.getPiece( m_x , i  ) == nullptr ){ values.push_back(  std::to_string( m_x - 1 ) + "-" + std::to_string( i - 1 ) + "-false" ); }
        }

        if ( e.getPiece( m_x + 1 , m_y - 1 ) != nullptr && e.getPiece( m_x + 1 , m_y - 1 )->isWhite() != isWhite())
        {
            values.push_back( std::to_string( m_x ) + "-" + std::to_string( m_y - 2 ) + "-true");
        }
        if ( e.getPiece( m_x - 1 , m_y - 1 ) != nullptr && e.getPiece( m_x - 1 , m_y - 1 )->isWhite() != isWhite() )
        {
            values.push_back( std::to_string( m_x - 2 ) + "-" + std::to_string( m_y - 2 ) + "-true" );
        }
    }

    return values;
}
