#ifndef __FOU__
#define __FOU__

#include "Piece.h"
#include <string>

class Fou :
	public Piece
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Fou"/> class.
	/// </summary>
	/// <param name="a_PieceColor">Color of a piece.</param>
	Fou(const Enums::EPieceColor a_PieceColor, int i_HP, int i_Attack, int i_Armor = 0);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Fou"/> class.
	/// </summary>
	virtual ~Fou();
};

#endif // __FOU__
