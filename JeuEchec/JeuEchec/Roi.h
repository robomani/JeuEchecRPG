#ifndef __ROI__
#define __ROI__

#include "Piece.h"
class Roi :
	public Piece
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Roi"/> class.
	/// </summary>
	/// <param name="a_PieceColor">Color of a piece.</param>
	Roi(const Enums::EPieceColor a_PieceColor, int i_HP, int i_Attack, int i_Armor = 0);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Roi"/> class.
	/// </summary>
	virtual ~Roi();
};

#endif // __ROI__