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

	// Pouvoir du roi : Mange une piece et gagne toutes ses stats, si la pièce mangé n'avait pas utiliser son pouvoir le roi peut réutiliser le sien.
	virtual void EatPiece(int i_HP, int i_Attack, int i_Armor, bool i_Power) { m_HP += i_HP; m_Attack += i_Attack; m_Armor += i_Armor; i_Power ? m_PowerReady = true : m_PowerReady = false; }
};

#endif // __ROI__