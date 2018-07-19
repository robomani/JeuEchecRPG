#include "Reine.h"

Reine::Reine(const Enums::EPieceColor a_PieceColor, int i_HP, int i_Attack, int i_Armor)
	: Piece(a_PieceColor == Enums::EPieceColor::Blanche ? "images/WQueen" : "images/BQueen", i_HP, i_Attack, i_Armor)
{
	Piece::m_PowerupDescr = "If The cases are empty, the queen spawn 3 Pion in front of her in a perpendicular line.";

	m_PieceType = Enums::EPieceType::Reine;
	m_PieceColor = a_PieceColor;

	for (int i = 1, j = 1; i < 8; i++, j++)
	{
		m_AvailableMoves[Enums::EDirection::North_East].push_back(std::tuple<int, int>(i, j));
		m_AvailableMoves[Enums::EDirection::North_West].push_back(std::tuple<int, int>(i, -j));
		m_AvailableMoves[Enums::EDirection::South_East].push_back(std::tuple<int, int>(-i, j));
		m_AvailableMoves[Enums::EDirection::South_West].push_back(std::tuple<int, int>(-i, -j));

		m_AvailableMoves[Enums::EDirection::North].push_back(std::tuple<int, int>(i, 0));
		m_AvailableMoves[Enums::EDirection::East].push_back(std::tuple<int, int>(0, j));
		m_AvailableMoves[Enums::EDirection::South].push_back(std::tuple<int, int>(-i, 0));
		m_AvailableMoves[Enums::EDirection::West].push_back(std::tuple<int, int>(0, -j));
	}

	if (m_PieceColor == Enums::EPieceColor::Noire)
	{
		m_AffectedPower[Enums::EDirection::North_East].push_back(std::tuple<int, int>(1, 1));
		m_AffectedPower[Enums::EDirection::North].push_back(std::tuple<int, int>(1, 0));
		m_AffectedPower[Enums::EDirection::North_West].push_back(std::tuple<int, int>(1, -1));
	}
	else
	{
		m_AffectedPower[Enums::EDirection::South_East].push_back(std::tuple<int, int>(-1, 1));
		m_AffectedPower[Enums::EDirection::South_West].push_back(std::tuple<int, int>(-1, -1));
		m_AffectedPower[Enums::EDirection::South].push_back(std::tuple<int, int>(-1, 0));
	}
	
}

Reine::~Reine()
{
}