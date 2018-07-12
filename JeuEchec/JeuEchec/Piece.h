#ifndef __PIECE__
#define __PIECE__

#include "EPieceColor.h"
#include "EPieceType.h"
#include "EDirection.h"
#include <SDL.h>
#include <string>
#include <vector>
#include <tuple>

class Case;

class Piece
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Piece"/> class.
	/// </summary>
	/// <param name="a_PieceTexturePath">a piece texture path.</param>
	Piece(const std::string a_PieceTexturePath, int i_HP, int i_Attack, int i_Armor = 0);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Piece"/> class.
	/// </summary>
	~Piece();
	
	/// <summary>
	/// Draws the piece's texture
	/// </summary>
	/// <param name="a_Parent">The parent to draw in</param>
	/// <param name="a_TargetedRect">The rectangle used to draw</param>
	void Draw(SDL_Surface* a_Parent, SDL_Rect* a_TargetedRect);
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	void Update();
	
	/// <summary>
	/// Gets the possible moves.
	/// </summary>
	/// <returns>All possible moves for the piece</returns>
	std::vector<std::vector<std::tuple<int, int>>> GetPossibleMoves() { return m_AvailableMoves; }
	
	/// <summary>
	/// Gets the possible attack.
	/// </summary>
	/// <returns>All possible attack moves for the piece</returns>
	virtual std::vector<std::vector<std::tuple<int, int>>> GetPossibleAttack() { return m_AvailableMoves; } // Return the same as availableMoves. Only pawns have different move for attack.
	
	/// <summary>
	/// Gets the color.
	/// </summary>
	/// <returns>The piece color</returns>
	const Enums::EPieceColor GetColor() { return m_PieceColor; }
	
	/// <summary>
	/// Gets the type.
	/// </summary>
	/// <returns>The piece type</returns>
	const Enums::EPieceType GetType() { return m_PieceType; }
	
	/// <summary>
	/// Determines whether the color of the piece is the same as the parameter.
	/// </summary>
	/// <param name="a_Color">The color to verify against</param>
	/// <returns>
	///   <c>true</c> if the color is the same as the parameter; otherwise, <c>false</c>.
	/// </returns>
	bool IsThisColor(Enums::EPieceColor a_Color) { return m_PieceColor == a_Color; }
	
	/// <summary>
	/// Determines whether the color of the piece is not the same as the parameter.
	/// </summary>
	/// <param name="a_Color">The color to verify against</param>
	/// <returns>
	///   <c>true</c> if the color is not the same as the parameter; otherwise, <c>false</c>.
	/// </returns>
	bool IsNotThisColor(Enums::EPieceColor a_Color) { return !IsThisColor(a_Color); }

	//Return if the piece can use its power
	bool GetPowerReady() { return m_PowerReady; }
	//Return the HP of the peice
	int GetHP() { return m_HP; }
	//Return the Attack of the peice
	int GetAttack() { return m_Attack; }
	//Return the Armor of the peice
	int GetArmor() { return m_Armor; }

	//Fonction to damage the peice. If the peice die it return true esle it return false
	bool DamagePiece(int i_Damage) { return (m_HP - (i_Damage - m_Armor)) > 0 ?  false : true; }
	//Make the piece able to use it's power again
	void ResetPower() { m_PowerReady = true; }
	//Boost the peice by selected amount
	void BoostPeice(int i_Boost) { m_Attack += i_Boost; m_HP += i_Boost; }
	
protected:
	
	/// <summary>
	/// Initializes this instance.
	/// </summary>
	virtual void Init();

	SDL_Surface* m_PieceTexture;  // The SDL Surface that contain the piece's texture

	Enums::EPieceType m_PieceType;  // The piece type
	Enums::EPieceColor m_PieceColor;  // The piece color

	std::vector<std::vector<std::tuple<int, int>>> m_AvailableMoves;  // Available moves for the piece

	//Life of the piece, if it drop to 0 or lower the piece die
	int m_HP;
	//Attack of the piece, when attacking reduce the HP of the piece being attacked by this amount minus defending piece armor
	int m_Attack;
	//Armor of the piece, when being attacked reduce the damage taken by this amount
	int m_Armor;
	//If true the piece can use it's super power
	bool m_PowerReady = true;

	//String That describe The Piece Power
	std::string m_PowerDescription;

private:	

};

#endif //__PIECE__
