#ifndef __PION__
#define __PION__

#include "Piece.h"

class Pion :
	public Piece
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Pion"/> class.
	/// </summary>
	/// <param name="a_PieceColor">Color of a piece.</param>
	Pion(const Enums::EPieceColor a_PieceColor, int i_HP, int i_Attack, int i_Armor = 0);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Pion"/> class.
	/// </summary>
	virtual ~Pion();
	
	/// <summary>
	/// Gets the possible attacks.
	/// </summary>
	/// <returns>All possibles attack for the pawn</returns>
	virtual std::vector<std::vector<std::tuple<int, int>>> GetPossibleAttack() { return m_PossibleAttacks; }

	//Make the piece use it's power
	virtual void UsePower();

private:
	std::vector<std::vector<std::tuple<int, int>>> m_PossibleAttacks;   // Contains possible attacks for a pawn.
};

#endif // __PION__