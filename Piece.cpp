/**
 * @authors Yoan Laurain ; Hugo Carricart ; Nathan Lesourd
 * @brief Source Code de Piece
 * @file Piece.cpp
 * @date 26/10/2021
 * @version 0.8
 */
#include <iostream>
#include "Piece.h"
#include "ChessBoard.h"
using namespace std;

/**
 * @brief Piece Builder
 * @param x -> column coordinate
 * @param y -> line coordinate
 * @param white -> Piece color
 * @param path -> Piece image path
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
 * @brief Destroyer of the Piece
 */
Piece::~Piece(){}

/**
 * @brief Updates the coordinates of the piece as well as its first move attribute
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
 * @brief Returns the attribute p_isEchec
 */
bool
Piece::GetIsEchec() { return p_isEchec; }

/**
 * @brief Invert bool attribute p_isEchec
 */
void
Piece::SetIsEchec() { p_isEchec = !p_isEchec; }

/**
 * @brief Returns the attribute p_x
 */
int
Piece::GetX() { return p_x; }

/**
 * @brief Returns the attribute p_y
 */
int
Piece::GetY() { return p_y; }

/**
 * @brief Returns the attribute p_firstMove
 */
bool
Piece::GetFirstMove() { return p_firstMove; }

/**
 * @brief Returns the attribute p_white
 */
bool
Piece::GetIsWhite() { return p_white; }

/**
 * @brief Returns the attribute p_path
 */
string
Piece::GetPath() { return p_path; }

/**
 *  @brief Method called after the  echec() method, checks if the King has a valid move
 *  @param ChessBoard &e
 *  @param int x -> King's x position
 *  @param int y -> King's y position
 *  @return bool -> true if the King has a valid move and the piece that failed him does not leave him unsuccessful following this move, or false otherwise
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
 * @brief King builder
 * @param white -> King color
 * @param path -> King Image Path
 */
King::King( bool white, string path ) : Piece( 5, white ? 1 : 8, white, path){}

/**
 * @brief King's Destroyer
 */
King::~King(){}

/**
 *  @brief Checks if a "castling" is possible between the King and the Rook as a parameter.
 *  @param ChessBoard &e
 *  @param *Rook x -> Pointer to the Rook
 *  @return bool -> true if the displacement is possible false otherwise
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
 * @brief Retrieves the coordinates of the cells whose movement is valid for the King.
 * @param ChessBoard e
 * @param bool whitePlay -> True if it is the Rook of the white player, False otherwise.
 * @return list<string> values -> List of all the coordinates of the cells valid for the movements of the King.
 *        The coordinates entered are in the format: 'x-y-bool' where x corresponds to the column of the cell, y corresponds to the row
 *        of the cell and bool corresponds to the attribution of the color true -> blue, false -> pink
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
 * @brief Queen builder
 * @param white -> Queen color
 * @param path -> Image path of the Queen image.
 */
Queen::Queen( bool white, string path ) : Piece( 4, white ? 1 : 8, white , path ), Bishop( white, true ,path ), Rook( white, true ,path ){}

/**
 * @brief Queen's Destroyer
 */
Queen::~Queen(){}

/**
 * @brief Retrieves the coordinates of the cells whose movement is valid for the Queen.
 * @param ChessBoard e
 * @param bool whitePlay -> True if it is the Rook of the white player, False otherwise.
 * @return list<string> values -> List of all the coordinates of the cells valid for the movements of the Queen.
 *        The coordinates entered are in the format: 'x-y-bool' where x corresponds to the column of the cell, y corresponds to the row
 *        of the cell and bool corresponds to the attribution of the color true -> blue, false -> pink
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
 * @brief Builder of the Rook.
 * @param white -> Color of the Rook.
 * @param path -> Image path of the Rook image.
 */
Rook::Rook( bool white, bool gauche, string path ) : Piece( gauche ? 1 : 8, white ? 1 : 8, white, path ){}

/**
 * @brief Destroyer of the Rook.
 */
Rook::~Rook(){}

/**
 * @brief Retrieves the coordinates of the cells whose movement is valid for the Rook.
 * @param ChessBoard e
 * @param bool whitePlay -> True if it is the Rook of the white player, False otherwise
 * @return list<string> values -> List of all the coordinates of the cells valid for the movements of the Rook.
 *        The coordinates entered are in the format: 'x-y-bool' where x corresponds to the column of the cell, y corresponds to the row
 *        of the cell and bool corresponds to the attribution of the color true -> blue, false -> pink
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
 * @brief Builder of the Bishop.
 * @param white -> Bishop color.
 * @param path -> Image path of the Bishop image.
 */
Bishop::Bishop( bool white, bool gauche, string path ) : Piece( gauche ? 3 : 6, white ? 1 : 8, white, path ){}

/**
 * @brief Bishop's Destroyer.
 */
Bishop::~Bishop(){}

/**
 * @brief Retrieves the coordinates of the cells whose movement is valid for the Bishop.
 * @param ChessBoard e
 * @param bool whitePlay -> True if it is the Rook of the white player, False otherwise.
 * @return list<string> values -> List of all the coordinates of the cells valid for the movements of the Bishop.
 *        The coordinates entered are in the format: 'x-y-bool' where x corresponds to the column of the cell, y corresponds to the row
 *        of the cell and bool corresponds to the attribution of the color true -> blue, false -> pink
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
 * @brief Knight's builder.
 * @param white -> Knight's color.
 * @param path -> Image path of the Knight image.
 */
Knight::Knight( bool white, bool gauche, string path ) : Piece( gauche ? 2 : 7, white ? 1 : 8, white, path ){}

/**
 * @brief Destroyer of the Knight.
 */
Knight::~Knight(){}

/**
 * @brief Retrieves the coordinates of cells whose movement is valid for the Knight.
 * @param ChessBoard e
 * @param bool whitePlay -> True if it is the Rook of the white player, False otherwise.
 * @return list<string> values -> List of all the coordinates of the cells valid for the movements of the Knight.
 *        The coordinates entered are in the format: 'x-y-bool' where x corresponds to the column of the cell, y corresponds to the row
 *        of the cell and bool corresponds to the attribution of the color true -> blue, false -> pink
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
 * @brief Pawn builder.
 * @param white -> Color of the Pawn.
 * @param path -> Image path of the Pawn.
 */
Pawn::Pawn( bool white, int x, string path ) : Piece( x, white ? 2 : 7, white, path ){}

/**
 * @brief Pawn Destroyer.
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
 * @brief Retrieves the coordinates of the cells whose movement is valid for the Pawn.
 * @param ChessBoard e
 * @param bool whitePlay -> True if it is the Rook of the white player, False otherwise.
 * @return list<string> values -> List of all the coordinates of the cells valid for the movements of the Pawn.
 *        The coordinates entered are in the format: 'x-y-bool' where x corresponds to the column of the cell, y corresponds to the row
 *        of the cell and bool corresponds to the attribution of the color true -> blue, false -> pink
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
