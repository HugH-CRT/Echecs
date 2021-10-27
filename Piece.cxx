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

Piece::~Piece(){}

void
Piece::move( int x, int y )
{
    m_x = x;
    m_y = y;
    firstMove = true;
}

int
Piece::x() { return m_x; }

int
Piece::y() { return m_y; }

bool
Piece::isWhite() { return m_white; }

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
    Piece *maPiece = e.getPiece(x,y);

    for ( int i = -1 ; i < 2 ; i++ )
        for ( int j = - 1 ; j < 2 ; j++ )
            if ( maPiece->mouvementValide( e , i , j ) )
                if ( !this->mouvementValide( e , i , j ) ) { return false; }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Roi::Roi( bool white ) : Piece( 5, white ? 1 : 8, white ){}

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
    //Si le roi n'a pas bougé
    if (!firstMove)
    {
        if ( this->m_white )
        {
            //La tour se situe à droite 
            if ( p->x() > m_x )
            {
                //Vérifier que la tour n'as pas bougée
                // Piece *maTour = e.getPiece(8,8);
                // if (!maTour->MouvementRealise()){}
                      
                for ( int i = m_x + 1; i < p->x() ; i++ )
                {
                    Piece *maPiece = e.getPiece(i,8);
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.VerifMoveRoiRoque( this , 7 , 8);

            }
            else if ( p->x() > m_x && p->x() == 1 && p->y() == 8 )
            {

                //Vérifier que la tour n'as pas bougée
                // Piece *maTour = e.getPiece(1,8);
                // if (!maTour->MouvementRealise()){}

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
                //Vérifier que la tour n'as pas bougée
                // Piece *maTour = e.getPiece(1,1);
                // if (!maTour->MouvementRealise()){}

                for ( int i = m_x - 1; i > p->x() ; i-- )
                {
                    Piece *maPiece = e.getPiece(i,1);
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.VerifMoveRoiRoque( this , 1 , 2);
            }
            else if ( p->x() > m_x )
            {
                //Vérifier que la tour n'as pas bougée
                // Piece *maTour = e.getPiece(1,8);
                // if (!maTour->MouvementRealise()){}

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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Reine::Reine( bool white ) : Piece( 4, white ? 1 : 8, white ), Fou( white, true ), Tour( white, true ){}

Reine::~Reine(){}

/** @brief Verifie si les coordonnées renseigner sont un déplacement valide pour la reine
    @param Echiquier &e 
    @param int x -> Position x de la case souhaitée
    @param int y -> Position y de la case souhaitée
    @return bool -> true si le déplacement est possible false dans le cas contraire
*/
bool
Reine::mouvementValide( Echiquier &e, int x, int y ) { return Fou::mouvementValide( e, x, y ) || Tour::mouvementValide( e, x, y ); }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Tour::Tour( bool white, bool gauche ) : Piece( gauche ? 1 : 8, white ? 1 : 8, white ){}

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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Fou::Fou( bool white, bool gauche ) : Piece( gauche ? 3 : 6, white ? 1 : 8, white ){}

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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Cavalier::Cavalier( bool white, bool gauche ) : Piece( gauche ? 2 : 7, white ? 1 : 8, white ){}

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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Pion::Pion( bool white, int x ) : Piece( x, white ? 2 : 7, white ){}

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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


