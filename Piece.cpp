/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Source Code de Piece
 * @file Piece.cpp
 * @date 26/10/2021
 * @version 0.5
 */
#include <iostream>
#include "Piece.h"
#include "ChessBoard.h"
using namespace std;

/**
 * @brief Constructeur d'une Piece
 * @param x -> coordonnée de la colonne
 * @param y -> coordonnée de la ligne
 * @param white -> couleur de la piece
 * @param path -> chemin de l'image de la piece
 */
Piece::Piece( int x, int y, bool white, string path)
{
    p_x         = x;
    p_y         = y;
    p_white     = white;
    p_firstMove = true;
    p_path      = path;
    p_isEchec   = false;
}

/**
 * @brief Destructeur de la Piece
 */
Piece::~Piece(){}

/**
 * @brief Met à jour les coordonnées de la piece ainsi que son attribut first move
 * @param x
 * @param y
 */
void
Piece::Move( int x, int y )
{
    p_x = x;
    p_y = y;
    p_firstMove = false;
}

/**
 * @brief Renvoie l'attribut p_isEchec
 */
bool
Piece::GetIsEchec() { return p_isEchec; }

/**
 * @brief Inverse l'attribut booléen p_isEchec
 */
void
Piece::SetIsEchec() { p_isEchec = !p_isEchec; }

/**
 * @brief Renvoie l'attribut p_x
 */
int
Piece::GetX() { return p_x; }

/**
 * @brief PRenvoie l'attribut p_y
 */
int
Piece::GetY() { return p_y; }

/**
 * @brief Renvoie l'attribut p_firstMove
 */
bool
Piece::GetFirstMove() { return p_firstMove; }

/**
 * @brief Renvoie l'attribut p_white
 */
bool
Piece::GetIsWhite() { return p_white; }

/**
 * @brief Renvoie l'attribut p_path
 */
string
Piece::GetPath() { return p_path; }

