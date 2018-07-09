#include "Fou.h"

Fou::Fou(const Enums::EPieceColor a_PieceColor, int i_HP, int i_Attack, int i_Armor)
	: Piece(a_PieceColor == Enums::EPieceColor::Blanche ? "images/WBishop" : "images/BBishop", i_HP, i_Attack, i_Armor)
{
	m_PieceType = Enums::EPieceType::Fou;
	m_PieceColor = a_PieceColor;

	for (int i = 1, j = 1; i < 8; i++, j++)
	{
		m_AvailableMoves[Enums::EDirection::North_East].push_back(std::tuple<int, int>(i, j));
		m_AvailableMoves[Enums::EDirection::North_West].push_back(std::tuple<int, int>(i, -j));
		m_AvailableMoves[Enums::EDirection::South_East].push_back(std::tuple<int, int>(-i, j));
		m_AvailableMoves[Enums::EDirection::South_West].push_back(std::tuple<int, int>(-i, -j));
	}
}

Fou::~Fou()
{
}