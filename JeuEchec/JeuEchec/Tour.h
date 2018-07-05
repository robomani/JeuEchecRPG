#ifndef __TOUR__
#define __TOUR__

#include "Piece.h"
class Tour :
	public Piece
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Tour"/> class.
	/// </summary>
	/// <param name="a_PieceColor">Color of a piece.</param>
	Tour(const Enums::EPieceColor a_PieceColor, int i_HP, int i_Attack, int i_Armor = 0);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Tour"/> class.
	/// </summary>
	virtual ~Tour();
};

#endif // __TOUR__