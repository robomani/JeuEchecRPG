#ifndef __REINE__
#define __REINE__

#include "Piece.h"
class Reine :
	public Piece
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Reine"/> class.
	/// </summary>
	/// <param name="a_PieceColor">Color of a piece.</param>
	Reine(const Enums::EPieceColor a_PieceColor, int i_HP, int i_Attack, int i_Armor = 0);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Reine"/> class.
	/// </summary>
	virtual ~Reine();
};

#endif // __REINE__