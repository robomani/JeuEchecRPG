#ifndef __CHEVALIER__
#define __CHEVALIER__

#include "Piece.h"
class Chevalier :
	public Piece
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Chevalier"/> class.
	/// </summary>
	/// <param name="a_Color">a color.</param>
	Chevalier(const Enums::EPieceColor a_Color, int i_HP, int i_Attack, int i_Armor = 0);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Chevalier"/> class.
	/// </summary>
	virtual ~Chevalier();
};

#endif // __CHEVALIER__