/**
 *  @brief Méthode appelée après la méthode echec() , vérifie si le King à un déplacement valide
 *  @param ChessBoard &e
 *  @param int x -> Position x du King
 *  @param int y -> Position y du King
 *  @return bool -> true si le King possède un déplacement valable et que la piece qui l'as mis en echec ne le laisse pas en echec suite à ce déplacement , ou false dans le cas contraire
*/
list<string>
Piece::CheckAvailableMovementKing(ChessBoard &e, int x, int y)
{
    list<string> values;
    Piece *monKing = e.GetPiece(x,y);

    for ( int i = -1 ; i < 2 ; i++ )
        for ( int j = - 1 ; j < 2 ; j++ )
            if ( ( monKing->GetX() + j > 0 && monKing->GetX() + j < 9 ) && ( monKing->GetY() + i > 0 && monKing->GetY() + i <  9)  )
            {
                Piece *maPiece = e.GetPiece( monKing->GetX() + j , monKing->GetY() + i );

                if ( maPiece == nullptr || maPiece->GetIsWhite() != monKing->GetIsWhite())
                    values.push_back( std::to_string( monKing->GetX() + j - 1) + "-" + std::to_string( monKing->GetY() + i - 1 ) + "-false" );
            }
   return values;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructeur du King
 * @param white -> Couleur du King
 * @param path -> Chemin d'image de l'image du King
 */
King::King( bool white, string path ) : Piece( 5, white ? 1 : 8, white, path){}

/**
 * @brief Destructeur du King
 */
King::~King(){}

/**
 *  @brief Vérifie si un "roque" est possible entre le King et la Rook en paramètre.
 *  @param ChessBoard &e
 *  @param *Rook x -> Pointeur vers la Rook
 *  @return bool -> true si le déplacement est possible false dans le cas contraire
*/
bool
King::CastlingAvailable( ChessBoard &e, Rook *p )
{
    if ( !p_firstMove && !GetFirstMove() )
    {
        if ( this->p_white )
        {
            if ( p->GetX() > p_x )
            {
                for ( int i = p_x + 1; i < p->GetX(); i++ )
                {
                    Piece *maPiece = e.GetPiece( i , 8 );
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.CheckRoqueValidity( this , 7 , 8);
            }
            else if ( p->GetX() > p_x && p->GetX() == 1 && p->GetY() == 8 )
            {
                for ( int i = p_x - 1; i > p->GetX() ; i-- )
                {
                    Piece *maPiece = e.GetPiece( i , 8 );
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.CheckRoqueValidity( this , 3 , 8 );
            }
        }
        else
        {
            if ( p->GetX() < p_x  )
            {
                for ( int i = p_x - 1; i > p->GetX() ; i-- )
                {
                    Piece *maPiece = e.GetPiece( i , 1 );
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.CheckRoqueValidity( this , 1 , 2 );
            }
            else if ( p->GetX() > p_x )
            {

                for ( int i = p_x + 1; i < p->GetX() ; i++ )
                {
                    Piece *maPiece = e.GetPiece( i , 1 );
                    if ( maPiece != nullptr ) { return false; }
                }

                return e.CheckRoqueValidity( this , 1 , 7 );
            }
        }
    }
    return false;
}

/**
 * @brief Récupère les coordonnées des cellules dont le mouvement est valide pour le King.
 * @param ChessBoard e
 * @param bool whitePlay -> Vrai si c'est le Rook du joueur blanc, Faux sinon.
 * @return list<string> values -> Liste de toutes les coordonnées des cellules valides pour les déplacements du King.
 *        Les coordonnées renseignées sont au format : 'x-y-bool' ou x correspond à la colonne de la cellule, y correspond à la ligne
 *        de la cellule et bool correspond à l'attribution de la couleur true -> bleu , false -> rose
 */
list<string>
King::DisplayAvailableMovement(ChessBoard &e, bool whitePlay)
{
    list<string> values;

    if ( p_white == whitePlay )
        for ( int i = p_x - 1; i <= p_x + 1 ; i++ )
            for ( int j = p_y - 1 ; j <= p_y + 1 ; j++ )
            {
                Piece *maPiece = e.GetPiece( i , j );
                if ( maPiece == nullptr )
                    values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( j - 1 ) + "-false" );
                else if ( p_white != maPiece->GetIsWhite() )
                   values.push_back( std::to_string( i - 1 ) + "-" + std::to_string( j - 1 ) + "-true" );
            }
    return values;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructeur de la Queen
 * @param white -> Couleur de la Queen
 * @param path -> Chemin d'image de l'image de la Queen.
 */
Queen::Queen( bool white, string path ) : Piece( 4, white ? 1 : 8, white , path ), Bishop( white, true ,path ), Rook( white, true ,path ){}

/**
 * @brief Destructeur de la Queen
 */
Queen::~Queen(){}

/**
 * @brief Récupère les coordonnées des cellules dont le mouvement est valide pour la Queen.
 * @param ChessBoard e
 * @param bool whitePlay -> Vrai si c'est le Rook du joueur blanc, Faux sinon.
 * @return list<string> values -> Liste de toutes les coordonnées des cellules valides pour les déplacements de la Queen.
 *        Les coordonnées renseignées sont au format : 'x-y-bool' ou x correspond à la colonne de la cellule, y correspond à la ligne
 *        de la cellule et bool correspond à l'attribution de la couleur true -> bleu , false -> rose
 */
list<string>
Queen::DisplayAvailableMovement(ChessBoard &e, bool whitePlay)
{
    list<string> casesValideBishop  = Bishop::DisplayAvailableMovement( e, whitePlay);
    list<string> casesValideRook = Rook::DisplayAvailableMovement( e,whitePlay);
    casesValideBishop.insert( casesValideBishop.end(), casesValideRook.begin(), casesValideRook.end() );

    return casesValideBishop;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructeur de la Rook.
 * @param white -> Couleur de la Rook.
 * @param path -> Chemin d'image de l'image de la Rook.
 */
Rook::Rook( bool white, bool gauche, string path ) : Piece( gauche ? 1 : 8, white ? 1 : 8, white, path ){}

/**
 * @brief Destructeur de la Rook.
 */
Rook::~Rook(){}

/**
 * @brief Récupère les coordonnées des cellules dont le mouvement est valide pour la Rook.
 * @param ChessBoard e
 * @param bool whitePlay -> Vrai si c'est le Rook du joueur blanc, Faux sinon.
 * @return list<string> values -> Liste de toutes les coordonnées des cellules valides pour les déplacements de la Rook.
 *        Les coordonnées renseignées sont au format : 'x-y-bool' ou x correspond à la colonne de la cellule, y correspond à la ligne
 *        de la cellule et bool correspond à l'attribution de la couleur true -> bleu , false -> rose
 */
list<string>
Rook::DisplayAvailableMovement(ChessBoard &e, bool whitePlay)
{
    list<string> casesValideRook;

    if ( p_white == whitePlay)
    {
        for ( int i = p_x + 1; i <= 8 ; i++ )
        {
            Piece *maPiece = e.GetPiece( i , p_y );

            if ( maPiece == nullptr )
                casesValideRook.push_back( std::to_string( i - 1 ) + "-" + std::to_string( p_y - 1 )+ "-false" );
            else if ( p_white != maPiece->GetIsWhite() )
            {
                casesValideRook.push_back( std::to_string( i - 1 ) + "-" + std::to_string( p_y - 1 )+ "-true" );
                break;
            }
            else break;
        }

        for ( int i = p_x - 1; i >= 0 ; i-- )
        {
            Piece *maPiece = e.GetPiece( i , p_y );

            if ( maPiece == nullptr )
                casesValideRook.push_back( std::to_string( i - 1 ) + "-" + std::to_string( p_y - 1 )+ "-false" );
            else if ( p_white != maPiece->GetIsWhite() )
            {
                casesValideRook.push_back( std::to_string( i - 1 ) + "-" + std::to_string( p_y - 1 )+ "-true" );
                break;
            }
            else break;
        }

        for ( int i = p_y + 1; i <= 8 ; i++ )
        {
            Piece *maPiece = e.GetPiece( p_x , i );

            if ( maPiece == nullptr )
                casesValideRook.push_back( std::to_string( p_x - 1 ) + "-" + std::to_string( i - 1 ) + "-false" );
            else if ( p_white != maPiece->GetIsWhite() )
            {
                casesValideRook.push_back( std::to_string( p_x - 1 ) + "-" + std::to_string( i - 1 ) + "-true" );
                break;
            }
            else break;
        }

        for ( int i = p_y - 1; i >= 0 ; i-- )
        {
            Piece *maPiece = e.GetPiece( p_x , i );

            if ( maPiece == nullptr )
                casesValideRook.push_back( std::to_string( p_x - 1 ) + "-" + std::to_string( i - 1 ) + "-false");
            else if ( p_white != maPiece->GetIsWhite() )
            {
                casesValideRook.push_back( std::to_string( p_x - 1 ) + "-" + std::to_string( i - 1 ) + "-true");
                break;
            }
            else break;
        }
    }
    return casesValideRook;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructeur du Bishop.
 * @param white -> Couleur du Bishop.
 * @param path -> Chemin d'image de l'image du Bishop.
 */
Bishop::Bishop( bool white, bool gauche, string path ) : Piece( gauche ? 3 : 6, white ? 1 : 8, white, path ){}

/**
 * @brief Destructeur du Bishop.
 */
Bishop::~Bishop(){}

/**
 * @brief Récupère les coordonnées des cellules dont le mouvement est valide pour le Bishop.
 * @param ChessBoard e
 * @param bool whitePlay -> Vrai si c'est le Rook du joueur blanc, Faux sinon.
 * @return list<string> values -> Liste de toutes les coordonnées des cellules valides pour les déplacements du Bishop.
 *        Les coordonnées renseignées sont au format : 'x-y-bool' ou x correspond à la colonne de la cellule, y correspond à la ligne
 *        de la cellule et bool correspond à l'attribution de la couleur true -> bleu , false -> rose
 */
list<string>
Bishop::DisplayAvailableMovement(ChessBoard &e, bool whitePlay)
{
    list<string> casesValideBishop;

    if ( p_white == whitePlay )
    {
        int saveLinePosition = p_y;
        for ( int i = p_x + 1 ; i <= 8 ; i ++ )
        {
            saveLinePosition++;

            Piece *maPiece = e.GetPiece(i,saveLinePosition);

            if ( maPiece == nullptr )
                casesValideBishop.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-false" );
            else if ( maPiece->GetIsWhite() != p_white  )
            {
                casesValideBishop.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-true" );
                break;
            }
            else break;
        }

        saveLinePosition = p_y;
        for ( int i = p_x + 1 ; i <= 8 ; i ++ )
        {
            saveLinePosition--;

            Piece *maPiece = e.GetPiece(i,saveLinePosition);

            if ( maPiece == nullptr )
                casesValideBishop.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-false");
            else if ( maPiece->GetIsWhite() != p_white ){
                casesValideBishop.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-true" );
                break;
            }
            else break;
        }

        saveLinePosition = p_y;
        for ( int i = p_x - 1 ; i >= 0 ;i -- )
        {
            saveLinePosition++;

            Piece *maPiece = e.GetPiece(i,saveLinePosition);

            if ( maPiece == nullptr )
                casesValideBishop.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-false");
            else if ( maPiece->GetIsWhite() != p_white )
            {
                casesValideBishop.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-true" );
                break;
            }
            else break;
        }

        saveLinePosition = p_y;
        for ( int i = p_x - 1 ; i >= 0 ;i -- )
        {
            saveLinePosition--;

            Piece *maPiece = e.GetPiece(i,saveLinePosition);

            if ( maPiece == nullptr )
                casesValideBishop.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-false");
            else if ( maPiece->GetIsWhite() != p_white )
            {
                casesValideBishop.push_back( std::to_string( i - 1 ) + "-" + std::to_string( saveLinePosition - 1 ) + "-true");
                break;
            }
            else break;
        }
    }
    return casesValideBishop;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructeur du Knight.
 * @param white -> Couleur du Knight.
 * @param path -> Chemin d'image de l'image du Knight.
 */
Knight::Knight( bool white, bool gauche, string path ) : Piece( gauche ? 2 : 7, white ? 1 : 8, white, path ){}

/**
 * @brief Destructeur du Knight.
 */
Knight::~Knight(){}

/**
 * @brief Récupère les coordonnées des cellules dont le mouvement est valide pour le Knight.
 * @param ChessBoard e
 * @param bool whitePlay -> Vrai si c'est le Rook du joueur blanc, Faux sinon.
 * @return list<string> values -> Liste de toutes les coordonnées des cellules valides pour les déplacements du Knight.
 *        Les coordonnées renseignées sont au format : 'x-y-bool' ou x correspond à la colonne de la cellule, y correspond à la ligne
 *        de la cellule et bool correspond à l'attribution de la couleur true -> bleu , false -> rose
 */
list<string>
Knight::DisplayAvailableMovement(ChessBoard &e, bool whitePlay )
{
    list<string> casesValideKnight;
    string Bool;

    if ( p_white == whitePlay )
    {
        Bool = e.GetPiece( p_x + 2 , p_y - 1  ) == nullptr ? "false" : e.GetPiece( p_x + 2 , p_y - 1 )->GetIsWhite() != p_white ?  "true" : "";
        casesValideKnight.push_back( std::to_string( p_x + 1 ) + "-" + std::to_string( p_y - 2 ) + "-" + Bool );

        Bool = e.GetPiece( p_x + 2 , p_y + 1  ) == nullptr ? "false" : e.GetPiece( p_x + 2 , p_y + 1 )->GetIsWhite() != p_white ? "true" : "";
        casesValideKnight.push_back( std::to_string( p_x + 1 ) + "-" + std::to_string( p_y ) + "-" +  Bool );

        Bool = e.GetPiece( p_x - 2 , p_y - 1  ) == nullptr ? "false" : e.GetPiece( p_x - 2 , p_y - 1 )->GetIsWhite() != p_white ? "true" : "";
        casesValideKnight.push_back( std::to_string( p_x - 3 ) + "-" + std::to_string( p_y - 2 ) +  "-" +Bool );

        Bool = e.GetPiece( p_x - 2 , p_y + 1  ) == nullptr ? "false" : e.GetPiece( p_x - 2 , p_y + 1 )->GetIsWhite() != p_white ? "true" : "";
        casesValideKnight.push_back( std::to_string( p_x - 3 ) + "-" + std::to_string( p_y ) + "-" +Bool);

        Bool = e.GetPiece( p_x + 1 , p_y + 2  ) == nullptr ? "false" : e.GetPiece( p_x + 1 , p_y + 2 )->GetIsWhite() != p_white ? "true" : "";
        casesValideKnight.push_back( std::to_string( p_x ) + "-" + std::to_string( p_y + 1 ) + "-" + Bool );

        Bool = e.GetPiece( p_x - 1 , p_y + 2  ) == nullptr ? "false" : e.GetPiece( p_x - 1 , p_y + 2 )->GetIsWhite() != p_white ? "true" : "" ;
        casesValideKnight.push_back( std::to_string( p_x - 2 ) + "-" + std::to_string( p_y + 1 ) + "-" + Bool );

        Bool = e.GetPiece( p_x + 1 , p_y - 2  ) == nullptr ? "false" : e.GetPiece( p_x + 1 , p_y - 2 )->GetIsWhite() != p_white ? "true" : "";
        casesValideKnight.push_back( std::to_string( p_x ) + "-" + std::to_string( p_y - 3 ) + "-" + Bool );

        Bool = e.GetPiece( p_x - 1 , p_y - 2  ) == nullptr ? "false" : e.GetPiece( p_x - 1 , p_y - 2 )->GetIsWhite() != p_white ?  "true" : "";
        casesValideKnight.push_back( std::to_string( p_x - 2 ) + "-" + std::to_string( p_y - 3 ) + "-" + Bool );
    }
    return casesValideKnight;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Constructeur du Pawn.
 * @param white -> Couleur du Pawn.
 * @param path -> Chemin d'image de l'image du Pawn.
 */
Pawn::Pawn( bool white, int x, string path ) : Piece( x, white ? 2 : 7, white, path ){}

/**
 * @brief Destructeur du Pawn.
 */
Pawn::~Pawn(){}

/**
 * @brief Pawn::DoitEvoluer
 * @param e
 * @param whitePlay
 * @return
 */
bool
Pawn::DoitEvoluer(ChessBoard &e,bool whitePlay )
{

    if ((this->p_y == 8 && this->GetIsWhite() == true) || (this->p_y == 1 && this->GetIsWhite() == false))
    {
        cout << "le Pawn peut etre évolué" << endl;
    }
    return true;
}

/**
 * @brief Récupère les coordonnées des cellules dont le mouvement est valide pour le Pawn.
 * @param ChessBoard e
 * @param bool whitePlay -> Vrai si c'est le Rook du joueur blanc, Faux sinon.
 * @return list<string> values -> Liste de toutes les coordonnées des cellules valides pour les déplacements du Pawn.
 *        Les coordonnées renseignées sont au format : 'x-y-bool' ou x correspond à la colonne de la cellule, y correspond à la ligne
 *        de la cellule et bool correspond à l'attribution de la couleur true -> bleu , false -> rose
 */
list<string>
Pawn::DisplayAvailableMovement(ChessBoard &e, bool whitePlay)
{
    list<string> casesValidePawn;
    int destination = ( GetFirstMove() ? 2 : 1 );

    if ( p_white && whitePlay)
    {
        for ( int i = p_y + 1  ; i <= p_y + destination ; i++ )
            if ( e.GetPiece( p_x , i  ) == nullptr )
                casesValidePawn.push_back( std::to_string( p_x - 1 ) + "-" + std::to_string( i - 1 )  + "-false" );

        if ( e.GetPiece( p_x + 1 , p_y + 1 ) != nullptr && e.GetPiece( p_x + 1 , p_y + 1 )->GetIsWhite() != GetIsWhite() )
            casesValidePawn.push_back( std::to_string( p_x ) + "-" + std::to_string( p_y ) + "-true");

        if ( e.GetPiece( p_x - 1 , p_y + 1 ) != nullptr && e.GetPiece( p_x - 1 , p_y + 1 )->GetIsWhite() != GetIsWhite() )
             casesValidePawn.push_back( std::to_string( p_x - 2 ) + "-" + std::to_string( p_y )  + "-true");
    }
    else if ( !p_white && !whitePlay )
    {
        for ( int i = p_y - 1  ; i >= p_y - destination ; i-- )
            if ( e.GetPiece( p_x , i  ) == nullptr )
              casesValidePawn.push_back(  std::to_string( p_x - 1 ) + "-" + std::to_string( i - 1 ) + "-false" );

        if ( e.GetPiece( p_x + 1 , p_y - 1 ) != nullptr && e.GetPiece( p_x + 1 , p_y - 1 )->GetIsWhite() != GetIsWhite())
            casesValidePawn.push_back( std::to_string( p_x ) + "-" + std::to_string( p_y - 2 ) + "-true");

        if ( e.GetPiece( p_x - 1 , p_y - 1 ) != nullptr && e.GetPiece( p_x - 1 , p_y - 1 )->GetIsWhite() != GetIsWhite() )
            casesValidePawn.push_back( std::to_string( p_x - 2 ) + "-" + std::to_string( p_y - 2 ) + "-true" );
    }
    return casesValidePawn;
}
